#include <string>
//#include <list>

enum regex_list { 
    REGEX_DEBUGON,
    REGEX_DEBUGOFF,
    REGEX_REPEAT,
    REGEX_END,
    REGEX_IF,
    REGEX_ELIF,
    REGEX_ELSE,
    REGEX_PUSH,
    REGEX_ROT,
    REGEX_PUT,
    REGEX_PUTC,
    REGEX_PUTNL,
    REGEX_COPY,
    REGEX_SWAP,
    REGEX_SUM,
    REGEX_SUB,
    REGEX_MUL,
    REGEX_DIV,
    REGEX_REM,
    REGEX_DROP
}; 

std::string regex_list_conv(enum regex_list value){
    switch (value)
    {
    case REGEX_DEBUGON:
        return "\s*DEBUGON\s*\n";
    case REGEX_DEBUGOFF:
        return "\s*DEBUGOFF\s*\n";
    case REGEX_REPEAT:
        return "\s*REPEAT\s*(.*)\s*DO\s*\n";
    case REGEX_END:
        return "\s*END\s*\n";
    case REGEX_IF:
        return "\s*IF\s*(.*)\s*DO\s*\n";
    case REGEX_ELIF:
        return "\s*ELIF\s*(.*)\s*DO\s*\n";
    case REGEX_ELSE:
        return "\s*ELSE\s+DO\s*\n";
    case REGEX_PUSH:
        return "\s*PUSH\s*(\d+)\s*\n";
    case REGEX_ROT:
        return "\s*ROT\s*\n";
    case REGEX_PUT:
        return "\s*PUT\s*\n";
    case REGEX_PUTC:
        return "\s*PUTC\s*\n";
    case REGEX_PUTNL:
        return "\s*PUTNL\s*\n";
    case REGEX_COPY:
        return "\s*COPY\s*\n";
    case REGEX_SWAP:
        return "\s*SWAP\s*\n";
    case REGEX_SUM:
        return "\s*SUM\s*\n";
    case REGEX_SUB:
        return "\s*SUB\s*\n";
    case REGEX_MUL:
        return "\s*MUL\s*\n";
    case REGEX_DIV:
        return "\s*DIV\s*\n";
    case REGEX_REM:
        return "\s*REM\s*\n";
    case REGEX_DROP:
        return "\s*DROP\s*\n";

    default:
        perror("invalid regex");
        exit(1);
        break;
    }
    return "";
}

//std::list<std::string> valid_token = {"REPEAT", "DO", "END", "IF",
//"ELIF", "ELSE", "DEBUGON", "DEBUGOFF"};
