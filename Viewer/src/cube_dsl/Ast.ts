export type NodeType = "Commutator" | "Concat" | "Prime" | "Ident" | "Repeat" | "Binding"

export interface Node {
    kind: NodeType,
    left: string | number | Node
    right: null | Node
}