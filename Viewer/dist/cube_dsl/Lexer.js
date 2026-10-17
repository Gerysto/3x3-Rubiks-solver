class Token {
    constructor(type, from, to) {
        this.type = type;
        this.from = from;
        this.to = to;
    }
}
export class Lexer {
    constructor(input_stream) {
        this.token_stream = [];
        this.cursor = 0;
        let i = 0;
        while (i < input_stream.length) {
            let c = input_stream[i];
            if (this.is_whitespace(c)) {
                i++;
                continue;
            }
            else if (/[a-zA-Z]/.test(c)) {
                let token = this.lex_identifier(input_stream, i);
                this.token_stream.push(token);
                i = token.to;
            }
            else if (/[0-9]/.test(c)) {
                let token = this.lex_number(input_stream, i);
                this.token_stream.push(token);
                i = token.to;
            }
            else if (c == "/") {
                i = this.lex_comment(input_stream, i);
            }
            else if (c) {
                let token = new Token(c, i, i + 1);
                this.token_stream.push(token);
            }
            else {
                throw Error("Lexer error!");
            }
        }
    }
    is_whitespace(c) {
        return c == " " || c == "\n" || c == "\t";
    }
    lex_number(input_stream, i_start) {
        let num = "";
        let i = i_start;
        let c = input_stream[i_start];
        while (/[0-9]/.test(c) && i < input_stream.length) {
            num.concat(c);
            ++i;
        }
        let token = new Token({ val: Number(num) }, i_start, i);
        return token;
    }
    lex_identifier(input_stream, i_start) {
        let id = "";
        let i = i_start;
        let c = input_stream[i_start];
        while (/[a-zA-Z]/.test(c) && i < input_stream.length) {
            id.concat(c);
            ++i;
        }
        let token = new Token({ val: id }, i_start, i);
        return token;
    }
    lex_comment(input_stream, i_start) {
        let i = i_start;
        let c = input_stream[i_start];
        if (input_stream.slice(0, 2) != "//")
            throw Error("Lexer Error");
        while (c != "\n" && i < input_stream.length)
            ++i;
        return i;
    }
    peek() {
        if (this.cursor >= this.token_stream.length) {
            return new Token("EOF", this.token_stream.length, this.token_stream.length);
        }
        return this.token_stream[this.cursor];
    }
    next() {
        let peek = this.peek();
        ++this.cursor;
        return peek;
    }
}
