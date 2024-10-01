%{
short int repeat = 0;
short int iff = 0;
//unsigned int val = 0;
%}

%%
"PUSH" { printf( "push( s," );}
[0-9]+ { printf("%s ", yytext);}
"POP" { printf("(unsigned int POP = pop( s )");}
"ROT" {printf("rot( s");}
"PUT" {printf("put( s");}
"PUTC" {printf("sputc( s");}
"DIV" {printf("sdiv( s");}
"COPY" {printf("copy( s");}
"SWAP" {printf("swap( s");}
"SUB" {printf("sub( s");}
"MUL" {printf("mul( s");}
"SUM" {printf("sum( s");}
"REM" {printf("rem( s");}
"PEEK" { printf("(unsigned int PEEk = peek( s )");}
"SIZE" { printf("(unsigned int SIZE = size( s )");}
"DROP" {printf("drop( s");}
"REPEAT" {printf("for (unsigned int i = 0; i < "); repeat = 1;}
"DEBUG" {printf("debugenable( s");}
"LOOP" {printf("while(1)");}
"BREAK" {printf("break");}
"IF" {printf("if ("); iff = 1; }
";" {printf(" );\n");}
"DO" {if (repeat){printf("; i++) { "); repeat = 0;}
if (iff){printf(") {"); iff = 0; }
else{printf(" { ");} }
"END" {printf(" } ");}
[ \t\n] { }
. {fprintf(stderr, "error undefine chars/char: %s\n", yytext);}
%%