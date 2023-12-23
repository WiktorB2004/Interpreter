#pragma once

typedef enum
{
    ID,            // 0 Identifier (variable name)
    V_TYPE,        // 1 Variable type
    VAL,           // 2 Value (Variable value)
    T_VAL,         // 3 Text variable value (char/string)
    KEYWORD,       // 4 Keywords (e.g., PRINT, IF, WHILE)
    ARITH_OP,      // 5 Arithmetic operators (e.g., +, -)
    LOGIC_OP,      // 6 Logic operators (e.g., ||, &&)
    RELAT_OP,      // 7 Relational operators (e.g., >, ==)
    ASSIGN,        // 8 Assignment operator (=)
    O_BRACKET,     // 9 Opening bracket {
    C_BRACKET,     // 10 Closing bracket }
    LIST_B,        // 11 Begining of the list [
    LIST_E,        // 12 Ending of the list ]
    O_PAREN,       // 13 Opening parenthesis (
    C_PAREN,       // 14 Closing parenthesis )
    R_TYPE,        // 15 Return type ->
    COMMA,         // 16 Comma ,
    SEMI,          // 17 Semicolon ;
    INVALID,       // 18 Invalid token
    TOKEN_Newline, // 19 Newline token
    TOKEN_EOF      // 20 End of file token
} TokenType;

typedef struct
{
    TokenType type;
    char value[80];
} Token;

Token *lexer(const char *input_text, int *num_tokens);
void print_tokens(Token *tokens, int num_tokens);
