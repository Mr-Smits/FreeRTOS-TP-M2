// pretraitement.c
#include "pretraitement.h"

void process_value_frame(valeur_voie_t* voie_dest, const uint8_t* frame_data, Voie voie_num) {
    if (!voie_dest || !frame_data) return;
    
    voie_dest->voie = voie_num;
    voie_dest->horodatage = time(NULL);
    
    for (int i = 0; i < BYTES_PER_VALUE; i++) {
        voie_dest->valeur[i] = frame_data[BYTES_PER_VALUE - i];
    }
}

valeurs_voies_t demultiplexage(long_frame_t frame) {
    valeurs_voies_t valeurs = {0};
    int position = 0;
    
    while (position < TAILLE_TABLEAU) {
        Voie current_voie = (Voie)frame.frame[position];
        
        switch (current_voie) {
            case VOIE_1:
                process_value_frame(&valeurs.voie1, &frame.frame[position], VOIE_1);
                position += VALUE_FRAME_SIZE;
                break;
                
            case VOIE_2:
                process_value_frame(&valeurs.voie2, &frame.frame[position], VOIE_2);
                position += VALUE_FRAME_SIZE;
                break;
                
            case VOIE_3:
                process_value_frame(&valeurs.voie3, &frame.frame[position], VOIE_3);
                position += VALUE_FRAME_SIZE;
                break;
                
            case VOIE_4:
                position += STATUS_FRAME_SIZE;
                break;
                
            default:
                position++;
                break;
        }
    }
    
    return valeurs;
}