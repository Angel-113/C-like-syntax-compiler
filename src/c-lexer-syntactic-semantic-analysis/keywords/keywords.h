#ifndef GRAMMAR_KEYWORDS_H
#define GRAMMAR_KEYWORDS_H

#include "base.h"
#include "../token/token.h"

typedef struct Bucket {
    char lBuffer[100];
    TokenType type;
} Bucket;

typedef struct Map {
    TokenType (*get_token) ( const char*, unsigned int);
} Map;

typedef struct Tuple {
    const char* s;
    unsigned int hash_value;
} Tuple;

extern Map InitMap ( void );

#endif //GRAMMAR_KEYWORDS_H
