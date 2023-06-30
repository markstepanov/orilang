#ifndef ORI_LEXER
#define ORI_LEXER
#include "../arena_allocator.h"


enum Tokens{
    ILLIGALL = 0,
    PLUS,
    MULT,
    MINUS,
    SLASH,
    ASSIGN,
    PAR_OPEN,
    PAR_CLOSE,
    CUR_BRAC_OPEN,
    CUR_BRAC_CLOSE,
    COMMA,
    NUM_LITERAL,
    STRING_LITERAL,
    CHAR,
    EXP_END,
    RESERVED_KEYWORD,
    ENUM_LENGHT
};


enum ReservedKeywords {
    KW_ILLIGAL = 0,
    KW_FUNC ,
    KW_TRUE,
    KW_FALSE,
    KW_IF,
    KW_ELSE,
    KW_BREAK,
    KW_RETURN,
    KW_ENUM_LENGHT
};

struct Token{
    Tokens token;
    char* val;
    ReservedKeywords keyword;
    int line;
};



void print_lexed(Token* program_tokens);

void lex(Arena* arena, char* program, int program_lenght, Token* program_tokens);
#endif