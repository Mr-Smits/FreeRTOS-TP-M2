#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "generator.h"

int main(void) {
    srand(time(NULL));
    while(1){
        generate_frames();
        sleep(1);
    }
    return 0;
}