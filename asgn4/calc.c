// this is the main program
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "mh"

int main(int argc, char **argv) {
    int opt;
    bool flag_passed = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'm': flag_passed = true; break;
        case 'h': fprintf(stdout, USAGE, argv[0]); return 0;
        default: fprintf(stderr, USAGE, argv[0]); return 1;
        }
    }
    char line_buff[1024];
    // char *expr = fgets(line_buff, 1024, stdin);

    /////////////////////////////////////////////////////////////////////////////////////
    char *saveptr;
    bool error = false;

    while (true) {
        fprintf(stderr, "> "); // Prompt for input on each iteration
        if (!fgets(line_buff, 1024, stdin) || feof(stdin)) {
            // If fgets fails to read input or EOF is encountered, break out of the loop
            break;
        }
        const char *token = strtok_r(
            line_buff, " \n", &saveptr); // Include newline in delimiters to handle it properly

        while (token != NULL
               && !error) { ////// but what if I said for it to look for a newline character??
            ///////////////////////////////////////////////////////////////////////////////
            double double_filler;
            if (parse_double(token, &double_filler)) {
                if (!(stack_push(double_filler))) {
                    error = true;
                }
            } else {

                switch (token[0]) {

                case '+':
                    if (!(apply_binary_operator(binary_operators['+']))) {
                        error = true;
                    }
                    break;

                case '-':
                    if (!(apply_binary_operator(binary_operators['-']))) {
                        error = true;
                    }
                    break;

                case '/':
                    if (!(apply_binary_operator(binary_operators['/']))) {
                        error = true;
                    }
                    break;

                case '*':
                    if (!(apply_binary_operator(binary_operators['*']))) {
                        error = true;
                    }
                    break;

                case 's':
                    if (flag_passed == true) {
                        if (!(apply_unary_operator(libm_unary_operators['s']))) {
                            error = true;
                        }
                        break;
                    } else {
                        if (!(apply_unary_operator(my_unary_operators['s']))) {
                            error = true;
                        }
                        break;
                    }

                case 'c':
                    if (flag_passed == true) {
                        if (!(apply_unary_operator(libm_unary_operators['c']))) {
                            error = true;
                        }
                        break;
                    } else {
                        if (!(apply_unary_operator(my_unary_operators['c']))) {
                            error = true;
                        }
                        break;
                    }

                case 't':
                    if (flag_passed == true) {
                        if (!(apply_unary_operator(libm_unary_operators['t']))) {
                            error = true;
                        }
                        break;
                    } else {
                        if (!(apply_unary_operator(my_unary_operators['t']))) {
                            error = true;
                        }
                        break;
                    }

                case 'a':
                    if (flag_passed == true) {
                        if (!(apply_unary_operator(libm_unary_operators['a']))) {
                            error = true;
                        }
                        break;
                    } else {
                        if (!(apply_unary_operator(my_unary_operators['a']))) {
                            error = true;
                        }
                        break;
                    }

                case 'r':
                    if (flag_passed == true) {
                        if (!(apply_unary_operator(libm_unary_operators['r']))) {
                            error = true;
                        }
                        break;
                    } else {
                        if (!(apply_unary_operator(my_unary_operators['r']))) {
                            error = true;
                        }
                        break;
                    }

                default: fprintf(stderr, ERROR_BAD_CHAR, token[0]); break;
                }
            }

            ///////////////////////////////////////////////////////////////
            token = strtok_r(NULL, " \n", &saveptr);
        }
        stack_print();
        printf("%c", '\n');
        stack_clear();
        ///////////////////////////////////////////////////////////////////////////////////////
    }
    return 0;
}

//////////////// sources ////////////////////////////
// https://www.geeksforgeeks.org/fgets-gets-c-language/
// https://13s-docs.jessie.id/c/options.html
