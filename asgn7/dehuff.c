#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "i:o:h"

/////////////////////////////////// Functions ////////////////////////////////////////

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    Node *stack[64];
    int top = -1;
    uint8_t type1 = bit_read_uint8(inbuf); // 'H'
    uint8_t type2 = bit_read_uint8(inbuf); // 'C'
    // for file size
    uint32_t filesize = bit_read_uint32(inbuf);
    // for leaves
    uint16_t num_leaves = bit_read_uint16(inbuf);
    // are we good?
    assert(type1 == 'H');
    assert(type2 == 'C');
    // right before loop
    uint64_t num_nodes = 2 * num_leaves - 1;
    Node *node = NULL;
    for (uint64_t i = 0; i < num_nodes; i += 1) {
        if (bit_read_bit(inbuf) == 1) {
            node = node_create(bit_read_uint8(inbuf), 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[top];
            top -= 1;
            node->left = stack[top];
            top -= 1;
        }
        top += 1;
        stack[top] = node;
    }
    //top -= 1;
    Node *code_tree = stack[top];
    //print code tree
    for (uint64_t j = 0; j < filesize; j += 1) {
        node = code_tree;
        while (true) {
            if (bit_read_bit(inbuf) == 0) {
                node = node->left;
            } else {
                node = node->right;
            }

            // if node is leaf
            if (node->left == NULL) {
                break;
            }
        }
        fputc(node->symbol, fout);
    }
    //free code tree
}

////////////////////////////// End of Functions, Begining of Main Program /////////////////////

int main(int argc, char **argv) {
    char *fizz;
    int opt;
    FILE *funky_out;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            fizz = strdup(optarg);
            if (fizz == NULL) {
                printf("error with reading infile\n");
                exit(1);
            }
            break;
        case 'o': // funky out is not beig set to optarg
            funky_out = fopen(optarg, "wb");
            if (funky_out == NULL) {
                printf("error reading outfile");
                exit(1);
            }
            break;
        case 'h':
            printf("Basic Operation\nRequired: -i infile.filetype -o outfile.huff\nOptional: -h "
                   "for help message\n");
            return 0;
        default: printf("You did not input correctly, please try again"); exit(1);
        }
    }

    BitReader *new_in = bit_read_open(fizz);
    dehuff_decompress_file(funky_out, new_in);
    fclose(funky_out);
    free(fizz);
    return 0;
}
