#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>

// Test function prototypes
void test_mathlib(void);
void test_messages(void);
void test_operators(void);
void test_stack(void);

int main() {
    printf("Starting tests...\n\n");

    test_mathlib();
    test_messages();
    test_operators();
    test_stack();

    printf("\nAll tests completed.\n");
    return 0;
}

void test_mathlib() {
    printf("Testing Math Library:\n");
    // Example test: sine function
    double sine_result = Sin(M_PI / 6); // Should be 0.5
    printf("Sin(PI/6): Expected = 0.5, Got = %.10f\n", sine_result);

    // Add more mathlib tests (Cos, Tan, Sqrt, Abs) here...
    printf("\n");
}

void test_messages() {
    printf("Testing Messages:\n");
    // Example: Print an error message defined in messages.h
    printf(ERROR_BAD_CHAR, 'x');
    // Add more message tests here...
    printf("\n");
}

void test_operators() {
    printf("Testing Operators:\n");
    // Example test: Addition
    double add_result = operator_add(1, 2); // Should be 3
    printf("1 + 2 = %.10f\n", add_result);

    // Add more operator tests (Subtraction, Multiplication, Division) here...
    printf("\n");
}

void test_stack() {
    printf("Testing Stack:\n");
    // Push and pop test
    stack_push(1.0);
    double item;
    stack_pop(&item);
    printf("Pushed 1.0, Popped: %.10f\n", item);

    // Add more stack tests here...
    printf("\n");
}
