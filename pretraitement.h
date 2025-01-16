// pretraitement.h
#ifndef PRETRAITEMENT_H
#define PRETRAITEMENT_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "generator.h"

// Constants
#define BYTES_PER_VALUE 3
#define VALUE_FRAME_SIZE 4
#define STATUS_FRAME_SIZE 2

// Structures
typedef struct {
    Voie voie;
    time_t horodatage;
    uint8_t valeur[BYTES_PER_VALUE];
} valeur_voie_t;

typedef struct {
    valeur_voie_t voie1;
    valeur_voie_t voie2;
    valeur_voie_t voie3;
} valeurs_voies_t;

// Functions
void process_value_frame(valeur_voie_t* voie_dest, const uint8_t* frame_data, Voie voie_num);
valeurs_voies_t demultiplexage(long_frame_t frame);

#endif // PRETRAITEMENT_H