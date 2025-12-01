# Lexical, Syntactic and Semantic Analysis for a C-like syntax language

This section was written while reading the *Scanning* chapter from *Crafting Interpreters*:
https://craftinginterpreters.com/scanning.html. I strongly recommend taking a look on it. 

**Important note**: My english writing skills are not good enough to make documentation. 
Feel free to ask if you don't understand any of the topics in this section.

## What's a lexical analyzer?

A lexical analyzer is a *phase* of a *compilation* or *interpretation* process. 
It receives a source code file and returns an associated list of *tokens*. Those
*tokens* are every single character, combination of characters or keywords that are
going to be accepted by the language.

For example: `"int", "var_name", "1", "if", "(", "?", "!"`

There are 5 types of tokens: 

- Single character tokens: like `LEFT_PARENTHESIS : "("`.
- Two-character tokens: like increment by one `PLUS_PLUS : "++"`.
- Literals: actual values like strings, number or character literals. `NUMBER: "1", STRING: "Hello World\n", CHARACTER: '\n'`.
- Keywords: all the language keywords. `IF: "if", WHILE: "while"`.
- Identifier: every valid combination of characters that are not any of the previous ones. `IDENTIFIER: "val_name"`.

## What's a syntactic analyzer?

## What's a semantic analyzer?

## Structs used in this compiler phase

### Scanner 

The Scanner files are made to read a file and to put it into a `char* buffer`. It defines a struct: 

```` C
typedef struct Scanner {
    char (*peek)(void);
    bool (*match)(char);
    char (*advance)(void);
    char (*next)(void);
    unsigned int (*get_line_number)(void);
    void (*destroy)(void);
} Scanner; 
````

As you could see, there are only functions into it. And every function and affected variables
are into the implementation file: `scanner.c`.

- `peek()` returns the character in the current position of the buffer.
- `match(char expected)` a conditional advance; if the current position's next character matches `expected` and it's different to `'\0'` then the `scanner` advance and return a `true`, otherwise just return `false`.
- `advance()` consume the character and returns the next to it.
- `next()` just returns the next character.
- `get_line_number()` just returns the line number the scanner is currently in.
- `destroy()` free's the dynamically allocated memory in buffer. 

### Token

