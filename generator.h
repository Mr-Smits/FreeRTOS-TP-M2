#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>
#include <stddef.h>

// Constants
#define MAX_VALUE 0xFFFFFF
#define TAILLE_TABLEAU 14
#define VALUE_FRAME_SIZE 4
#define STATUS_FRAME_SIZE 2
#define BYTES_PER_VALUE 3

typedef enum {
    VOIE_1 = 1,
    VOIE_2 = 2,
    VOIE_3 = 3,
    VOIE_4 = 4,
    VOIE_COUNT = 4
} Voie;

// Structure definitions
typedef struct {
    uint8_t header;
    uint8_t value[BYTES_PER_VALUE];
} value_frame_t;

typedef struct {
    uint8_t header;
    uint8_t value;
} status_frame_t;

typedef struct {
    uint8_t frame[TAILLE_TABLEAU];
} long_frame_t;

// Function declarations
uint32_t generate_random_value(void);
void generate_voie_order(uint8_t order[VOIE_COUNT]);
value_frame_t create_value_frame(uint8_t voie, uint32_t value);
status_frame_t create_status_frame(uint8_t voie);
void copy_frame_to_buffer(uint8_t* buffer, const uint8_t* source, uint8_t size);
void print_frame(const uint8_t* frame, size_t size);
long_frame_t generate_frames(void);

#endif // GENERATOR_H