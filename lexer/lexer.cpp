#include <iostream>
#define DOUBLE_QUOT 34
#include "lexer.h"
#include "../stb_ds.h"
#include "../arena_allocator.h"


bool _check_if_number(char c){
    if (c >= 48 && c <=57){
        return true;
    }
    return false;
}

bool _check_if_char(char c){
    if (c >= 97 && c <= 122 || c >= 65 && c <= 90){
        return true;
    }
    return false;
}


int _get_full_number(char* program, int program_lenght, int parse_offset){
    int offset = 0;

    while(true){
        if (parse_offset + offset +1 > program_lenght){
            return offset;
        }

        char cur_char = program[parse_offset+offset];

    
        if (_check_if_number(cur_char) || cur_char  == '.'){
            offset++;
        } else {
            return offset;
        }
    }
}


int _get_full_string(char* program, int program_lenght, int parse_offset){
    int offset = 0;
    bool isFirst = true;

    while(true){
        if (parse_offset + offset +1 > program_lenght){
            return offset;
        }
        
        if (isFirst){
            offset++;
            isFirst = false;
        }

        char cur_char = program[parse_offset+offset];

    
        if (cur_char != DOUBLE_QUOT){
            offset++;
        } else {
            offset++;
            return offset;
        }
    }

}


int _get_full_char_seq(char* program, int program_lenght, int parse_offset){
    int offset = 0;
    bool isFirst = true;

    while(true){
        if (parse_offset + offset +1 > program_lenght){
            return offset;
        }

        char cur_char = program[parse_offset+offset];
        if (isFirst){
            offset++;
            isFirst = false;
            continue;
        }
    
        if (_check_if_char(cur_char) || _check_if_number(cur_char) || cur_char == '_'){
            offset++;
        } else {
            return offset;
        }
    }
}




ReservedKeywords _check_if_reserved_keyword(char* char_seq){
    static_assert(ReservedKeywords::KW_ENUM_LENGHT == 8, "ENUM IS NO FULLY COVERED");
    switch (char_seq[0])
    {
    case 'f':
        if (strcmp(char_seq, "fun") == 0){
            return ReservedKeywords::KW_FUNC;
        }

        else if (strcmp(char_seq, "false") == 0){
            return ReservedKeywords::KW_FALSE;
        }
        return  ReservedKeywords::KW_ILLIGAL;
        break;

    case 't':
        if (strcmp(char_seq, "true") == 0){
            return ReservedKeywords::KW_TRUE;
        }
        return ReservedKeywords::KW_ILLIGAL;
        break;

    case 'e':
        if (strcmp(char_seq, "else") == 0){
            return ReservedKeywords::KW_ELSE;
        }
        return ReservedKeywords::KW_ILLIGAL;
        break;

    case 'b':
        if (strcmp(char_seq, "break") == 0){
            return ReservedKeywords::KW_ILLIGAL;
        }
        return ReservedKeywords::KW_ILLIGAL;
        break;

    case 'r':
        if (strcmp(char_seq, "return") == 0){
            return ReservedKeywords::KW_RETURN;
        }
        return ReservedKeywords::KW_ILLIGAL;
        break;
    }

    return KW_ILLIGAL;
}


