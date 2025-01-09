#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>

#define MAX_VALUE 16777215 //uint24 max value
#define VOIE_1 1
#define VOIE_2 2
#define VOIE_3 3
#define VOIE_4 4
#define VOIE_STATUS 0x0400

uint32_t generator_rand_num(void);
void shuffle_order(uint8_t order[4]);

#endif /* MODULE_H */