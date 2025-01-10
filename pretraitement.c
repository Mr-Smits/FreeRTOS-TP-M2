#include <stdint.h>
#include <stdio.h>
#include <time.h>

// Define constants for channel identification
#define VOIE_1 0x02  // Changed to match your test data
#define VOIE_2 0x03
#define VOIE_3 0x04
#define TAILLE_TABLEAU 14

typedef struct {
    time_t horodatage;
    uint8_t valeur[3];
} valeur_voie_t;

typedef struct {
    valeur_voie_t voie1;
    valeur_voie_t voie2;
    valeur_voie_t voie3;
} valeurs_voies_t;

uint8_t tableau[TAILLE_TABLEAU] = {
    0x02, 0xD4, 0xDF, 0x88,
    0x03, 0x65, 0xEE, 0x87,
    0x04, 0x00, 0x01, 0x76,
    0xAE, 0x9F
};

valeurs_voies_t demultiplexage(uint8_t tableau[TAILLE_TABLEAU]) {
    valeurs_voies_t valeurs = {0};
    int count = 0;
    
    while(count < TAILLE_TABLEAU) {
        if(tableau[count] == VOIE_1) {
            valeurs.voie1.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie1.valeur[ii] = tableau[count + 1 + ii];
            }
            count = count + 4;
        }
        else if(tableau[count] == VOIE_2) {
            valeurs.voie2.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie2.valeur[ii] = tableau[count + 1 + ii];
            }
            count = count + 4;
        }
        else if(tableau[count] == VOIE_3) {
            valeurs.voie3.horodatage = time(NULL);
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie3.valeur[ii] = tableau[count + 1 + ii];
            }
            count = count + 4;
        }
        else {
            count = count + 1;
        }
    }
    return valeurs;
}

int main(void) {
    // Initialisation de la structure
    valeurs_voies_t valeurs;
    
    // Appel de la fonction de démultiplexage
    valeurs = demultiplexage(tableau);
    
    // Affichage des résultats
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
    
    return 0;
}