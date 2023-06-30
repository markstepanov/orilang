#ifndef ORI_AST
#define ORI_AST

#include "../lexer/lexer.h"

enum ASTSuperType{
    AST_ST_EXPRESSION = 0,
    AST_ST_STATEMENT,
    AST_ST_DECLARATION,
    AST_ST_ENUM_LENGHT
};


enum BasicTypes {
    VOID = 0,
    INT8,
    BT_ENUM_LENGHT
};

struct VarDecl {
    BasicTypes type;
    char* name;
};

struct FuncDecl {
// Should the name be referenced to token value?
// rn I think it's not that great of idea, I would like to free tokens 
    const char* name;
// EXPAND TO HAVE MULTIPLE RETURN TYPES.
// I think I should first get familiar with the way the compiler
// will generate actuall assembly and then work with multilpe return types.
    BasicTypes return_type; 

    BasicTypes* param_start;
    BasicTypes* param_end;

    uint8_t param_count;
// speaking about parameters, I like pre-definded paramaters like in python.
// the idea is - if paramater is pre-defined, than the caller may not pass it.
    
    Token* start;
    Token* end;
};

void generate_AST(Arena* arena, Token* tokens);

#endif