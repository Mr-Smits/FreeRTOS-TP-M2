#ifndef PRETRAITEMENT_H
#define PRETRAITEMENT_H

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "generator.h"

//Constantes


//Structures
typedef struct {
    time_t horodatage;
    uint8_t valeur[3];
} valeur_voie_t;

typedef struct {
    valeur_voie_t voie1;
    valeur_voie_t voie2;
    valeur_voie_t voie3;
} valeurs_voies_t;

//Fonctions
valeurs_voies_t demultiplexage(long_frame_t frame);
void print_voie(valeurs_voies_t valeurs);


#endif // PRETRAITEMENT