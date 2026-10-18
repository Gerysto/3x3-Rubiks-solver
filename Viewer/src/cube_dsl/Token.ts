export type CharacterType = "(" | ")" | "[" | "]" | ";" | "\'" | "=";


export type TokenType = "NUM" | "IDENT" | CharacterType | "EOF";

export class Token {
    type: TokenType;
    line: number;
    value: number | string | null;
    from: number;
    to: number;

    constructor(type: TokenType, line: number, from: number, to: number, 
        value: number | string | null = null) {
        this.type = type;
        this.line = line;
        this.from = from;
        this.to = to;this.value = value
        
    }
}