#ifndef METHODS_H
#define METHODS_H
char** tokenize(char* input, int* tokenCnt);
char** postfix(char** tokens, int len, int* postLen);
int isNumber(char* token);
int isOp(char c);
#endif