cmake_minimum_required (VERSION 3.29)
project (grammar C)

set (CMAKE_C_STANDARD 11)

include_directories (include src/c-lexer-syntactic-semantic-analysis src/test)

add_executable ( grammar
        src/main.c
        src/c-lexer-syntactic-semantic-analysis/lexer.c
        src/c-lexer-syntactic-semantic-analysis/lexer.h
        src/c-lexer-syntactic-semantic-analysis/token/token.c
        src/c-lexer-syntactic-semantic-analysis/token/token.h
        include/base.h
        src/c-lexer-syntactic-semantic-analysis/scanner/scanner.c
        src/c-lexer-syntactic-semantic-analysis/scanner/scanner.h
        src/c-lexer-syntactic-semantic-analysis/keywords/keywords.c
        src/c-lexer-syntactic-semantic-analysis/keywords/keywords.h
        src/test/lexer_test.c
        include/base.c
        src/test/parser_test.c
        src/test/test.h
)
