#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "methods.h"

int isOp(char c)
{
    return (c == '+' || c == '-' || c == '(' || c == ')' || c == '*' || c == '/' || c == '^');
}

int isDelim(char c)
{
    return (c == ' ' || c == ';');
}

int isInt(char c)
{
    return (c >= 48 && c <= 57);
}

int isUnary(char **arr, int cnt)
{
    if (cnt == 0)
    {
        return 1;
    }

    for (int i = cnt - 1; i >= 0; i--)
    {
        char *element = arr[i];
        char ch = element[0];

        if (isInt(ch))
        {
            return 0;
        }

        if (isLeft(ch))
        {
            return 1;
        }

        if (ch == '^')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

int isNumber(char *token)
{
    int len = strlen(token);
    for (int i = 0; i < len; i++)
    {
        if (isInt(token[i]))
        {
            return 1;
        }
    }
    return 0;
}

char **tokenize(char *input, int *tokenCnt)
{

    int len = strlen(input);
    char **tokens = malloc(sizeof(char *) * len);

    int end = 0;
    int begin = 0;
    char curr = input[begin];

    int unaryMinus = 0;
    int negativeCnt = 0;

    while (end < len)
    {

        if (!isInt(curr))
        {

            if (begin < end)
            {

                int tokenLen = end - begin + unaryMinus;
                char temp[tokenLen];
                strncpy(temp, input + begin, tokenLen);

                char *token = malloc(tokenLen + 1);

                if (unaryMinus)
                {
                    token[0] = '-';
                }

                strncat(token, temp, tokenLen);
                token[tokenLen] = '\0';

                printf("Token: <%s> at %d\n", token, *tokenCnt);

                tokens[*tokenCnt] = token;
                *tokenCnt += 1;
                unaryMinus = 0;
            }

            if (isOp(curr))
            {
                if (curr == '-')
                {
                    negativeCnt++;
                    if (isUnary(tokens, *tokenCnt))
                    {
                        unaryMinus = !unaryMinus;
                        end++;
                        begin = end;
                        curr = input[end];
                        continue;
                    }
                }
                // because it may begin with a -(...
                //  only distribute -1 when its a unary minus

                else if (curr == '(' && (*tokenCnt > 0 || unaryMinus))
                {
                    int prev = *tokenCnt - 1;
                    if (unaryMinus)
                    {
                        char *token = malloc(2);
                        token[0] = '-';
                        token[1] = '1';
                        tokens[*tokenCnt] = token;
                        printf("Token: <%s> at %d\n", token, *tokenCnt);
                        *tokenCnt += 1;
                        char *op = malloc(1);
                        op[0] = '*';
                        tokens[*tokenCnt] = op;
                        printf("Token: <%s> at %d\n", op, *tokenCnt);
                        *tokenCnt += 1;
                        unaryMinus = 0;
                    }
                    else if (isNumber(tokens[prev]))
                    {
                        char *token = malloc(1);
                        token[0] = '*';
                        tokens[*tokenCnt] = token;
                        printf("Token: <%s> at %d\n", token, *tokenCnt);
                        *tokenCnt += 1;
                    }

                    unaryMinus = 0;
                }

                char *op = malloc(1);
                op[0] = curr;
                op[1] = '\0';
                printf("Token: <%s> at %d\n", op, *tokenCnt);

                tokens[*tokenCnt] = op;
                *tokenCnt += 1;
            }
            else if (!isDelim(curr))
            {
                printf("symbol %c not recognized!\n", curr);
            }

            begin = end + 1;
        }

        end++;
        curr = input[end];
    }

    return tokens;
}