#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

// FIXME: Reafactor the code
// FIXME: Test the code - write automated test cases for parser and lexer
// FIXME: Comment the code and document the logic

// Definition of utility functions for lexer

// Check if char is valid ID or VAL
int is_valid_char_token(char ch)
{
    return isalnum(ch) || ch == '_';
}

// A function to help distinguish between T_VAL and VAL
int get_text_value(char ch)
{
    return (ch > 31 && ch < 127 && ch != 34 && ch != 39) || ch == 92;
}

// A function to check if char is valid bracket (Any bracket)
int is_bracket(char ch)
{
    return ch == 123 || ch == 125 || ch == 91 || ch == 93 || ch == 40 || ch == 41;
}

// A function to check if char is valid operator (Logic and Relational operators)
int is_operator(char ch)
{
    return ch == 60 || ch == 61 || ch == 62 || ch == 33 || ch == 38 || ch == 124;
}

// A function to check if string exists in list
int is_string_in_list(const char *target, const char *list[], int listSize)
{
    for (int i = 0; i < listSize; ++i)
    {
        if (strcmp(target, list[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

// LEXER

// Lexer function
Token *lexer(const char *input_text, int *num_tokens)
{
    Token *tokens = malloc(strlen(input_text) * sizeof(Token));
    *num_tokens = 0;
    int is_line_empty;
    const char *types[6] = {"int", "float", "char", "string", "bool", "void"};
    const char *keywords[6] = {"DEF", "IF", "ELSE", "PRINT", "WHILE", "return"};

    while (*input_text)
    {
        // Skip whitespaces and create TOKEN_Newline's
        while (isspace(*input_text))
        {
            if (*input_text == '\n')
            {
                tokens[(*num_tokens)++].type = TOKEN_Newline;
                ++input_text;
            }
            else
            {
                ++input_text;
            }
        }

        // Handle letters only tokens
        if (isalpha(*input_text))
        {
            char buffer[80];
            int i = 0;
            while (is_valid_char_token(*input_text))
            {
                buffer[i++] = *input_text++;
            }
            buffer[i] = '\0';

            // Check if token is one of variable type specifiers (V_TYPE)
            if (is_string_in_list(buffer, types, sizeof(types) / sizeof(types[0])) == 1)
            {
                tokens[*num_tokens].type = V_TYPE;
                strcpy(tokens[*num_tokens].value, buffer);
            }
            // Check if token is KEYWORD
            else if (is_string_in_list(buffer, keywords, sizeof(keywords) / sizeof(keywords[0])) == 1)
            {
                tokens[*num_tokens].type = KEYWORD;
                strcpy(tokens[*num_tokens].value, buffer);
            }
            // The token must be variable identifier (ID)
            else
            {
                tokens[*num_tokens].type = ID;
                strcpy(tokens[*num_tokens].value, buffer);
            }

            (*num_tokens)++;
        }
        // Distinguish strings and chars from other text tokens (T_VAL)
        else if (*input_text == '"' || *input_text == '\'')
        {
            char buffer[80];
            int i = 0;
            buffer[i++] = *input_text++;
            while (get_text_value(*input_text))
            {
                buffer[i++] = *input_text++;
            }
            buffer[i++] = *input_text++;
            buffer[i] = '\0';
            tokens[*num_tokens].type = T_VAL;
            strcpy(tokens[*num_tokens].value, buffer);
            (*num_tokens)++;
        }
        // Handle integer and float tokens (VAL)
        else if (isdigit(*input_text) || *input_text == '.')
        {
            char buffer[80];
            int i = 0;
            while (isdigit(*input_text) || *input_text == '.')
            {
                buffer[i++] = *input_text++;
            }
            buffer[i] = '\0';

            tokens[*num_tokens].type = VAL;
            strcpy(tokens[*num_tokens].value, buffer);
            (*num_tokens)++;
        }
        // Handle all types of brackets (O_*, C_*, LIST_*)
        else if (is_bracket(*input_text))
        {
            switch (*input_text)
            {
            case '{':
                tokens[*num_tokens].type = O_BRACKET;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            case '}':
                tokens[*num_tokens].type = C_BRACKET;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            case '[':
                tokens[*num_tokens].type = LIST_B;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            case ']':
                tokens[*num_tokens].type = LIST_E;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            case '(':
                tokens[*num_tokens].type = O_PAREN;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            case ')':
                tokens[*num_tokens].type = C_PAREN;
                memcpy(tokens[*num_tokens].value, input_text, 1);
                break;
            default:
                break;
            }
            *input_text++;
            (*num_tokens)++;
        }
        // Handle - and -> (ARITH_OP, R_TYPE)
        else if (*input_text == '-')
        {
            tokens[*num_tokens].value[0] = *input_text++;
            if (*input_text == '>')
            {
                tokens[*num_tokens].type = R_TYPE;
                tokens[*num_tokens].value[1] = '>';
                tokens[*num_tokens].value[2] = '\0';
            }
            else
            {
                tokens[*num_tokens].type = ARITH_OP;
                tokens[*num_tokens].value[1] = '\0';
            }
            *input_text++;
            (*num_tokens)++;
        }

        // Handle logical and relational operators (LOGIC_OP, RELAT_O)
        else if (is_operator(*input_text) == 1)
        {
            char buffer[80];
            int i = 0;

            while (is_operator(*input_text) == 1)
            {
                buffer[i++] = *input_text++;
            }
            buffer[i] = '\0';
            if (i == 1 && buffer[0] == '=')
            {
                tokens[*num_tokens].type = ASSIGN;
            }
            else if (buffer[0] == '&' || buffer[0] == '|')
            {
                tokens[*num_tokens].type = LOGIC_OP;
            }
            else
            {
                tokens[*num_tokens].type = RELAT_OP;
            }

            strcpy(tokens[*num_tokens].value, buffer);
            (*num_tokens)++;
        }
        // Handle left tokens
        else
        {
            switch (*input_text)
            {
            case '+':
                tokens[*num_tokens].type = ARITH_OP;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
                break;
            case '*':
                tokens[*num_tokens].type = ARITH_OP;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
                break;
            case '/':
                tokens[*num_tokens].type = ARITH_OP;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
                break;
            case ';':
                tokens[*num_tokens].type = SEMI;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
                break;
            case ',':
                tokens[*num_tokens].type = COMMA;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
                break;
            default:
                // Handle invalid characters or symbols
                tokens[*num_tokens].type = INVALID;
                tokens[*num_tokens].value[0] = *input_text++;
                tokens[*num_tokens].value[1] = '\0';
                (*num_tokens)++;
            }
        }
    }
    tokens[*num_tokens].type = TOKEN_EOF;
    (*num_tokens)++;
    return tokens;
}

// Function to print tokens (for debugging purpose)
void print_tokens(Token *tokens, int num_tokens)
{
    for (int i = 0; i < num_tokens; ++i)
    {
        printf("Token Type: %d, Value: %s\n", tokens[i].type, tokens[i].value);
    }
}