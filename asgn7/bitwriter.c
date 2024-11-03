#include "bitwriter.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *my_write = calloc(1, sizeof(BitWriter));
    FILE *f = fopen(filename, "wb");
    if (f == 0) {
        return NULL;
        // not quite sure what fopen() returns if it does not work but should not be any of those.
    }
    my_write->underlying_stream = f;
    my_write->byte = 0x00;
    my_write->bit_position = 0x00;
    return my_write;
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            int error_checker = fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
            if (error_checker == -1) { // -1 means EOF which mean error from fputc()
                printf("something went wrong with bit_write_close, BAD!");
                exit(1);
            }
        }
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}
// https://www.tutorialspoint.com/c_standard_library/c_function_fputc.htm

// does not work! look at comment
void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        int error_checker = fputc(buf->byte, buf->underlying_stream);
        if (error_checker == -1) { // -1 means EOF which mean error from fputc()
            printf("MINE MINE something went wrong with bit_write_bit, BAD!");
            exit(1);
        }
        buf->byte = 0;
        buf->bit_position = 0;
    }
    // Im confused here???
    buf->byte |= (bit << buf->bit_position);
    // next bit works, heheh bit
    buf->bit_position += 1;
}

// depends on bit write bit working . . .
// also has issues of seperating out an indivigual bit? how do I do that?? byte[i]???
void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (int i = 0; i <= 7; i++) {
        bit_write_bit(buf, ((byte >> i) & 0x01));
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i <= 15; i++) {
        bit_write_bit(buf, ((x >> i) & 0x01));
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i <= 31; i++) {
        bit_write_bit(buf, ((x >> i) & 0x01));
    }
}
