#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (c > 96 && c < 123) {
        return true;
    } else {
        return false;
    }
}

// checks for any invalid characters like 0 or > in secret given by user
bool validate_secret(const char *secret) {
    int s = 0; // current secret character, secret[i]
    for (int i = 0; secret[i] != '\0'; i++) {
        if (i == 257) {
            printf("the secret phrase is over 256 characters.\n");
            return false;
        }
        s = secret[i];
        if (!(s == 32 || s == 45 || s == 39
                || (s < 123
                    && s > 96))) { // if the statement is false, it gets flopped to true so it executes the error stuff
            printf("invalid character: '");
            printf("%c", s);
            printf("'\n");
            printf("the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                   "apostrophies\n");
            return false;
        } else if (s > 47 && s < 58) {
            return false;
        }
    }
    return true;
}

bool string_contains_character(const char *s, char c) {
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == c) {
            return true;
        }
        i += 1;
    }
    return false;
}

char read_letter(void) { // issues
    char input_character;
    char garbage;
    printf("Guess a letter: ");
    scanf("%c%c", &input_character, &garbage);
    return input_character;
}
// whats the dea with pointers, how to you get to the next item in the array with pointers? what is the difference between scanf and stderr
// targets in the make file.
///////////////////////////////////////////////my junk ////////////////////////////////////////////////////////
char *ghost_line_generator(
    char *s) { // s will be the secret phrase inputted by the user at the start
    int i = 0;
    int j = 0;
    // i will be the lenght of the line
    while (s[i] != '\0') {
        i += 1;
    }
    // i is now the lenght +1. ex) abc makes i = 4
    char ghost_line[i];
    while (j < i) {
        if (is_lowercase_letter(s[j])) {
            ghost_line[j] = '_';
        } else {
            ghost_line[j] = s[j]; // - ' ' and ' will appear in the line
        }
        j++;
    }
    ghost_line[i] = '\0';
    char *copy = ghost_line;
    return copy;
}

// prints the phrase line with the ghostline. Ghostline must be updated in the main code
void print_phrase_line(char *s) {
    printf("    Phrase: ");
    int cap = 0;
    while (s[cap] != '\0') {
        cap += 1;
    }
    for (int i = 0; i < cap; i += 1) {
        printf("%c", s[i]);
    }
    printf("\n");
}

//print function for printing updates and begining list of eliminated letters. needs a global eliminated letters array
void eliminated_letters_line(char *s) {
    printf("Eliminated: ");
    for (int i = 0; s[i] != '\0'; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}
