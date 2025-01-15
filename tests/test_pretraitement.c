#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "test.h"
#include "pretraitement.h"

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
    long_frame_t frame = {0};
    frame.frame[0] = VOIE_1;
    frame.frame[1] = 0x12;
    frame.frame[2] = 0x34;
    frame.frame[3] = 0x56;
    frame.frame[4] = VOIE_2;
    frame.frame[5] = 0x78;
    frame.frame[6] = 0x9A;
    frame.frame[7] = 0xBC;
    frame.frame[8] = VOIE_4; // Status frame

    valeurs_voies_t valeurs = demultiplexage(frame);

    // Vérifie VOIE_1
    if (valeurs.voie1.voie != VOIE_1) return fail();
    if (memcmp(valeurs.voie1.valeur, (uint8_t[]){0x56, 0x34, 0x12}, BYTES_PER_VALUE) != 0) return fail();

    // Vérifie VOIE_2
    if (valeurs.voie2.voie != VOIE_2) return fail();
    if (memcmp(valeurs.voie2.valeur, (uint8_t[]){0xBC, 0x9A, 0x78}, BYTES_PER_VALUE) != 0) return fail();

    // Vérifie que VOIE_3 est restée vide
    if (valeurs.voie3.voie != 0) return fail();

    return pass();
}

int test_invalid_frames() {
    long_frame_t frame = {0};
    frame.frame[0] = 0xFF; // Invalide
    frame.frame[1] = VOIE_1;
    frame.frame[2] = 0x12;
    frame.frame[3] = 0x34;

    valeurs_voies_t valeurs = demultiplexage(frame);

    // Vérifie que les voies ne contiennent aucune donnée
    if (valeurs.voie1.voie != 0) return fail();
    if (valeurs.voie2.voie != 0) return fail();
    if (valeurs.voie3.voie != 0) return fail();

    return pass();
}

int main() {
    int tests_passed = 0;

    tests_passed += test_process_value_frame();
    tests_passed += test_demultiplexage();
    tests_passed += test_invalid_frames();

    printf("%d/%d tests passed\n", tests_passed, 3);

    return 0;
}
