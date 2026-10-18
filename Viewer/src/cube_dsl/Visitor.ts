import {Node, NodeType} from "../cube_dsl/Ast.js"
import {DEFAULT_TABLE_OF_SYMBOLS, VALID_MOVE, VALID_MOVES, Sequence} from "../cube_dsl/constants.js"

const zip = (a:any[], b:any[]) => a.map((k:any, i:number) => [k, b[i]]);

function alg_to_string(alg: Sequence): string {
    let result = ""
    for (let [move, prime] of zip(alg.moves, alg.primes)) {
        result += move
        if (prime) result += "\'"
        result += " "
    }
    return result
}

function invert_alg(alg: Sequence): Sequence {
    let primes = alg.primes.slice()
    let moves = alg.moves.slice()
    for (let i = 0; i < alg.primes.length; ++i) primes[i] = !primes[i]
    return {moves: moves.reverse(), primes: primes.reverse()} as Sequence
}

function concat_algs(algs: Sequence[]): Sequence {
    let moves: VALID_MOVE[] = []
    let primes: boolean[] = []
    for (let alg of algs) {
        moves = moves.concat(alg.moves)
        primes = primes.concat(alg.primes)
    }
    return {moves: moves,primes: primes}
}

export class Visitor {
    table_of_symbols: Record<string,Sequence>

    constructor() {
        this.table_of_symbols = DEFAULT_TABLE_OF_SYMBOLS
    }

    visit_tree(ASTs: Node[]): String {
        let res = "" 
        for (let AST of ASTs) {
            let seq = this.visit_node(AST)
            if (seq) res += alg_to_string(seq)
        }
        return res
    }

    visit_commutator(node: Node): Sequence {
        let [l, r] = this.visit_children(node)
        return concat_algs([l, r, invert_alg(l), invert_alg(r)])
    }
    visit_concat(node: Node): Sequence {
        let [seq_left, seq_right] = this.visit_children(node)
        return concat_algs([seq_left, seq_right]) 
    }
    visit_prime(node: Node): Sequence {
        let [seq_left, _] = this.visit_children(node)
        return invert_alg(seq_left)
    }
    visit_ident(node: Node): Sequence {
        let name = node.left as string
        if (this.table_of_symbols[name] === undefined) throw Error(`Undeclared Identifier ${name}`)
        return this.table_of_symbols[name]
    }
    visit_repeat(node: Node): Sequence {
        let count = node.left as number
        let seq = this.visit_node(node.right as Node) as Sequence
        let res = {moves:[], primes:[]} as Sequence
        for (let i = 0; i < count; ++i) {
            res = concat_algs([res, seq])
        }
        return res as Sequence
    }
    visit_binding(node: Node): void {
        let name = (node.left as Node).left as string
        let value = this.visit_node(node.right as Node) as Sequence
        if (name in VALID_MOVES) throw Error(`Reserved identifier ${name}`)
        this.table_of_symbols[name] = value
    }

    visit_node(node: Node): Sequence | void {
        if (node === null) return {} as Sequence
        switch(node.kind) {
            case "Commutator":
                return this.visit_commutator(node)
            case "Concat":
                return this.visit_concat(node)
            case "Prime":
                return this.visit_prime(node)
            case "Ident":
                return this.visit_ident(node)
            case "Repeat":
                return this.visit_repeat(node)
            case "Binding":
                this.visit_binding(node)
        }
    }
    visit_children(node: Node): [Sequence, Sequence] {
        let l = this.visit_node(node.left  as Node) as Sequence
        let r = this.visit_node(node.right as Node) as Sequence
        return [l, r] 
    }
}