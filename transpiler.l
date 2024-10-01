%{
#include <stdbool.h>
bool repeat = false;
bool iff = false;
FILE* output = NULL;
%}

%%
"PUSH" { fprintf(output,  "push( s," );}
[0-9]+ { fprintf(output, " %s ", yytext);}
"POP" { fprintf(output, "(unsigned int POP = pop( s )");}
"ROT" {fprintf(output, "rot( s");}
"PUT" {fprintf(output, "put( s");}
"PUTC" {fprintf(output, "sputc( s");}
"DIV" {fprintf(output, "sdiv( s");}
"COPY" {fprintf(output, "copy( s");}
"SWAP" {fprintf(output, "swap( s");}
"SUB" {fprintf(output, "sub( s");}
"MUL" {fprintf(output, "mul( s");}
"SUM" {fprintf(output, "sum( s");}
"REM" {fprintf(output, "rem( s");}
"PEEK" { fprintf(output, "(unsigned int PEEk = peek( s )");}
"SIZE" { fprintf(output, "(unsigned int SIZE = size( s )");}
"DROP" {fprintf(output, "drop( s");}
"REPEAT" {fprintf(output, "for (unsigned int i = 0; i < "); repeat = true;}
"DEBUG" {fprintf(output, "debugenable( s");}
"LOOP" {fprintf(output, "while(1)");}
"BREAK" {fprintf(output, "break");}
"IF" {fprintf(output, "if ("); iff = true; }
";" {fprintf(output, " );\n");}
"DO" {if (repeat){fprintf(output, "; i++) {\n"); repeat = false;}
else if (iff){fprintf(output, ") {"); iff = false; }
else{fprintf(output, " {\n");} }
"END" {fprintf(output, " }\n");}
[ \t\n] { }
. {fprintf(stderr, "error undefine chars/char: %s\n", yytext);exit(1);}
%%

int main(){
    yyin = fopen("test.piatti", "r");
    output = fopen("out.c", "w");
    yylex();
    fclose(yyin);
    fclose(output);
}