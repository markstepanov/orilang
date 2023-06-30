#!/bin/bash

set -xe

g++ arena_allocator.cpp ast/ast.cpp lexer/lexer.cpp stb_ds.cpp main.cpp -o main -g