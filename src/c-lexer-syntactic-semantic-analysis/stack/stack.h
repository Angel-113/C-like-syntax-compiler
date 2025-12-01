#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include "token/token.h"

typedef struct TokenStack {
    Token (*top)(void);
    void (*push)(Token);
    Token (*pop)(void);
    bool (*is_empty)(void);
    unsigned int (*size)(void);
    void (*destroy)(void);
} TokenStack;

extern TokenStack InitStack ( void );

#endif //STACK_H
