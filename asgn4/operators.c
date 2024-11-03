// "contains the basic operators in their wrapper functions "?? im thinking + - * /
#include "operators.h"

#include "messages.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// op will be a string input like '+', and that gets translated behind the scenes into operator_add
bool apply_binary_operator(binary_operator_fn op) {
    // basically the same as the next one
    // you need two numbers for binary to work
    if (stack_size < 2) {
        printf(ERROR_BINARY_OPERATOR);
        return false;
    }
    double x;
    double y;
    assert(stack_pop(&y)); // does the pop return stick?
    assert(stack_pop(&x));
    double result = op(x, y);
    // even though there are 2 inputs, there is still 1 result
    assert(stack_push(result));
    return true;
}

bool apply_unary_operator(unary_operator_fn op) {
    // Make sure that the stack is not empty
    if (stack_size < 1) {
        printf(ERROR_UNARY_OPERATOR);
        return false;
    }
    double x;
    // It should be impossible for stack_pop to fail here, since we have checked
    // above that the stack is not empty. The assert() function causes your
    // program to exit if the condition passed is false. It is often useful for
    // "sanity checks" like this: if stack_pop fails, either our assumption that
    // it can't fail was false, or the implementation of stack_pop has a bug.
    // Either way, we'd like to know immediately instead of silently ignoring an
    // error.
    assert(stack_pop(&x));
    // Calculate the value we should push to the stack
    double result = op(x);
    // Similar to above: stack_push should never fail here, because we just
    // popped an element, so we are not increasing the stack size past the size
    // it had originally.
    assert(stack_push(result));
    return true;
}

///////////////////////////////////////////// basic babies /////////////////////////////////////////////////

// does NOT need to be a pointer
double operator_add(double lhs, double rhs) {
    return (lhs + rhs);
}

double operator_sub(double lhs, double rhs) {
    return (lhs - rhs);
}

double operator_mul(double lhs, double rhs) {
    return (lhs * rhs);
}

double operator_div(double lhs, double rhs) {
    return (lhs / rhs);
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
