#include "names.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // #####################################  basic set up of (pre game)   #####################################################################
    typedef enum { DOT, LEFT, CENTER, RIGHT } Position;
    const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

    // basic user settings (pre game), number of players set up. TRY MESSING WITH THS LATER
    int num_players = 3;
    printf("Number of players (3 to 10)? ");
    int scanf_result = scanf("%d", &num_players);
    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    // basic user settings (pre game), random seed choice set up
    unsigned seed = 4823;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    // not sure what exactly a valid seed is or what is consists of. might need more if statements to check this...
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    }
    srandom(seed);

    // Basic chip set up for users, each start out with three chips (defining arrays) (pregame)
    // funky initialisation to get past not being able to use a variable to determine size of array

    int chips[num_players];
    for (int i = 0; i < num_players; i++) {
        chips[i] = 3;
    }

    // ########## filler to stop error ##############
    int filler_var = die[0];
    filler_var = filler_var + filler_var;
    // r = (rand() % (max + 1 - min)) + min      generates numbers withing the range of max and min for dice rolling

    //################################### ACTUAL GAME CODE #######################################################################################
    int current_player = 0;
    int last_index = num_players - 1;
    int winner_checker = 0;
    int potential_winning_index = 0;
    int dice_roll = 0;
    int flag = 0;
    int i = num_players; // for winner checker for loop
    int random_num = 0;
    int counter = 3;
    int borf = 0;

    for (;;) { // game in theory can go forever so rounds loop forever
        // winner checker block
        borf = 0;
        winner_checker = 0;
        potential_winning_index = 0;
        for (i = num_players - 1; i >= 0; i = i - 1) {
            if (chips[i] > 0) {
                winner_checker += 1;
                potential_winning_index = i;
            }
        }
        if (winner_checker <= 1) {
            // winning game and end game print statement
            printf("%s", player_name[potential_winning_index]);
            printf(" won!");
            printf("\n");
            return 0;
        }

        // is this the last or first player? helpfull to know for chip passing and index resseting
        if (current_player == last_index) {
            flag = 1;
        } else if (current_player == 0) {
            flag = 2;
        } else if (chips[current_player] == 0) {
            flag = 3;
        } else {
            flag = 0;
        }

        // cannot roll more than 3 times
        if (chips[current_player] > 3) {
            counter = 3;
        } else {
            counter = chips[current_player];
        }

        // reroll equal to number of chips
        for (int j = counter; j > 0; j -= 1) {
            borf = 1;
            if (flag == 3) { // if you have 0 chips, break
                break;
            }
            random_num = rand();
            if (chips[current_player] > 0) {
                dice_roll = (random_num % (5 + 1 - 0));
                if (dice_roll < 3) {
                    // nothing happend if dot is rolled, then print the current chip count
                    printf("");
                } else if (dice_roll < 4) {
                    // check flag, pass a chip to the next player, print current chip count
                    if (flag == 1) {
                        chips[0] = chips[0] + 1;
                        chips[current_player] = chips[current_player] - 1;
                    } else {
                        chips[current_player + 1] = chips[current_player + 1] + 1;
                        chips[current_player] = chips[current_player] - 1;
                    }
                } else if (dice_roll < 5) {
                    // remove a chip, no passing, print current chip count
                    chips[current_player] = chips[current_player] - 1;
                } else {
                    // check flag, pass a chip to the previous player, print current chip count
                    if (flag == 2) {
                        chips[last_index] = chips[last_index] + 1;
                        chips[current_player] = chips[current_player] - 1;
                    } else {
                        chips[current_player - 1] = chips[current_player - 1] + 1;
                        chips[current_player] = chips[current_player] - 1;
                    }
                }
            } else {
                // just print that the player had no chips
                printf("%s", player_name[current_player]);
                printf(": ends her turn with ");
                printf("%d", chips[current_player]);
                printf("\n");
                break;
            }
        }
        if (chips[current_player] != 0) {
            printf("%s", player_name[current_player]);
            printf(": ends her turn with ");
            printf("%d", chips[current_player]);
            printf("\n");
        } else if (borf == 1) {
            printf("%s", player_name[current_player]);
            printf(": ends her turn with ");
            printf("%d", chips[current_player]);
            printf("\n");
        }

        //is this the last index? if so, reset index. if not, move on to next player.
        if (flag == 1) {
            current_player = 0;
        } else {
            current_player += 1;
        }
    }

    // links:
    // https://stackoverflow.com/questions/2427336/why-cant-i-create-an-array-with-size-determined-by-a-global-variable#:~:text=If%20you%20want%20to%20create,make%20the%20size%20a%20constant.&text=In%20pre%2DC99%20standard%20compilers,constant%20instead%20of%20a%20variable.
    // https://www.geeksforgeeks.org/c-arrays/

    return 0;
}
