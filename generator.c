
// generator.c
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

uint32_t generate_random_value(void) {
    return rand() % (MAX_VALUE);
}

void generate_voie_order(uint8_t order[VOIE_COUNT]) {
    // Initialize order array
    for (int i = 0; i < VOIE_COUNT; i++) {
        order[i] = i + 1;  // VOIE_1 through VOIE_4
    }
    
    // Fisher-Yates shuffle
    for (int i = VOIE_COUNT - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        uint8_t temp = order[i];
        order[i] = order[j];
        order[j] = temp;
    }
}

value_frame_t create_value_frame(uint8_t voie, uint32_t value) {
    value_frame_t frame = {
        .header = voie,
        .value = {
            value & 0xFF,
            (value >> 8) & 0xFF,
            (value >> 16) & 0xFF
        }
    };
    return frame;
}

status_frame_t create_status_frame(uint8_t voie) {
    status_frame_t frame = {
        .header = voie,
        .value = 0x00
    };
    return frame;
}

void copy_frame_to_buffer(uint8_t* buffer, const uint8_t* source, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        buffer[i] = source[i];
    }
}

void print_frame(const uint8_t* frame, size_t size) {
    printf("Generator output = ");
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", frame[i]);
    }
    printf("\n\n");
}

long_frame_t generate_frames(void) {
    uint8_t order[VOIE_COUNT];
    long_frame_t result = {0};
    uint8_t position = 0;
    
    generate_voie_order(order);
    
    for (int i = 0; i < VOIE_COUNT; i++) {
        if (order[i] == VOIE_4) {
            status_frame_t status = create_status_frame(order[i]);
            copy_frame_to_buffer(&result.frame[position], (uint8_t*)&status, STATUS_FRAME_SIZE);
            position += STATUS_FRAME_SIZE;
        } else {
            uint32_t random_value = generate_random_value();
            value_frame_t value = create_value_frame(order[i], random_value);
            copy_frame_to_buffer(&result.frame[position], (uint8_t*)&value, VALUE_FRAME_SIZE);
            position += VALUE_FRAME_SIZE;
        }
    }
    
    print_frame(result.frame, TAILLE_TABLEAU);
    return result;
}