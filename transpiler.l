%{
short int repeat = 0;
unsigned int val = 0;
%}

%%
"PUSH" { printf( "push( " );}
[0-9]+ { printf("%s ", yytext);}
"REPEAT" {printf("for (unsigned int i = 0; i < "); repeat = 1;}
"LOOP" {printf("while(1)");}
"BREAK" {printf("break");}
';' {printf(" );\n");}
"DO" {if (repeat){printf("; i++) { "); repeat = 0;}else{printf(" { ");} }
"END" {printf(" } ");}
[ \t\n] { }
. {printf("error undefine chars/char: %s\n", yytext);}
%%