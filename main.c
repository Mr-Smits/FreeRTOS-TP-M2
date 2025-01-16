#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "generator.h"
#include "pretraitement.h"

int main(void) {
    srand(time(NULL));
    while(1){
        long_frame_t frame = {0};
        frame = generate_frames();

        for(int ii = 0; ii < TAILLE_TABLEAU ; ii++) printf("%02X", frame.frame[ii]);
        printf("\n");

        valeurs_voies_t valeurs = {0};
        valeurs = demultiplexage(frame);
        
        for(int ii = 0; ii < BYTES_PER_VALUE; ii++) printf("Voie1 : 0x%02X",valeurs.voie1.valeur[ii]);
        printf("\n");
        for(int ii = 0; ii < BYTES_PER_VALUE; ii++) printf("Voie2 : 0x%02X",valeurs.voie2.valeur[ii]);
        printf("\n");
        for(int ii = 0; ii < BYTES_PER_VALUE; ii++) printf("Voie3 : 0x%02X",valeurs.voie3.valeur[ii]);
        printf("\n\n");

        sleep(1);
    }
    return 0;
}