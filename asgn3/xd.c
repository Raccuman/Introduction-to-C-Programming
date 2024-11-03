// this is the main program where we write our function xd. should have a read loop and a printing loop :)
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
///////////////////////////////////////////////////////////////////////////////////////////////
    int fd;
    void *buff_array[16]; // our buffer
    /* check if argc is one or 2?? if its one they didnt give a file name, if its 2 they gave a file name,
    if three or greator return as an error?? */
    // if there is more than one input throw error
    if (argc == 1) {
        fd = 0; // if you input 0 in the file section, it reads the lext input on the comand line ad tha file contents
        //and other junk
    } else if (argc == 2) {
        fd = open(argv[1], O_RDONLY);
        // and other junk
    } else {
        return 1;
        //throw error cause you cant have more than 2 inputs :3
    }
    // checking for correct file name input, if invalid throw error
    if (fd == -1) {
        return 1;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////

    size_t n = 16; // this is to see how many bytes you should read in
    size_t are_we_there_yet; // keeps track of how many bytes have been read
    size_t read_zero_checker = 10;
    int lefthand_hex_index = 0;
    int return_flag = 0;
    char new_array[16];
    int array_length = 0;
    int remaining_bytes;

    ///////////////////////////// printing lines output loop /////////////////////////////////////////

    while (read_zero_checker != 0) {

        // 16 byte buff filler loop. if it runs out of file before it hits 16 bytes, it just breaks
        are_we_there_yet = 0;
        while (are_we_there_yet < 16) {
            n = n - are_we_there_yet;
            read_zero_checker = (size_t) (read(fd, buff_array, n));
            are_we_there_yet += read_zero_checker;
            if (read_zero_checker <= 0) {
                break;
            }
        }
///////////////////////////////////////////////////////////////////////////////////////////////////////
        // cant just straight up use buff_array, we need to copy to a new array
        array_length = 0;
        for (int l = 0; l < (int) are_we_there_yet; l++) {
            new_array[l] = ((char *) buff_array)[l];
            array_length += 1;
        }
///////////////////////////////////////////////////////////////////////////////////////////////////
        // printing out an indivigual line with formatting loop thingy?? string formatting

        //these 2 lines print the lefthand index
        if (array_length != 0) {
            printf("%08x", lefthand_hex_index);
            printf(": ");
        }
        // regular character to hex print for the long middle lines
        for (int i = 0; i < (int) are_we_there_yet; i++) {
            if ((int) new_array[i] == 10) {
                printf("0a");
            } else {
                printf("%02hhx", new_array[i]);
            }
            // print a space after 4 hex didgits have been printed
            if ((i % 2) == 1) {
                printf(" ");
            }
        }
        // this next set is for a potential final line that did not have 16 bytes of info. it will just fill with blanks
        
        if (array_length < 16 && array_length != 0) {
            return_flag += 1;

            remaining_bytes = (16 - array_length) * 2 + ((16 - array_length) / 2 - 1);
            for (int j = 0; j < remaining_bytes; j++) {
                printf(" "); // where hex values would go (4 spaces)
            }
            if (array_length % 2 == 1) {
                printf(" ");
                printf(" ");
            }
            if (array_length % 2 == 0) {
                printf(" ");
            }
        }

        // there are 2 spaces at the end of the long hex line instead of just 1
        if (array_length != 0) {
            printf(" ");
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        // print the end of line character phrase
        for (int k = 0; k < (int) are_we_there_yet; k++) {
            // acceptable characters to print. if not print .
            if ((int) (new_array[k]) >= 32 && (int) (new_array[k]) <= 126) {
                printf("%c", new_array[k]);
            } else {
                printf(".");
            }
        }
        if (array_length != 0) {
            printf("\n");
        }

        // clear the buffer before the loop restarts to the top
        if (return_flag > 0) {
            return 0;
        }
        lefthand_hex_index += 16;
    }
}
