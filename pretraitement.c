#include <stdint.h>
#include <stdio.h>

// Define constants for channel identification
#define VOIE_1 0x01
#define VOIE_2 0x02
#define VOIE_3 0x03
#define TAILLE_TABLEAU 14

typedef struct {
    uint8_t voie1[3];
    uint8_t voie2[3];
    uint8_t voie3[3];
} valeur_voie_t;

uint8_t tableau[TAILLE_TABLEAU] = {0x02, 0xD4, 0xDF, 0x88, 0x03, 0x65, 0xEE, 0x87, 0x04, 0x00, 0x01, 0x76, 0xAE, 0x9F};

valeur_voie_t demultiplexage(uint8_t tableau[TAILLE_TABLEAU]) {
    valeur_voie_t valeurs = {0};    
    int count = 0;
    
    while(count < TAILLE_TABLEAU) {
        if(tableau[count] == VOIE_1) {
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie1[ii] = tableau[count + 3 - ii];
            }
            count = count + 4;
        }
        else if(tableau[count] == VOIE_2) {
            for(int ii = 0; ii < 3; ii++) { 
                valeurs.voie2[ii] = tableau[count + 3 - ii];
            }
            count = count + 4;
        }
        else if(tableau[count] == VOIE_3) {
            for(int ii = 0; ii < 3; ii++) {
                valeurs.voie3[ii] = tableau[count + 3 - ii];
            }
            count = count + 4;
        }
        else {
            count = count + 2;
        }
    }
    
    return valeurs;
}

int main(void) {
    // Initialisation de la structure
    valeur_voie_t valeurs;
    
    // Appel de la fonction de démultiplexage
    valeurs = demultiplexage(tableau);
    
    // Affichage des résultats
    printf("Voie 1: ");
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie1[i]);
    }
    printf("\n");
    
    printf("Voie 2: ");
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie2[i]);
    }
    printf("\n");
    
    printf("Voie 3: ");
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie3[i]);
    }
    printf("\n");
    
    return 0;
}