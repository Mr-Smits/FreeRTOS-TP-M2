#include "pretraitement.h"

valeurs_voies_t demultiplexage(long_frame_t frame) {
    valeurs_voies_t valeurs = {0};
    int count = 0;

    while (count < TAILLE_TABLEAU) {
        switch ((Voie)frame.frame[count]) {
            case VOIE_1:
                valeurs.voie1.voie = VOIE_1;
                valeurs.voie1.horodatage = time(NULL);
                for (int ii = 0; ii < 3; ii++) {
                    valeurs.voie1.valeur[ii] = frame.frame[count + 3 - ii];
                }
                count += 4;
                break;

            case VOIE_2:
                valeurs.voie2.voie = VOIE_2;
                valeurs.voie2.horodatage = time(NULL);
                for (int ii = 0; ii < 3; ii++) {
                    valeurs.voie2.valeur[ii] = frame.frame[count + 3 - ii];
                }
                count += 4;
                break;

            case VOIE_3:
                valeurs.voie3.voie = VOIE_3;
                valeurs.voie3.horodatage = time(NULL);
                for (int ii = 0; ii < 3; ii++) {
                    valeurs.voie3.valeur[ii] = frame.frame[count + 3 - ii];
                }
                count += 4;
                break;

            case VOIE_4:
                count += 2;
                break;

            default:
                break;
        }
    }

    return valeurs;
}


void print_voie(valeurs_voies_t valeurs) {
    printf("Voie %d (timestamp: %ld): ",valeurs.voie1.voie, valeurs.voie1.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie1.valeur[i]);
    }
    printf("\n");
    
    printf("Voie %d (timestamp: %ld): ",valeurs.voie2.voie, valeurs.voie2.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie2.valeur[i]);
    }
    printf("\n");
    
    printf("Voie %d (timestamp: %ld): ",valeurs.voie3.voie, valeurs.voie3.horodatage);
    for(int i = 0; i < 3; i++) {
        printf("0x%02X ", valeurs.voie3.valeur[i]);
    }
    printf("\n");
}

//TODO 3 files de sortie pour les voies 1, 2, et 3