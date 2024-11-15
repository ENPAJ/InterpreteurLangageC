cmake_minimum_required(VERSION 3.10)
project(mon_interpreteur C)

set(CMAKE_C_STANDARD 99)

add_executable(mon_interpreteur main.c
        eval.c
        ast.c
        Variable.c
        lexer.c
        parser.c
        interpreter.c
        ast.h
        eval.h
        interpreter.h
        lexer.h
        parser.h
        variable.h
        tools.h
        tools.c
)
