#include "badhash.h"
#include "dictwords.h"
#include "hash.h"

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    void *buff_array[5000];
    Hashtable *my_table = hash_create();
    if (fd == -1) {
        return 1;
    }
    if (argc > 3) {
        return 1;
    }
    // max read in is set to 5000, will I need more?
    size_t n = 5000; // this is to see how many bytes you should read in
    size_t are_we_there_yet = 0; // keeps track of how many bytes have been read
    size_t read_zero_checker = 10;
    char new_array[5000];
    int array_length = 0;
    while (are_we_there_yet < 5000) {
        n = n - are_we_there_yet;
        read_zero_checker = (size_t) (read(fd, buff_array, n));
        are_we_there_yet += read_zero_checker;
        if (read_zero_checker <= 0) {
            break;
        }
    }
    for (int l = 0; l < (int) are_we_there_yet; l++) {
        new_array[l] = ((char *) buff_array)[l];
        array_length += 1;
    }
    /////////////////////////// above is reading stuff //////////////////////////////////
    int i = 0;
    char liner[255] = "blank";
    while (i < array_length) {
        if (new_array[i] == '\n') {
            hash_put(my_table, liner, 0);
        } else {
            append(liner, 1, new_array[1]); // a character is 1 byte long
        }
    }

    hash_destroy(&my_table);
    return 0;
}
