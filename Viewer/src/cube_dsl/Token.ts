export type CharacterType = "(" | ")" | "[" | "]" | ";" | "\'" | "=";


export type TokenType = "NUM" | "IDENT" | CharacterType | "EOF";

export class Token {
    type: TokenType;
    value: number | string | null;
    from: number;
    to: number;

    constructor(type: TokenType, from: number, to: number, 
        value: number | string | null = null) {
        this.type = type;
        this.from = from;
        this.to = to;this.value = value
        
    }
}