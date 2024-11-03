// this impliments the stack
#include "stack.h"

#include "messages.h"

#include <stdio.h>

int stack_size = 0;
double stack[STACK_CAPACITY] = { 0 };

bool stack_push(double item) {
    if (stack_size == STACK_CAPACITY) {
        fprintf(stderr, ERROR_NO_SPACE, item);
        return false;
    } else {
        stack[stack_size] = item;
        stack_size += 1;
        return true;
    }
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return false;
        //finish the thing!
    } else {
        item[0] = stack[stack_size - 1]; // copies over the first item in the stack??
        return true;
    }
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;
    } else {
        item[0] = stack[stack_size - 1];
        stack_size -= 1;
        return true;
    }
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    // if there is nothing in the stack dont print
    if (stack_size == 0) {
        return;
    }
    // print the first element with 10 decimal places
    printf("%.10f", stack[0]);
    // print the remaining elements (if any), with a space before each one
    for (int i = 1; i < stack_size; i++) {
        printf(" %.10f", stack[i]);
    }
}
