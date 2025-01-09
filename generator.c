#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "generator.h"

#define VOIE_1 1
#define VOIE_2 2
#define VOIE_3 3
#define VOIE_4 4

typedef struct frame_s {
    uint8_t header;
    uint8_t value[3];
    uint32_t frame;
}frame_t;

uint32_t generator_rand_num(void) {
    uint32_t randomNumber = rand();
    uint32_t randomNumberRange = randomNumber % MAX_VALUE;
    printf("Random Number = %02X\n", randomNumberRange);
    
    return(randomNumberRange);
}

uint8_t shuffle_order(int order[4]) {

}

uint32_t voie_value (uint8_t voie, uint32_t value) {
    frame_t frame;

    frame.header = voie;
    frame.value[0] = (value & 0x0000FF);
    frame.value[1] = (value & 0x00FF00) >> 8;
    frame.value[2] = (value & 0xFF0000) >> 16;

    frame.frame = (frame.header << 24) | (frame.value[2] << 16) | (frame.value[1] << 8) | frame.value[0];
    printf("frame = %08X\n\n", frame.frame);

    return frame.frame;
}

void generate_frames(void) {
    int order[4] = {VOIE_1, VOIE_2, VOIE_3, VOIE_4};
    shuffle_order(order);

    for(int ii = 0; ii < 4; ii++) {
        uint32_t value_voie = generator_rand_num();
        uint32_t frame = voie_value(order[ii], value_voie);
    }
}


int main(void) {
    srand(time(NULL));
    generate_frames();
    return 1;
}
