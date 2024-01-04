#pragma once

/*!
 * \brief Enumerates different token types for lexical analysis.
 *
 * This enumeration represents various token types used during lexical analysis.
 * It includes identifiers, variable types, values, operators, delimiters, and special tokens.
 */
typedef enum
{
    ID,            /**< Identifier (variable name) - 0 */
    V_TYPE,        /**< Variable type - 1 */
    VAL,           /**< Value (Variable value) - 2 */
    T_VAL,         /**< Text variable value (char/string) - 3 */
    KEYWORD,       /**< Keywords (e.g., PRINT, IF, WHILE) - 4 */
    ARITH_OP,      /**< Arithmetic operators (e.g., +, -) - 5 */
    LOGIC_OP,      /**< Logic operators (e.g., ||, &&) - 6 */
    RELAT_OP,      /**< Relational operators (e.g., >, ==) - 7 */
    ASSIGN,        /**< Assignment operator (=) - 8 */
    O_BRACKET,     /**< Opening bracket { - 9 */
    C_BRACKET,     /**< Closing bracket } - 10 */
    LIST_B,        /**< Begining of the list [ - 11 */
    LIST_E,        /**< Ending of the list ] - 12 */
    O_PAREN,       /**< Opening parenthesis ( - 13 */
    C_PAREN,       /**< Closing parenthesis ) - 14 */
    R_TYPE,        /**< Return type -> - 15 */
    COMMA,         /**< Comma , - 16 */
    SEMI,          /**< Semicolon ; - 17 */
    INVALID,       /**< Invalid token - 18 */
    TOKEN_Newline, /**< Newline token - 19 */
    TOKEN_EOF      /**< End of file token - 20 */
} TokenType;

/*!
 * \brief Represents a token with a TokenType and a value.
 *
 * This structure defines a token containing a TokenType indicating its type
 * and a character array to hold its value.
 */
typedef struct
{
    TokenType type; /**< Type of the token */
    char value[80]; /**< Value of the token */
} Token;

/*!
 * \brief Performs lexical analysis on the input text to generate tokens.
 *
 * This function performs lexical analysis on the given input text and generates tokens.
 * It returns an array of tokens and updates the 'num_tokens' variable with the total number of tokens found.
 * The caller is responsible for freeing the memory allocated for the tokens.
 *
 * @param input_text The input text to be analyzed.
 * @param num_tokens Pointer to an integer to hold the number of tokens found.
 * @return Pointer to an array of tokens generated from the input text.
 */
Token *lexer(const char *input_text, int *num_tokens);

/*!
 * \brief Prints the tokens to the standard output.
 *
 * This function prints the provided array of tokens to the standard output.
 * It takes an array of tokens and the number of tokens to be printed.
 *
 * @param tokens Array of tokens to be printed.
 * @param num_tokens Number of tokens in the 'tokens' array.
 */
void print_tokens(Token *tokens, int num_tokens);
