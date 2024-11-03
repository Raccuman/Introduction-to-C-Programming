#include "bitreader.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    BitReader *my_write = calloc(1, sizeof(BitReader));
    FILE *f = fopen(filename, "rb");
    if (f == 0) {
        return NULL;
        // not quite sure what fopen() returns if it does not work but should not be any of those.
    }
    my_write->underlying_stream = f;
    my_write->byte = 0x00;
    my_write->bit_position = 8;
    return my_write;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    uint8_t one_bit = 0;
    if ((buf)->bit_position > 7) {
        int temp = fgetc(buf->underlying_stream);
        if (temp == -1) {
            printf("fgetc() got an EOF, BAD!");
            exit(1);
        }
        buf->byte = (uint8_t) temp;
        buf->bit_position = 0;
    }
    // get the bit indexed at bit position from byte
    //buf->byte = (((buf->byte & 0x01) >> buf->bit_position));
    one_bit = ((buf->byte >> buf->bit_position) & 0x01);
    //
    buf->bit_position += 1;
    return one_bit; // the bit at the index
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    uint8_t target_bit = 0;
    for (uint8_t i = 0; i <= 7; i++) {
        target_bit = bit_read_bit((buf));
        // set bit at index i of byte to the value of b
        byte |= (target_bit << i);
        //
    }
    return byte;
}

/// //////////////////////////////////////////////////////////
uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    uint16_t target_bit = 0;
    for (int i = 0; i <= 15; i++) {
        target_bit = bit_read_bit(buf);
        // set bit at index i of word to the value of b
        word |= (target_bit << i);
        //
    }
    return word;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    uint32_t target_bit = 0;
    for (int i = 0; i <= 31; i++) {
        target_bit = bit_read_bit(buf);
        // set bit at index i of word to the value of b
        word |= (target_bit << i);
        //
    }
    return word;
}

///////////////////////////////////////////////////////my junk ////////////////////

FILE *file_return(BitReader *cat) {
    return cat->underlying_stream;
}
