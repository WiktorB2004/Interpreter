// TODO(#1): Define syntax (BNF/EBNF)
// TODO(#2): Create lexer
// TODO(#3): Create parser
// TODO(#4): Create iterpreter
// TODO(#5): Test and upgrade

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types
typedef enum
{
    ID,        // Identifier (variable name)
    V_TYPE,    // Variable type
    VAL,       // Value (Variable value)
    KEYWORD,   // Keywords (e.g., SET, PRINT, IF, WHILE)
    ARITH_OP,  // Arithmetic operators (e.g., +, -)
    LOGIC_OP,  // Logic operators (e.g., ||, &&)
    RELAT_OP,  // Relational operators (e.g., >, ==)
    ASSIGN,    // Assignment operator (=)
    O_BRACKET, // Opening bracket {
    C_BRACKET, // Closing bracket }
    LIST_B,    // Begining of the list [
    LIST_E,    // Ending of the list ]
    O_PAREN,   // Opening parenthesis (
    C_PAREN,   // Closing parenthesis )
    R_SPEC,    // Return type specifier ->
    COMMA,     // Comma ,
    SEMI,      // Semicolon ;
    INVALID    // Invalid token
} TokenType;

// Token structure
typedef struct
{
    TokenType type;
    char value[80];
} Token;

Token *lexer(const char *input_text, int *num_tokens)
{
    Token *tokens = malloc(strlen(input_text) * sizeof(Token));
    *num_tokens = 0;
}

int main(void)
{
    // EXAMPLE CODE
    const char *source_code = "SET x = 42;\nPRINT x + 8;\n";
    int num_tokens;

    Token *tokens = lexer(source_code, &num_tokens);

    free(tokens);
    return 0;
}
