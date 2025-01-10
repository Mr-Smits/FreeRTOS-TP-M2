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
        valeurs_voies_t valeurs = {0};
        valeurs = demultiplexage(frame);
        print_voie(valeurs);
        sleep(1);
    }
    return 0;
}