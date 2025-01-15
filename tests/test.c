#include <stdio.h>
#include <string.h>

#include "test_generator.h"


typedef int(testfn_t)(void);

typedef struct test_s {
    testfn_t *call;
    const char *name;
} test_t;

void test_all(test_t* tests) {
    for (test_t *test = tests; test->call != NULL; test++) {
        int ret = test->call();
        const char *status = ret ? "OK" : "KO"; // Corrected ternary operator
        printf("%s %s\n", test->name, status);
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
        {&test_generate_random_value, "generation_valeur"},
        {&test_generate_voie_order, "generation_ordre"},
        {&test_create_value_frame, "generation_value_frame"},
        {&test_create_status_frame, "generation_status_frame"},
        {&test_copy_frame_to_buffer, "copy_arrays"},
        {&test_generate_frames, "generation_frame"},
        {NULL, NULL} // Sentinel
    };

    test_all(tests); // Pass the array directly
    return 0;
}
