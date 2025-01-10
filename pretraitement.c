#include "pretraitement.h"

uint8_t tableau[TAILLE_TABLEAU] = {
    0x02, 0xD4, 0xDF, 0x88,
    0x03, 0x65, 0xEE, 0x87,
    0x04, 0x00, 0x01, 0x76,
    0xAE, 0x9F
};

valeurs_voies_t demultiplexage(long_frame_t frame) {
    valeurs_voies_t valeurs = {0};
    int count = 0;
    
    while(count < TAILLE_TABLEAU) {
        if(frame.frame[count] == VOIE_1) {
            valeurs.voie1.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie1.valeur[ii] = frame.frame[count + 1 + ii];
            }
            count = count + 4;
        }
        else if(frame.frame[count] == VOIE_2) {
            valeurs.voie2.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie2.valeur[ii] = frame.frame[count + 1 + ii];
            }
            count = count + 4;
        }
        else if(frame.frame[count] == VOIE_3) {
            valeurs.voie3.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie3.valeur[ii] = frame.frame[count + 1 + ii];
            }
            count = count + 4;
        }
        else {
            count = count + 1;
        }
    }
    
    return valeurs;
}

void print_voie(valeurs_voies_t valeurs) {
    printf("Voie 1 (timestamp: %ld): ", valeurs.voie1.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie1.valeur[i]);
    }
    printf("\n");
    
    printf("Voie 2 (timestamp: %ld): ", valeurs.voie2.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie2.valeur[i]);
    }
    printf("\n");
    
    printf("Voie 3 (timestamp: %ld): ", valeurs.voie3.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie3.valeur[i]);
    }
    printf("\n");
}

//TODO 3 files de sortie pour les voies 1, 2, et 3