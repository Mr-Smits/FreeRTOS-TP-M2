#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>

// Constants
#define MAX_VALUE 0xFFFFFF
#define TAILLE_TABLEAU 14
#define VOIE_1 0x01
#define VOIE_2 0x02
#define VOIE_3 0x03
#define VOIE_4 0x04

// Structure definitions
typedef struct {
    uint8_t header;
    uint8_t value[3];
} value_frame_t;

typedef struct {
    uint8_t header;
    uint8_t value;
} status_frame_t;

typedef struct {
    uint8_t frame[TAILLE_TABLEAU];
} long_frame_t;

// Function declarations
long_frame_t generate_frames(void);

#endif // GENERATOR_H