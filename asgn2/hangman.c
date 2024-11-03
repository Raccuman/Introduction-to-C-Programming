#include "hangman_helpers.h"

//////////////////////////////////////////////functions deffinitions ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {
    if (argc > 3) {
        printf("wrong number of arguments\n");
        printf("usage: ./hangman <secret word or phrase>\n");
        printf("if the secret is multiple words, you must quote it\n");
        return 1;
    }
    if (!(validate_secret(argv[1]))) {
        return 1;
    }

    //char test = 'c';
    //bool t = is_lowercase_letter(test);

    int num_loss = 0;
    char eliminated_letters[7]; // you can only guess incorrectly 6 times. 7th is for backslash zero
    eliminated_letters[0] = '\0';
    char given_letter;
    bool good_letter;
    char *ghost_line = ghost_line_generator(argv[1]);
    int win_checker_tally = 0;
    char *secret_phrase = argv[1];
    // secret phrase lenght finder
    int cap = 0;
    while (secret_phrase[cap] != '\0') {
        cap += 1;
    }
    char good_guess[cap + 1];
    int good_guess_index = 0;

    for (;;) {
        // page set up and guess read
        printf("%s", CLEAR_SCREEN);
        printf("%s\n\n", arts[num_loss]); // prints hangman art
        print_phrase_line(ghost_line);
        eliminated_letters_line(eliminated_letters);
        printf("\n");
        given_letter = read_letter(); //takes in the user guess
        good_letter = validate_secret(&given_letter); // makes sure the users letter is a valid one

        if (good_letter == false) {
            printf("program broke");
            break; // what do I do if they enter an invalid character ??
        }

        // is the letter in the secret??
        if (string_contains_character(argv[1], given_letter) == true) {
            // update the phrase line to the character is not visible. replace _ with a
            ////////////////////////////////////////problem area ///////////////////////////////////////////
            good_guess[good_guess_index] = given_letter;
            good_guess_index += 1;
            for (int i = 0; i < cap; i += 1) {
                if (secret_phrase[i] == given_letter) {
                    ghost_line[i] = given_letter;
                } else if (!(is_lowercase_letter(secret_phrase[i]))) {
                    ghost_line[i] = secret_phrase[i];
                } else {
                    ghost_line[i] = '_';
                }
                // has that letter already been revealed??
                for (int j = 0; j <= good_guess_index; j++) {
                    if (secret_phrase[i] == good_guess[j]) {
                        ghost_line[i] = good_guess[j];
                    }
                }
            }
        } else {
            eliminated_letters[num_loss] = given_letter;
            num_loss += 1;
            for (int i = 0; i < cap; i += 1) {
                if (secret_phrase[i] == given_letter) {
                    ghost_line[i] = given_letter;
                } else if (!(is_lowercase_letter(secret_phrase[i]))) {
                    ghost_line[i] = secret_phrase[i];
                } else {
                    ghost_line[i] = '_';
                }
                // has that letter already been revealed??
                for (int j = 0; j <= good_guess_index; j++) {
                    if (secret_phrase[i] == good_guess[j]) {
                        ghost_line[i] = good_guess[j];
                    }
                }
                // lose checker block
                if (num_loss == LOSING_MISTAKE) {
                    // END THE GAME AS A LOSS
                    printf("%s", CLEAR_SCREEN);
                    printf("%s\n", arts[num_loss]); // prints hangman art
                    eliminated_letters_line(eliminated_letters);
                    printf("You lose! The secret phrase was: ");
                    printf("%s\n", secret_phrase);
                    return 0;
                }
                continue;
            }

            // winner checker block
            win_checker_tally = 0;
            for (int i = 0; i < cap; i += 1) {
                if (ghost_line[i] == '_') {
                    win_checker_tally += 1;
                }
            }

            if (win_checker_tally == 0) {
                // win ender block
                printf("You win! The secret phrase was: ");
                printf("%s\n", secret_phrase);
                return 0;
            }
        }
    }
    return 0;
}

// my lament is as follows:
// I am not feeling something strange. A resoluteness.
// Concrete in my desicion I have just made.
// I burned through this assighnment so hard in most of the wrong ways.
// Perhaps I should have listened.
// I need to learn when to give up. 
// I used to keow, but I think i got caught up in the pannic of making it through thirteen scanf
// So know I have given up on this assighnment, in hope I will do better on the next one.
// It is ok to lose sometimes
// you cant win them all 
// I will do better next __time_tI just wish I threw in the towel yesterday.
