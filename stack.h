#ifndef STACK_H
#define STACK_H

typedef struct
{
    char** arr;
    int count;
} Stack;

Stack initStack(int size);
void push(Stack* self, char* item);
int pop(Stack* self);
char* peek(Stack* self);
#endif