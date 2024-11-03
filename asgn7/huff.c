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

/////////////////////////////////// Functions and stuff //////////////////////////////////

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

// works
uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    uint32_t filesize = 0; // every time anything is incrimentes, incriment this as well...
    // for clearing histogram
    int i = 0;
    while (i < 256) {
        histogram[i] = 0x00;
        i += 1;
    }
    // these next two are for the weird special case they described, ignore?? HACK
    ++histogram[0x00];
    ++histogram[0xff];
    int primary_error_check = fgetc(fin); // <- issue is here
    if (primary_error_check == -1) {
        printf("AHHHHH, there was a problem with reading the file in fill_histogram\n");
        exit(1);
    }
    int current_item = primary_error_check;
    while (current_item != -1) {
        ++histogram[(uint32_t) current_item];
        filesize += 1;
        current_item = fgetc(fin);
    }
    return filesize;
}

// there are a bunch of unfreed nodes in here, figure that out
Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *my_queue = pq_create();
    uint16_t i = 0;
    while (i < 256) {
        if (histogram[i] != 0) {
            Node *new_node = node_create((uint8_t) i, histogram[i]);
            enqueue(my_queue, new_node);
            *num_leaves += 1;
        }
        i += 1;
    }
    Node *left = NULL;
    Node *right = NULL;
    while (!(pq_is_empty(my_queue)) && !(pq_size_is_1(my_queue))) {
        left = dequeue(my_queue);
        right = dequeue(my_queue);
        Node *new_node = node_create(0, left->weight + right->weight);
        new_node->left = left;
        new_node->right = right;
        enqueue(my_queue, new_node);
    }
    // returns the complete fano tree
    Node *returner = dequeue(my_queue);
    pq_free(&my_queue);
    return returner;
}

//issue is here
void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (!(node->left == NULL)) {
        // for the left side
        fill_code_table(code_table, node->left, code, code_length + 1);
        /* append a 1 to code and recurse */
        code |= (uint64_t) 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        /* Leaf node: store the Huffman Code. */
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        /* node is a leaf */
        bit_write_bit(outbuf, 0x01);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        /* node is internal */
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_free_tree(Node *node) {
    if (node->left == NULL) {
        /* node is a leaf */
        node_free(&node);
    } else {
        /* node is internal */
        huff_free_tree(node->left);
        huff_free_tree(node->right);
    }
}

// Works
void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    fseek(fin, 0, SEEK_SET);
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);

    while (true) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (uint8_t i = 0; i < code_length; i++) {
            // Write each bit of the code to outbuf
            bit_write_bit(outbuf, (code & 0x01));
            code >>= 0x01;
        }
    }
}

////////////////////////////////// end of functions, now its the main program //////////////////////////////////////////////

int main(int argc, char **argv) {
    char *fizz;
    int opt;
    char *funky_out;

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
            funky_out = strdup(optarg);
            break;
        case 'h':
            printf("Basic Operation\nRequired: -i infile.filetype -o outfile.huff\nOptional: -h "
                   "for help message\n");
            return 0;
        default: printf("You did not input correctly, please try again"); exit(1);
        }
    }

    FILE *fi = fopen(fizz, "rb");
    uint32_t *histogram_g = calloc(256, sizeof(uint32_t));
    uint32_t file_size = fill_histogram(fi, histogram_g); //

    uint16_t num_leaves_g;
    Node *complete_fano_tree = create_tree(histogram_g, &num_leaves_g);

    Code *code_table_g = calloc(256, sizeof(Code));
    fill_code_table(
        code_table_g, complete_fano_tree, 0, 0); //<- errors with short, breaks with long

    // might have issues beyond this point ************
    BitWriter *outfile_bw = bit_write_open(funky_out);

    huff_compress_file(outfile_bw, fi, file_size, num_leaves_g, complete_fano_tree, code_table_g);

    /////////////// closing up shop now ///////////////////////////////
    bit_write_close(&outfile_bw);
    free(histogram_g);
    free(code_table_g);
    huff_free_tree(complete_fano_tree);
    return (0);
}
