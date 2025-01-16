#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "generator.h"
#include "pretraitement.h"

#include "freertos.h"

#define STACK_SIZE 25

void* Generator(void *parm){
    xQueueHandle handle_out = (xQueueHandle) parm;

    while(1) {
        long_frame_t frame = {0};
        frame = generate_frames();
        printf("frame generated !\n");

        //TO DO : send frame to Queue xQueueSendToBack();
        wait_ms(1000);
    }
    return NULL;
}

void* Pretraitement(void *parm){
    xQueueHandle handle_in = (xQueueHandle) parm;

    xQueueHandle handle_voie1 = (xQueueHandle) parm;
    xQueueHandle handle_voie2 = (xQueueHandle) parm;
    xQueueHandle handle_voie3 = (xQueueHandle) parm;

    while(1) {
        //TO DO : read frame from Queue
        long_frame_t frame = xQueueReceive(handle_in);

        valeurs_voies_t valeurs = {0};
        valeurs = demultiplexage();
        printf("frame generated !\n");

        wait_ms(1000);
    }
    return NULL;
}

int main(void) {

    pthread_t handle_1, handle_2;

    xQueueHandle Queue_handler = xQueueCreate(XQUEUE_MAX_COUNT, sizeof(long_frame_t));

    xQueueHandle Queue_handler_voie1 = xQueueCreate(XQUEUE_MAX_COUNT, sizeof(long_frame_t));
    xQueueHandle Queue_handler_voie2 = xQueueCreate(XQUEUE_MAX_COUNT, sizeof(long_frame_t));
    xQueueHandle Queue_handler_voie3 = xQueueCreate(XQUEUE_MAX_COUNT, sizeof(long_frame_t));

    xTaskCreate(&Generator, "Generate frame", STACK_SIZE, NULL, 1, &handle_1);
    xTaskCreate(&Pretraitement, "Generate frame", STACK_SIZE, NULL, 1, &handle_1);


    vTaskStartScheduler();

    while(1);

    return 1;
}
