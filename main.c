#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "macros.h"

int main()
{
    char in[INPUT_LEN];
    printf("enter expression: ");

    fgets(in, sizeof(in), stdin);
    int last = strlen(in) - 1;
    in[last] = ';';

    printf("Inputted %s\n\n", in);
    printf("Token stream: \n\n");

    int len = 0;
    char** tokens = tokenize(in, &len);

    printf("\nToken count: %d\n", len);

    int postLen = 0;
    char **rpn = postfix(tokens, len, &postLen);

    printf("The postfix is: \n");
    for (int i = 0; i < postLen; i++) {
        printf("%s ", rpn[i]);
    }

    for (int i = 0; i < len; i++) {
        free(tokens[i]);
    }

    free(tokens);
    free(rpn);
}