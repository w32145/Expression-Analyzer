#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "methods.h"

int getPrec(char c)
{
    if (c == '(' || c == ')' || c == '^')
    {
        return 3;
    }
    if (c == '*' || c == '/')
    {
        return 2;
    }
    if (c == '+' || c == '-')
    {
        return 1;
    }

    return -1;
}

int isLeft(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

char **postfix(char **tokens, int len, int *postLen)
{
    char **rpn = malloc(sizeof(char *) * len);
    char stack[len];
    int si = 0;

    for (int i = 0; i < len; i++)
    {
        char *token = tokens[i];
        int tokenLen = strlen(token);

        char op = token[0];

        if (isOp(op) == 1 && tokenLen == 1)
        {

            char top;
            if (si > 0)
            {
                top = stack[si - 1];
            }
            else
            {
                top = ' ';
            }

            if (op == ')')
            {

                while (top != '(' && si > 0)
                {
                    char *toString = malloc(2);
                    toString[0] = top;
                    toString[1] = '\0';

                    rpn[(*postLen)] = toString;
                    si--;
                    (*postLen)++;

                    if (si > 0)
                    {
                        top = stack[si - 1];
                    }
                }

                if (si > 0)
                {
                    si--;
                }
                continue;
            }

            if (isLeft(op))
            {

                while (getPrec(top) >= getPrec(op) && top != '(' && si > 0)
                {
                    top = stack[si - 1];
                    char *toString = malloc(2);
                    toString[0] = top;
                    toString[1] = '\0';
                    rpn[(*postLen)] = toString;

                    si--;
                    (*postLen)++;
                }
            }

            stack[si++] = token[0];
        }
        else
        {
            char *dest = malloc(tokenLen);
            memcpy(dest, token, tokenLen);
            rpn[(*postLen)] = dest;
            (*postLen)++;
        }
    }

    while (si > 0)
    {
        char top = stack[si - 1];
        char *toString = malloc(2);
        toString[0] = top;
        toString[1] = '\0';
        rpn[(*postLen)] = toString;
        si--;
        (*postLen)++;
    }

    return rpn;
}