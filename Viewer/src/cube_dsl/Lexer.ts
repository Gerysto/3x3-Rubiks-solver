import { Token, TokenType, CharacterType} from "../cube_dsl/Token.js";

const STATEMENT_SEPARATOR = '\n'

export class Lexer {
    lexed_code: Token[][];
    line_num: number;

    constructor(input_stream: string) {
        this.lexed_code = [];
        this.line_num = 1
        
        let input_lines = input_stream.split(STATEMENT_SEPARATOR)
        
        for (const line of input_lines) {
            const EOF = new Token("EOF",this.line_num, line.length, line.length)
            const lexed_line = this.lex_line(line).concat([EOF])
            this.lexed_code.push(lexed_line)
            this.line_num++
        }
    }

    lex_line(input_stream: string): Token[]{
        let i = 0;
        let token_stream: Token[] = []

        while (i < input_stream.length) {
            let c = input_stream[i];
            
            if (this.is_whitespace(c)) {
                i++;
                continue;
            }
            else if (/[a-zA-Z]/.test(c)) {
                let token = this.lex_identifier(input_stream, i);
                token_stream.push(token);
                i = token.to;
            } else if (/[0-9]/.test(c)) {
                let token = this.lex_number(input_stream, i);
                token_stream.push(token);
                i = token.to;
            } else if (c == "/") {
                i = this.lex_comment(input_stream, i);

            } else if (c as CharacterType) {
                let token = new Token(
                    c as CharacterType,
                    this.line_num,
                    i,
                    i+1
                );
                ++i;
                token_stream.push(token);
            } else {
                throw Error("Lexer error!");
            }
        }
        return token_stream
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
            this.line_num,
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
            this.line_num,
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
}