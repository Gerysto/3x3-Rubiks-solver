export const VALID_MOVES = ["R","L","U","D","F","B","r","l","u","d","f","b","M","E","S","X","Y","Z"]
export type VALID_MOVE = "R"|"L"|"U"|"D"|"F"|"B"|"r"|"l"|"u"|"d"|"f"|"b"|"M"|"E"|"S"|"X"|"Y"|"Z"

export interface Sequence {
    moves: VALID_MOVE[]
    primes: boolean[] 
}

export const DEFAULT_TABLE_OF_SYMBOLS: Record<string, Sequence> = {
    "R": {moves:["R"], primes:[false]} as Sequence,
    "L": {moves:["L"], primes:[false]} as Sequence,
    "U": {moves:["U"], primes:[false]} as Sequence,
    "D": {moves:["D"], primes:[false]} as Sequence,
    "F": {moves:["F"], primes:[false]} as Sequence,
    "B": {moves:["B"], primes:[false]} as Sequence,
    "r": {moves:["r"], primes:[false]} as Sequence,
    "l": {moves:["l"], primes:[false]} as Sequence,
    "u": {moves:["u"], primes:[false]} as Sequence,
    "d": {moves:["d"], primes:[false]} as Sequence,
    "f": {moves:["f"], primes:[false]} as Sequence,
    "b": {moves:["b"], primes:[false]} as Sequence,
    "M": {moves:["M"], primes:[false]} as Sequence,
    "E": {moves:["E"], primes:[false]} as Sequence,
    "S": {moves:["S"], primes:[false]} as Sequence,
    "X": {moves:["X"], primes:[false]} as Sequence,
    "Y": {moves:["Y"], primes:[false]} as Sequence,
    "Z": {moves:["Z"], primes:[false]} as Sequence,
} 