#ifndef METHODS_H
#define METHODS_H
char** tokenize(char* input, int* tokenCnt);
char** postfix(char** tokens, int len, int* postLen);
double solve(char **rpn, int len);
int isNumber(char* token);
int isOp(char c);
int isLeft(char c);
#endif