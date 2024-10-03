%{
#include <stdbool.h>
bool repeat = false;
bool iff = false;
FILE* output = NULL;
//int fileno(FILE *stream); //bad
const char* startheader = \
"#include <cpiatti.h> \n \
#include <stdio.h> \n \
#include <stdlib.h> \n \
#include <signal.h> \n \
\n \
void transpiledcode(struct Stack* s){ \n \
init_stack(s);\n\n//stanspiledcode\n\n";

const char* endheader = \
"}\n\n//end\n\nvoid handle_signal(){ \n \
//free stack \n \
fprintf(stderr, SIGERRS); \n \
exit(0); \n \
} \n \
\n \
int main(){ \n \
    struct Stack s; \n \
    signal(SIGINT, handle_signal); \n \
    transpiledcode(&s); \n \
    deinit_stack(&s); \n \
    return 0; \n \
}";

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
"==" {fprintf(output, " == ");}
">=" {fprintf(output, " >= ");}
"<=" {fprintf(output, " <= ");}
"!=" {fprintf(output, " != ");}
">" {fprintf(output, " > ");}
"<" {fprintf(output, " < ");}
"PUTNL" {fprintf(output, "printf( NL");}
"DO" {if (repeat){fprintf(output, "; i++) {\n"); repeat = false;}
else if (iff){fprintf(output, ") {"); iff = false; }
else{fprintf(output, " {\n");} }
"END" {fprintf(output, " }\n");}
"//".* { /* COMMENT */ }
[ \t\n] { }
. {fprintf(stderr, "error undefine chars/char: %s\n", yytext);exit(1);}
%%

void transpile(const char* path){
    yyin = fopen(path, "r");
    if (yyin == NULL){
        fprintf(stderr, "error opening %s\n", path);
        exit(1);
    }
    output = fopen("/tmp/temppiattiout.c", "w");
    if (output == NULL){
        fprintf(stderr, "error opening /tmp/temppiattiout.c\n");
        exit(1);
    }
    fprintf(output, "%s", startheader);
    yylex();
    fclose(yyin);
    fprintf(output, "%s", endheader);
    fclose(output);
}
