#pragma once

#define REGEX_DEBUGON 0
#define REGEX_DEBUGOFF 1
#define REGEX_REPEAT 2
#define REGEX_BREAK 3
#define REGEX_END 4
#define REGEX_IF 5
#define REGEX_ELIF 6
#define REGEX_ELSE 7
#define REGEX_PUSH 8
#define REGEX_ROT 9
#define REGEX_PUT 10
#define REGEX_PUTC 11
#define REGEX_PUTNL 12
#define REGEX_COPY 13
#define REGEX_SWAP 14
#define REGEX_SUM 15
#define REGEX_SUB 16
#define REGEX_MUL 17
#define REGEX_DIV 18
#define REGEX_REM 19
#define REGEX_DROP 20
#define REGEX_EMPTYLINE 21
#define REGEX_POP 22
#define REGEX_LOOP 23
#define REGEX_PUSHC 24

#define REGEX_LIST_SIZE 25

#define END_IF 0
#define END_ELIF 1
#define END_ELSE 2
#define END_REPEAT 3
#define END_LOOP 4

#define OP_DEBUGON 0
#define OP_DEBUGOFF 1
#define OP_REPEAT 2
#define OP_BREAK 3
#define OP_END 4
#define OP_IF 5
#define OP_ELIF 6
#define OP_ELSE 7
#define OP_PUSH 8
#define OP_ROT 9
#define OP_PUT 10
#define OP_PUTC 11
#define OP_PUTNL 12
#define OP_COPY 13
#define OP_SWAP 14
#define OP_SUM 15
#define OP_SUB 16
#define OP_MUL 17
#define OP_DIV 18
#define OP_REM 19
#define OP_DROP 20
#define OP_POP 21
#define OP_LOOP 22
#define OP_ENDIF 23
#define OP_ENDELIF 24
#define OP_ENDELSE 25
#define OP_ENDREPEAT 26
#define OP_ENDLOOP 27
#define OP_EXIT 28
#define OP_PUSHC 29

#define NULLSTR "NULLSTR"

//#define DEBUG