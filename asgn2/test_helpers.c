#include "hangman_helpers.h" // not sure if it should be in quotes ??
// this must thoroughly test test all the functions in hangman_helpers.c

int main(void) {
    int error_counter = 0;
    //////////////////////////// is lower case test ////////////////////////////////////////////////////

    if (is_lowercase_letter('a') != true) {
        printf("is_lowercase_letter function did not work properly, did not recognise that a is "
               "lower case, bad!\n");
        error_counter += 1;
    } else if (false != is_lowercase_letter('A')) {
        printf("is_lowercase_letter function did not work properly, did not recognise that A is "
               "not lower case, bad!\n");
        error_counter += 1;
    } else if (true != is_lowercase_letter('z')) {
        printf("is_lowercase_letter function did not work properly, did not recognise that z is "
               "lower case, bad!\n");
        error_counter += 1;
    } else if (true != is_lowercase_letter('f')) {
        printf("is_lowercase_letter function did not work properly, did not recognise that f is "
               "lower case, bad!\n");
        error_counter += 1;
    }

    ///////////////////////////////////////// validate secret test ///////////////////////////////////////////////////////////////////

    char test
        [4]; // Whats the deal with strings. does backslash 0 take up a space in memory? "" means string, auto inserts 0 thing at end.
    test[3] = '\0';
    test[2] = 'a';
    test[1] = 'a';
    test[0] = 'a';
    if (validate_secret(test) == false) {
        printf("validate secret funtion thought good secret was wrong, Bad!\n");
        error_counter += 1;
    }
    test[2] = ' ';
    if (validate_secret(test) == false) {
        printf("validate secret funtion thought good secret was wrong, Bad!\n");
        error_counter += 1;
    }
    test[2] = '0';
    if (validate_secret(test) == true) {
        printf("validate secret funtion thought bad secret was right, let a number slip Bad!\n");
        error_counter += 1;
    }

    /////////////////////////////////////////////// read letter tester //////////////////////////////////////////////////////////////

    // when testing this, only input a, nothing else. test will not work if you do not input a. a nd newline??????
    char read_letter_checker;
    read_letter_checker = read_letter();
    if (read_letter_checker != 'a') {
        printf("read letter did not work properly for whatever reason? a Bad!\n");
        error_counter += 1;
    }

    //////////////////////////////////////////////// string contains character tester /////////////////////////////////////////

    char testing[5] = "aaaa";
    char target = 'c';
    bool contains_checker = string_contains_character(testing, target);
    if (contains_checker == true) {
        printf("string contains character somehow found c in aaaa, Bad!\n");
        error_counter += 1;
    }
    testing[2] = 'c';
    contains_checker = string_contains_character(testing, target);
    if (contains_checker == false) {
        printf("string contains character did not find c in aaca, Bad!\n");
        error_counter += 1;
    }

    /////////////////////////////////////////// total error return //////////////////////////////////////////////////////////
    if (error_counter > 0) {
        printf("%d", error_counter);
        printf(" errors from function testers.\n \n");
        return 1;
    } else {
        printf("Anolzo :3\n");
        return 0;
    }
}
