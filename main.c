#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "generator.h"
#include "pretraitement.h"

#include "freertos.h"

#define STACK_SIZE 25

void* Task1(void *parm){
    while(1) {
        printf("task1\n");
        wait_ms(1000);
    }
    return NULL;
}

void* Task2(void *parm){
    while(1) {
        printf("task2\n");
        wait_ms(1000);
    }
    return NULL;
}

int main(void) {

    pthread_t handle_1, handle_2;

    xTaskCreate(&Task1, "task1", STACK_SIZE, NULL, 1, &handle_1);
    xTaskCreate(&Task2, "task2", STACK_SIZE, NULL, 1, &handle_2);

    vTaskStartScheduler();

    while(1);

    return 1;
}
