#include <stdio.h>
#include <stdlib.h>

#include "methods.h"

int solve(char **rpn, int len)
{
    int numbers[len];
    int idx = 0;

    for (int i = 0; i < len; i++)
    {

        int left = 0;
        int right = 0;
        char op = rpn[i][0];

        if (isOp(op))
        {

            if (idx >= 2)
            {

                right = numbers[idx - 1];
                idx--;
                left = numbers[idx - 1];
                idx--;
            }
            else if (idx == 1)
            {

                right = numbers[idx - 1];
                idx--;
            }
            else
            {
                printf("An operator was encountered but there were no operands\n");
            }

            int x = 0;

            switch (op)
            {
            case '+':
                x = left + right;

                break;

            case '-':
                x = left - right;
                break;

            case '*':
                x = left * right;
                break;

            case '/':
                x = left / right;
            }

            numbers[idx] = x;
            idx++;
        }
        else
        {
            numbers[idx] = atoi(rpn[i]);
            idx++;
        }
    }

    if (idx == 0)
    {
        return numbers[0];
    }

    return numbers[idx - 1];
}