#include <stdlib.h>

#include "stack.h"
#include "macros.h"

Stack initStack(int size) {
    Stack stack;
    stack.arr = malloc(sizeof(char*) * size);
    stack.count = 0;
    return stack;
}

void push(Stack *self, char* item) {
    int end = STACK_SIZE - 1;
    int temp = self -> count;

    if (temp < end) {
        self -> arr[temp] = item;
        self -> count = temp + 1;
    }
    else
    {
        self -> arr[end] = item;
        // prevent overflow
    }
}

int pop(Stack *self) {
    int temp = self -> count;

    if (temp > 0) {
        temp--;
        self -> count = temp;
        return 1;
    }

    return 0;
}

char* peek(Stack *self) {
    int temp = self -> count;

    if (temp == 0) {
        return " ";
    }

    return self -> arr[(temp - 1)];
}