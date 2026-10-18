import { Token, TokenType } from "../cube_dsl/Token.js"
import {Node, NodeType} from "../cube_dsl/Ast.js"
export class Parser {
    lexed_code: Token[][]
    token_stream: Token[]
    ASTs: Node[]

    constructor(lexed_code: Token[][]) {
        this.lexed_code = lexed_code
        this.token_stream = []
        this.ASTs = []

        let i = 0
        let ast: Node

        for (this.token_stream of lexed_code) {
            let res = this.parse_statement(i)
            if (res != null) {
                [i, ast] = res
                this.ASTs.push(ast)
                console.log(ast)
            }
            i = 0
        }
    }

    parse_paren(i: number): [number, Node] | null {
        let ast
        const open = this.token_stream[i]
        if (open.type != "(") return null
        i++

        const mid = this.parse_expression(i);
        if (mid == null) return null;
        [i, ast] = mid;

        const close = this.token_stream[i]
        if (close.type != ")") return null
        i++

        return [i, ast]
    }

    parse_concat(i: number): [number, Node] | null {
        let astLeft: Node | null = null;
        let astRight: Node | null = null;

        const left = this.parse_term(i);
        if (left == null) return null;
        [i, astLeft] = left;

        const right = this.parse_expression(i);
        if (right == null) return null;
        [i, astRight] = right;

        return [i, {
        kind: "Concat",
        left: astLeft,
        right: astRight,
        }];
    }

    parse_commutator(i: number): [number, Node] | null{
        
        let astLeft: Node | null = null;
        let astRight: Node | null = null;

        const open = this.token_stream[i]
        if (open.type != "[") return null
        i++

        const left = this.parse_expression(i);
        if (left == null) return null;
        [i, astLeft] = left;

        const mid = this.token_stream[i]
        if (mid.type != ";") return null
        i++

        const right = this.parse_expression(i);
        if (right == null) return null;
        [i, astRight] = right;

        const close = this.token_stream[i]
        if (close.type != "]") return null
        i++

        const result: Node = {
            kind:"Commutator",
            left:astLeft,
            right:astRight}

        return [i, result]
    }   
    
    parse_prime(i: number): [number, Node] | null {
        let astLeft: Node | null
        const func_order = [
            this.parse_repeat_right.bind(this),
            this.parse_commutator.bind(this),
            this.parse_repeat.bind(this),
            this.parse_ident.bind(this),
            this.parse_paren.bind(this)
        ]
        const left = this.parse(i, func_order);
        if (left == null) return null;
        [i, astLeft] = left;

        const prime = this.token_stream[i]
        if (prime.type != "\'") return null
        i++

        const result: Node = {
            kind:"Prime",
            left:astLeft,
            right:null}

        return [i, result]
    }

    parse_repeat(i: number): [number, Node] | null {
        let astRight: Node | null

        const prime = this.token_stream[i]
        if (prime.type != "NUM") return null 
        i++

        const right = this.parse_term(i);
        if (right == null) return null;
        [i, astRight] = right;
        
        const result: Node = {
            kind:"Repeat",
            left:prime.value as number,
            right:astRight
        }

        return [i, result]
    }

    parse_repeat_right(i: number): [number, Node] | null {
        let astLeft: Node | null
        const func_order = [
            this.parse_commutator.bind(this),
            this.parse_ident.bind(this),
            this.parse_paren.bind(this)
        ]

        const left = this.parse(i, func_order);
        if (left == null) return null;
        [i, astLeft] = left;

        const num = this.token_stream[i]
        if (num.type != "NUM") return null 
        i++        

        const result: Node = {
            kind:"Repeat",
            left:num.value as number,
            right:astLeft
        }

        return [i, result]
    }

    parse_ident(i: number): [number, Node] | null {
        const prime = this.token_stream[i]
        if (prime.type != "IDENT") return null 
        i++

        const result: Node = {
            kind:"Ident",
            left:prime.value as string,
            right:null
        }
        return [i, result]
    }

    parse_binding(i: number): [number, Node] | null {
        let astLeft, astRight

        const left = this.parse_ident(i);
        if (left == null) return null;
        [i, astLeft] = left;

        const mid = this.token_stream[i]
        if (mid.type != "=") return null
        i++

        const right = this.parse_expression(i);
        if (right == null) return null;
        [i, astRight] = right;
        
        const result: Node = {
            kind:"Binding",
            left:astLeft,
            right:astRight
        }
        
        return [i, result];
    }

    parse_term(i: number): [number, Node] | null {
        const func_order = [
            this.parse_prime.bind(this),
            this.parse_repeat_right.bind(this),
            this.parse_commutator.bind(this),
            this.parse_repeat.bind(this),
            this.parse_ident.bind(this),
            this.parse_paren.bind(this)
        ]
        return this.parse(i, func_order)
    }

    parse_expression(i: number): [number, Node] | null {
        const func_order = [
            this.parse_concat.bind(this),
            this.parse_term.bind(this)
        ]
        return this.parse(i, func_order)
    }

    parse_statement(i: number): [number, Node] | null {
        const func_order = [
            this.parse_binding.bind(this),
            this.parse_expression.bind(this)
        ]
        return this.parse(i, func_order)
    }


    parse(i: number, functions: Function[]): [number, Node] | null {
        for (let func of functions) {
            let res = func.call(this, i)
            if (res != null) {
                let [nextIndex, expr_ast] = res
                return [nextIndex, expr_ast]
            }
        }
        return null
    }
}