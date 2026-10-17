import {Node, NodeType} from "../cube_dsl/Ast.js"
import {DEFAULT_TABLE_OF_SYMBOLS, VALID_MOVE, Sequence} from "../cube_dsl/constants.js"


function invert_alg(alg: Sequence): Sequence {
    for (let i = 0; i < alg.primes.length; ++i) alg.primes[i] = !alg.primes[i]
    return {moves: alg.moves.reverse(), primes: alg.primes.reverse()} as Sequence
}

function concat_algs(algs: Sequence[]): Sequence {
    let moves: VALID_MOVE[] = []
    let primes: boolean[] = []
    for (let alg of algs) {
        moves.concat(alg.moves)
        primes.concat(alg.primes)
    }
    return {moves: moves,primes: primes}
}

class Visitor {
    table_of_symbols: Record<string,Sequence>

    constructor(ASTs: Node[]) {
        this.table_of_symbols = DEFAULT_TABLE_OF_SYMBOLS
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
        let res = {} as Sequence
        for (let i = 0; i < count; ++i) {
            res = concat_algs([res, seq])
        }
        return res as Sequence
    }
    visit_binding(node: Node): void {
        let name = (node.left as Node).left as string
        let value = this.visit_node(node.right as Node) as Sequence
        this.table_of_symbols[name] = value
    }

    visit_node(node: Node): Sequence | void {
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