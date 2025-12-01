#include "stack.h"

static unsigned int __TokenStackSize = 0;

static typedef struct NodeTokenStack {
    Token token;
    struct NodeTokenStack *next;
    struct NodeTokenStack *prev;
} NodeTokenStack;

NodeTokenStack *stack = NULL;

Token top ( void ) { return stack->token; }

void push ( const Token token ) {
    NodeTokenStack* node = ( NodeTokenStack* ) malloc ( sizeof ( NodeTokenStack ) );
    node->token = token;
    stack->next = node;
    node->prev = stack;
    stack = stack->next;
    __TokenStackSize++;
}

Token pop ( void ) {
    const Token token = stack->token;
    NodeTokenStack* node = stack;
    stack = stack->prev;
    free( node );
    __TokenStackSize--;
    return token;
}

bool is_empty ( void ) { return __TokenStackSize == 0; }
unsigned int size ( void ) { return __TokenStackSize; }

void destroy ( void ) {
    NodeTokenStack* node = stack;
    while ( node ) {
        NodeTokenStack* aux = node;
        node = node->prev;
        free( aux );
    }
    __TokenStackSize = 0;
}

TokenStack InitTokenStack ( void ) {
    return (TokenStack) {
        &top,
        &push,
        &pop,
        &is_empty,
        &size,
        &destroy,
    };
}