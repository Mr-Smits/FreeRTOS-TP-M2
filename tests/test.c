#include <stdio.h>
#include <string.h>

#include "test_generator.h"
#include "test_pretraitement.h"

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

typedef int(testfn_t)(void);

typedef struct test_s {
    testfn_t *call;
    const char *name;
} test_t;


void test_all(test_t* tests) {
    for (test_t *test = tests; test->call != NULL; test++) {
        int ret = test->call();
        const char *status_color = ret ? GREEN : RED; // Choose color based on result
        const char *status_text = ret ? "OK" : "KO";  // Choose text based on result
        printf("%25s %s%s%s\n", test->name, status_color, status_text, RESET);
    }
}


int pass(void) {
    return 1;
}

int fail(void) {
    return 0;
}


int main(void) {
    test_t tests[] = {
        //Test Generator
        {&test_generate_random_value, "generation_valeur"},
        {&test_generate_voie_order, "generation_ordre"},
        {&test_create_value_frame, "generation_value_frame"},
        {&test_create_status_frame, "generation_status_frame"},
        {&test_copy_frame_to_buffer, "copy_arrays"},
        {&test_generate_frames, "generation_frame"},
        //Test Pretraitement
        {&test_demultiplexage, "demultiplexage"},
        {NULL, NULL} // Sentinel
    };

    test_all(tests); // Pass the array directly
    return 0;
}
