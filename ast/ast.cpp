#include "../stb_ds.h"
#include "assert.h"
#include <iostream>
#include "ast.h"
#include "../arena_allocator.h"


// struct ASTNode{
//     ASTSuperType type;
// };


// struct ParsingError{
//     char* err_message;
// // };

#define FUNC_NAME_OFFSET 1
#define FUNC_PARAM_PAREN_OPEN_OFFSET 2

void _parse_func(Arena* arena, Token* tokens, int offset){
    //NON VOID
    // func CHAR_LITERAL ( TYPE CHAR_LITERAL , TYPE CHAR_LITERAL )  TYPE {  RETURN CHAR_LITERAL || NUM_LITERAL || KEYWORD  } ; return may be more than once;
    //VOID
    // func CHAR_LITERAL ( TYPE CHAR_LITERAL , TYPE CHAR_LITERAL ) {    } ; return is prohibited;

    

    char* func_name;
    Token name_token =tokens[offset + FUNC_NAME_OFFSET];



    if(name_token.token != Tokens::STRING_LITERAL){
        std::cout << "Wrong Function Declaration at line " << name_token.line << "\n";
        std::exit(-1);
    }
    func_name = name_token.val;
    


    
    




        if (
            !(tokens[offset + FUNC_NAME_OFFSET ].token == Tokens::STRING_LITERAL && 
            tokens[offset + FUNC_PARAM_PAREN_OPEN_OFFSET].token == Tokens::PAR_OPEN)
        ){
            std::cout << "ERROR: Wrong function declaration on line " << tokens[offset+3].line << "\n";
            std::exit(-1);
        }

            Token* parameters = NULL;
            int cur_offset = 3;
            int tokenlen = arrlen(tokens);

            while ((cur_offset+ offset) < tokenlen){
               if ( 
                tokens[offset + cur_offset + 1 ].token == Tokens::STRING_LITERAL && 
                tokens[offset + cur_offset + 2 ].token == Tokens::STRING_LITERAL 
               ){
               }
            }
}

void _parse_reserved_keyword(Arena* arena, Token* tokens, int offset){
    static_assert(ReservedKeywords::KW_ENUM_LENGHT == 8, "ENUM IS NOT FULLY COVERED");
    Token cur_token = tokens[offset];
    switch (cur_token.keyword)
    {
    case ReservedKeywords::KW_FUNC:
        _parse_func(arena, tokens, offset);
        break;
    }


}


void generate_AST(Arena* arena, Token* tokens){
    for (int i; i < arrlen(tokens); i++){
        Token cur_token = tokens[i];
        switch (cur_token.token)
        {
        case Tokens::RESERVED_KEYWORD:
            _parse_reserved_keyword(arena, tokens, i);
            break;
        }
        
    }
}