void lex(Arena* arena, char* program, int program_lenght, Token* program_tokens){
    static_assert(Tokens::ENUM_LENGHT == 16, "ENUM IS NOT FULLY COVERED");
    int cur_line = 1;
    
    for (int i = 0; i < program_lenght; i++){
        char cur_sign = program[i];
        Token token;
        token.line = cur_line;
        
        switch (cur_sign)
        {
        case '+':
            token.token = Tokens::PLUS;
            arrput(program_tokens, token);
            break;

        case '*':
            token.token = Tokens::MULT;
            arrput(program_tokens, token);
            break;

        case '=':
            token.token = Tokens::ASSIGN;
            arrput(program_tokens, token);
            break;

        case '-':
            token.token = Tokens::MINUS;
            arrput(program_tokens, token);
            break;

        case ',':
            token.token = Tokens::COMMA;
            arrput(program_tokens, token);
            break;

        case '{':
            token.token = Tokens::CUR_BRAC_OPEN;
            arrput(program_tokens, token);
            break;

        case '}':
            token.token = Tokens::CUR_BRAC_CLOSE;
            arrput(program_tokens, token);
            break;

        case '(':
            token.token = Tokens::PAR_OPEN;
            arrput(program_tokens, token);
            break;

        case ')':
            token.token = Tokens::PAR_CLOSE;
            arrput(program_tokens, token);
            break;

        case '/':
            token.token = Tokens::SLASH;
            arrput(program_tokens, token);
            break;

        case ';':
            token.token = Tokens::EXP_END;
            arrput(program_tokens, token);
            break;

        case ' ':
            break;

        case '\n':
            cur_line++;
            break;
        default:
            if (_check_if_number(cur_sign)){
                int offset = _get_full_number(program, program_lenght, i);
                char* cont = (char*) arena_malloc(arena, sizeof(char)*offset +1);
                cont+='\0';
                strncpy(cont, program+i,offset);
                token.val = cont;
                token.token = Tokens::NUM_LITERAL;
                arrput(program_tokens, token);
                i+=offset-1;
            }
            if (_check_if_char(cur_sign)){
                int offset = _get_full_char_seq(program, program_lenght, i);
                char* cont = (char*) arena_malloc(arena, sizeof(char)*offset+1);
                cont+='\0';
                strncpy(cont, program+i,offset);
                token.val = cont;
                ReservedKeywords reserved = _check_if_reserved_keyword(cont);
                if (reserved == ReservedKeywords::KW_ILLIGAL){
                    token.token = Tokens::CHAR;
                    arrput(program_tokens, token);
                } else {
                    token.token = Tokens::RESERVED_KEYWORD;
                    token.keyword = reserved;
                    arrput(program_tokens, token);
                }
                i+=offset-1;
            }

            if (cur_sign == DOUBLE_QUOT){
                token.token = Tokens::STRING_LITERAL;
                int offset = _get_full_string(program, program_lenght, i);
                char* cont = (char*) arena_malloc(arena, sizeof(char)*offset);
                strncpy(cont, program+i,offset);
                token.val = cont;
                arrput(program_tokens, token);
                i+=offset-1;
            }
            break;
        }
    }
    
}


void print_keyword(int keyword){
    static_assert(ReservedKeywords::KW_ENUM_LENGHT == 8, "ENUM IS NOT FULLY COVERED");

    switch (keyword)
    {
    case ReservedKeywords::KW_BREAK:
        std::cout << "BREAK\n";
        break;

    case ReservedKeywords::KW_IF:
        std::cout << "IF\n";
        break;

    case ReservedKeywords::KW_ELSE:
        std::cout << "ELSE\n";
        break;

    case ReservedKeywords::KW_TRUE:
        std::cout << "TRUE\n";
        break;

    case ReservedKeywords::KW_FALSE:
        std::cout << "FALSE\n";
        break;

    case ReservedKeywords::KW_FUNC:
        std::cout << "FUNCTION\n";
        break;
    
    case ReservedKeywords::KW_RETURN:
        std::cout << "RETURN STATEMENT\n";
        break;

    case ReservedKeywords::KW_ILLIGAL:
        std::cout << "ILLIGAL\n";
        break;
    }
}

void print_lexed(Token* program_tokens){
    static_assert(Tokens::ENUM_LENGHT == 16, "ENUM IS NOT FULLY COVERED");
    for (int i = 0; i< arrlen(program_tokens); i++){
        Token cur_token = program_tokens[i];
        std::cout << cur_token.line << ": ";
        switch (cur_token.token)
        {
        case Tokens::MULT:
            std::cout << "MULT\n";
            break;

        case Tokens::PLUS:
            std::cout << "PLUS\n";
            break;

        case Tokens::ASSIGN:
            std::cout << "ASSIGN\n";
            break;

        case Tokens::EXP_END:
            std::cout << "EXP END\n";
            break;

        case Tokens::SLASH:
            std::cout << "SLASH\n";
            break;

        case Tokens::MINUS:
            std::cout << "MUNUS\n";
            break;
        
        case Tokens::STRING_LITERAL:
            std::cout << "STRING:" <<  cur_token.val << "\n";
            break;

        case Tokens::PAR_OPEN:
            std::cout << "PAR OPEN\n";
            break;

        case Tokens::PAR_CLOSE:
            std::cout << "PAR CLOSE\n";
            break;

        case Tokens::CUR_BRAC_OPEN:
            std::cout << "CUR BRAC OPEN\n";
            break;

        case Tokens::CUR_BRAC_CLOSE:
            std::cout << "CUR BRAC CLOSE\n";
            break;

        case Tokens::COMMA:
            std::cout << "COMMA\n";
            break;

        case Tokens::NUM_LITERAL:
            std::cout << "NUM LITERAL:" << cur_token.val << "\n";
            break;

        case Tokens::CHAR:
            std::cout << "CHAR_SEQ:" << cur_token.val << "\n";
            break;

        case Tokens::ILLIGALL:
            std::cout << "ILLIGAL\n";
            break;

        case Tokens::RESERVED_KEYWORD:
            std::cout << "KEYWORD: ";
            print_keyword(cur_token.keyword);
            break;
        }
    }
}