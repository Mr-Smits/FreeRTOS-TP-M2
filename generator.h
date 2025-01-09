#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>

// Constants
#define MAX_VALUE 0xFFFFFF
#define VOIE_1 0x01
#define VOIE_2 0x02
#define VOIE_3 0x03
#define VOIE_4 0x04

// Structure definitions
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

// Function declarations
void generate_frames(void);

#endif // GENERATOR_H