// TODO(#3): Create parser
// TODO(#4): Create iterpreter
// TODO(#5): Test and upgrade

// FIXME: Refactor the code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/utils/load_code.h"

// MAIN
int main(void)
{
    const char *filename = "./examples/example.wlg";
    if (!filename)
    {
        fprintf(stderr, "Did not find the file\n");
        exit(EXIT_FAILURE);
    }
    char *source_code = get_source_code(filename);
    int num_tokens;

    Token *tokens = lexer(source_code, &num_tokens);

    // printf("\nLEXER \n");
    // print_tokens(tokens, num_tokens);
    // printf("\nPARSER \n");
    ASTNode *ASTree = parse_program(&tokens);
    print_ASTree(ASTree, 0);

    free(source_code);
    free(tokens);
    // free_ASTree(ASTree);
    return 0;
}
