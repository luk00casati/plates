%{
#include <stdbool.h>
bool repeatf = false;
bool iff = false;
FILE* output = NULL;
//int fileno(FILE *stream); //bad
const char* startheader = \
"#include <cpiatti.h>\n \
#include <stdio.h>\n \
#include <stdlib.h>\n \
#include <signal.h>\n \
#include <unistd.h>\n \
//global\n \
struct Stack s;\n \
\n \
void transpiledcode(struct Stack* s){\n \
init_stack(s);\n\n//stanspiledcode\n\n";

const char* endheader = \
"}\n\n//end\n\nvoid handle_signal(int sig) {\n \
const char *msg = SIGERRS;\n \
write(STDERR_FILENO, msg, sizeof(SIGERRS) - 1);\n \
deinit_stack(&s);\n \
_exit(1);\n \
}\n \
\n \
int main(){\n \
    signal(SIGINT, handle_signal);\n \
    transpiledcode(&s);\n \
    deinit_stack(&s);\n \
    return 0;\n \
}";

%}

%%
"PUSH" { fprintf(output,  "push( s," );}
[0-9]+ { fprintf(output, " %s ", yytext);}
"POP" { fprintf(output, "pop( s )");}
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
"PEEK" { fprintf(output, "peek( s )");}
"SIZE" { fprintf(output, "size( s )");}
"DROP" {fprintf(output, "drop( s");}
"REPEAT" {fprintf(output, "for (unsigned int i = 0; i < "); repeatf = true;}
"DEBUG" {fprintf(output, "debugenable( s");}
"LOOP" {fprintf(output, "while(1)");}
"BREAK" {fprintf(output, "break");}
"IF" {fprintf(output, "if ("); iff = true; }
"ELIF" {fprintf(output, "else if ("); iff = true; }
"ELSE" {fprintf(output, "else "); }
";" {fprintf(output, " );\n");}
"==" {fprintf(output, " == ");}
">=" {fprintf(output, " >= ");}
"<=" {fprintf(output, " <= ");}
"!=" {fprintf(output, " != ");}
">" {fprintf(output, " > ");}
"<" {fprintf(output, " < ");}
"PUTNL" {fprintf(output, "printf( NL");}
"DO" {if (repeatf){fprintf(output, "; i++) {\n"); repeatf = false;}
else if (iff){fprintf(output, ") {\n"); iff = false; }
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
    output = fopen("/tmp/tmppiattiout.c", "w");
    if (output == NULL){
        fprintf(stderr, "error opening /tmp/tmppiattiout.c\n");
        exit(1);
    }
    fprintf(output, "%s", startheader);
    yylex();
    fclose(yyin);
    fprintf(output, "%s", endheader);
    fclose(output);
}
