#include "stdio.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "lexer/lexer.h"
#include "stb_ds.h"
#include "arena_allocator.h"
#include "ast/ast.h"



int main(){
    // Arena* r=  create_arena(8*1024*1024);
    Token* program_tokens = NULL;

    std::string program;


    std::ifstream program_file ("main.ori");

    std::string linebuffer;
    while (std::getline(program_file, linebuffer)){
        program.append(linebuffer.append("\n"));
    }


    char* program_char_p = const_cast<char*>(program.c_str());
    arrsetcap(program_tokens, program.length());
    Arena* arena = create_arena(8*1024*1024);
    lex(arena, program_char_p, program.length(), program_tokens);
    print_lexed(program_tokens);
    std::cout << " \n\n";
    generate_AST(arena, program_tokens);

    return 0;

    // std::string pg1 = "\"hello world!\"\n";

    // char* pg_p1= const_cast<char*>(pg1.c_str());


    // int end1 = get_full_string(pg_p1, pg1.length(), 0);
    // char * answ = (char*)malloc(sizeof(char) * end1);
    // strncpy(answ, pg_p1,end1);

    

    // std::cout << answ << std::endl;
    // return 0;
}

