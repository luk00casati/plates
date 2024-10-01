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
"==" {fprintf(output, " == ");}
">=" {fprintf(output, " >= ");}
"<=" {fprintf(output, " <= ");}
"!=" {fprintf(output, " != ");}
">" {fprintf(output, " > ");}
"<" {fprintf(output, " < ");}
"DO" {if (repeat){fprintf(output, "; i++) {\n"); repeat = false;}
else if (iff){fprintf(output, ") {"); iff = false; }
else{fprintf(output, " {\n");} }
"END" {fprintf(output, " }\n");}
[ \t\n] { }
. {fprintf(stderr, "error undefine chars/char: %s\n", yytext);exit(1);}
%%

void transpile(const char* path ,const char* flag){
    yyin = fopen(path, "r");
    if (yyin == NULL){
        fprintf(stderr, "error opening %s\n", path);
        exit(1);
    }

    if ( strcmp(flag, "show") == 0){
        output = fopen("out.c", "w");
        if (output == NULL){
            fprintf(stderr, "error opening out.c\n");
            exit(1);
        }
    }
    else if ( strcmp(flag, "hidden") == 0){
        output = fopen("/tmp/tempout.c", "w");
        if (output == NULL){
            fprintf(stderr, "error opening /tmp/tempout.c\n");
            exit(1);
        }
    }
    else {
        fprintf(stderr, "invalid arg transpile");
        exit(1);
        }
    yylex();
    fclose(yyin);
    fprintf(output, "deninit_stack(s);");
    fclose(output);
}
