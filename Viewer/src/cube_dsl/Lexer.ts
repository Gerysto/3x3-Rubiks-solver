import { Token, TokenType, CharacterType} from "../cube_dsl/Token.js";

const STATEMENT_SEPARATOR = '\n'

export class Lexer {
    lexed_code: Token[][];
    token_stream: Token[];
    cursor: number;
    
    constructor(input_stream: string) {
        this.lexed_code = [];
        this.token_stream = [];
        this.cursor = 0;

        let i = 0;

        while (i < input_stream.length) {
            let c = input_stream[i];
            if (c == STATEMENT_SEPARATOR){
                if (this.token_stream.length == 0) { 
                    i++
                    continue
                }
                this.token_stream.push(
                    new Token(
                        "EOF",
                        i,
                        i+1
                    )
                )
                this.lexed_code.push(this.token_stream)

                this.token_stream = []
                i++
                console.log("Lexing new line!")
                continue
                
            }
            if (this.is_whitespace(c)) {
                i++;
                continue;
            }
            else if (/[a-zA-Z]/.test(c)) {
                let token = this.lex_identifier(input_stream, i);
                this.token_stream.push(token);
                i = token.to;
            } else if (/[0-9]/.test(c)) {
                let token = this.lex_number(input_stream, i);
                this.token_stream.push(token);
                i = token.to;
            } else if (c == "/") {
                i = this.lex_comment(input_stream, i);

            } else if (c as CharacterType) {
                let token = new Token(
                    c as CharacterType,
                    i,
                    i+1 
                );
                ++i;
                this.token_stream.push(token);
            } else {
                throw Error("Lexer error!");
            }
        }
    }

    is_whitespace(c: string) {
        return c == " " || c == "\t";
    }

    lex_number(input_stream: string, i_start: number): Token {
        let num: string = "";
        let i = i_start;
        let c = input_stream[i];
        while (/[0-9]/.test(c) && i < input_stream.length) {
            num = num.concat(c);
            ++i;
            c = input_stream[i];
        }
        let token: Token = new Token(
            "NUM", 
            i_start, 
            i,
            num);
        return token;
    }

    lex_identifier(input_stream: string, i_start: number): Token {
        let id: string = "";
        let i = i_start;
        let c = input_stream[i];
        while (/[a-zA-Z]/.test(c) && i < input_stream.length) {
            id = id.concat(c);
            ++i;
            c = input_stream[i];
        }
        let token: Token = new Token(
            "IDENT", 
            i_start, 
            i,
            id);
        return token;
    }
    
    lex_comment(input_stream: string, i_start: number): number {
        let i = i_start;
        let c = input_stream[i_start];
        if(input_stream.slice(0,2) != "//") throw Error("Lexer Error");

        while (c != "\n" && i < input_stream.length) ++i;
        return i;
    }

    peek(): Token {
        if (this.cursor >= this.token_stream.length){
            return new Token("EOF", this.token_stream.length, this.token_stream.length);
        }
        return this.token_stream[this.cursor];
    }

    next(): Token {
        let peek = this.peek();
        ++this.cursor;
        return peek;
    }

    print_token_stream() {
        console.log(this.token_stream.map((t, i, arr)=>t.type))
    }
}