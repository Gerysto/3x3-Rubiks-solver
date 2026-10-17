
root : (assign | sequence)* EOF

sequence := IDENT (sequence)*;
			| '(' sequence ')'
			| '[' sequence ';' sequence ']'
			| (sequence)'\''
			| (sequence)NUM
			; 

assign := ID '=' sequence ;

NUM := [0-9]+ ;
ID := [a-zA-Z]+ ;


"[R U; [R U; R' U']]"