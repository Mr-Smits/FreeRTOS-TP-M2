#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "test.h"
#include "../pretraitement.h"

int test_process_value_frame() {
    valeur_voie_t voie_dest = {0};
    uint8_t frame_data[BYTES_PER_VALUE] = {0x12, 0x34, 0x56};
    Voie voie_num = VOIE_2;

    process_value_frame(&voie_dest, frame_data, voie_num);

    if (voie_dest.voie != voie_num) return fail();
    if (memcmp(voie_dest.valeur, (uint8_t[]){0x56, 0x34, 0x12}, BYTES_PER_VALUE) != 0) return fail();

    return pass();
}

int test_demultiplexage() {
    long_frame_t frame = {
        .frame = {
            VOIE_1, 0x12, 0x34, 0x56,  // Frame de VOIE_1 avec valeur 0x123456
            VOIE_2, 0x78, 0x9A, 0xBC,  // Frame de VOIE_2 avec valeur 0x789ABC
            VOIE_3, 0xDE, 0xAD, 0xBE,  // Frame de VOIE_3 avec valeur 0xDEADBE
            VOIE_4, 0x00               // Frame de statut de VOIE_4
        }
    };

    valeurs_voies_t valeurs = demultiplexage(frame);

    // Vérifie VOIE_1
    if (valeurs.voie1.voie != VOIE_1) return fail();
    if (memcmp(valeurs.voie1.valeur, (uint8_t[]){0x56, 0x34, 0x12}, BYTES_PER_VALUE) != 0) return fail();

    // Vérifie VOIE_2
    if (valeurs.voie2.voie != VOIE_2) return fail();
    if (memcmp(valeurs.voie2.valeur, (uint8_t[]){0xBC, 0x9A, 0x78}, BYTES_PER_VALUE) != 0) return fail();

    // Vérifie VOIE_3
    if (valeurs.voie3.voie != VOIE_3) return fail();
    if (memcmp(valeurs.voie3.valeur, (uint8_t[]){0xBE, 0xAD, 0xDE}, BYTES_PER_VALUE) != 0) return fail();

    return pass();
}