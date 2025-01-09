#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "generator.h"

// Structures
typedef struct value_frame_s {
    uint8_t header;
    uint8_t value[3];
} value_frame_t;

typedef struct status_frame_s {
    uint8_t header;
    uint8_t value;
} status_frame_t;

typedef struct long_frame_s {
    uint8_t frame[14];
} long_frame_t;

// Generate a random number within the range
uint32_t generator_rand_num(void) {
    uint32_t randomNumber = rand() % (MAX_VALUE + 1);  // Ensure inclusive range
    return randomNumber;
}

// Shuffle the order of an array
void shuffle_order(uint8_t order[4]) {
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);
        uint8_t temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }
}

// Create a value frame for a given "voie" and value
value_frame_t voie_value(uint8_t voie, uint32_t value) {
    value_frame_t frame;

    frame.header = voie;
    frame.value[0] = (value & 0x0000FF);
    frame.value[1] = (value & 0x00FF00) >> 8;
    frame.value[2] = (value & 0xFF0000) >> 16;
    return frame;
}

// Generate frames and print them
void generate_frames(void) {
    uint8_t order[4] = {VOIE_1, VOIE_2, VOIE_3, VOIE_4};
    shuffle_order(order);

    long_frame_t frame = {0};  // Initialize frame to zero
    uint8_t position = 0;      // Start position

    for (int ii = 0; ii < 4; ii++) {
        if (order[ii] == VOIE_4) {
            frame.frame[position] = order[ii];
            frame.frame[position + 1] = 0x00;  // Status frame
            position += 2;
        } else {
            uint32_t value_voie = generator_rand_num();
            value_frame_t buf_frame = voie_value(order[ii], value_voie);
            frame.frame[position] = buf_frame.header;  // Add header
            for (int jj = 0; jj < 3; jj++) {
                frame.frame[position + 1 + jj] = buf_frame.value[jj];  // Add values
            }
            position += 4;
        }
    }

    // Print the generated frame in hexadecimal format
    for (int ii = 0; ii < sizeof(frame.frame); ii++) {
        printf("%02X ", frame.frame[ii]);
    }
    printf("\n");
}

int main(void) {
    srand((unsigned int)time(NULL));  // Seed the random number generator
    generate_frames();
    return 0;
}
