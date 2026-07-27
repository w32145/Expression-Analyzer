#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "methods.h"

double solve(char **rpn, int len)
{
    double numbers[len];
    int idx = 0;

    for (int i = 0; i < len; i++)
    {

        double left = 0;
        double right = 0;
        char op = rpn[i][0];

        if (isOp(op) && !isNumber(rpn[i]))
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

            double x = 0;

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
                break;
            case '^':
                x = pow(left, right);
            }

            numbers[idx] = x;
            idx++;
        }
        else
        {
            numbers[idx] = strtod(rpn[i], NULL);
            idx++;
        }
    }

    if (idx == 0)
    {
        return numbers[0];
    }

    return numbers[idx - 1];
}