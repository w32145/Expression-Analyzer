#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "macros.h"

int main()
{
    printf("program ran successfully\n");

    char in[INPUT_LEN];
    printf("enter expression: ");
    fgets(in, sizeof in, stdin);
    int last = strlen(in) - 1;
    in[last] = ';';

    int len = 0;
    char **tokens = tokenize(in, &len);

    printf("\nToken count: %d\n", len);

    // char** rpn = postfix(ex, len);
    // printf("\nanswer: %d", solve(rpn, len));

    for (int i = 0; i < len; i++)
    {
        printf("Index %d: %s\n", i, tokens[i]);
        free(tokens[i]);
    }

    free(tokens);
    return 0;
}