#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"
#include "stack.h"

int getPrec(char c) {
    if (c == '(' || c == ')' || c == '^') {
        return 3;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    if (c == '+' || c == '-') {
        return 1;
    }

    return -1;
}

int isLeft(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

char** postfix(char** tokens, int len, int* postLen) {
    char** rpn = malloc(sizeof(char*) * len);
    Stack stack = initStack(len);
    int idx = 0;

    for (int i = 0; i < len; i++) {
        char* token = tokens[i];
        int tokenLen = strlen(token);

        char op = token[0];

        if (isOp(op) == 1 && tokenLen == 1) {
            
            char top = peek(&stack)[0];

            if (op == ')') {

                while (top != '(' && top != ' ') {
                    rpn[idx] = peek(&stack);
                    pop(&stack);
                    top = peek(&stack)[0];
                    idx++;
                }
                
                pop(&stack);
                continue;
            }

            if (isLeft(op)) {

                while (getPrec(top) >= getPrec(op) && top != '(') {
                    rpn[idx] = peek(&stack);
                    pop(&stack);
                    top = peek(&stack)[0];
                    idx++;
                }
            }
            
            push(&stack, token);
        }
        else {
            rpn[idx] = token;
            idx++;
        }

    }

    while (strcmp(peek(&stack), " ") != 0) {
        rpn[idx] = peek(&stack);
        pop(&stack);
        idx++;
    }
    
    *postLen = idx;
    free(stack.arr);
    return rpn;
}