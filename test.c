#include <stdio.h>
#include <string.h>
#include "generator.h"

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

int test_generator(void) {
    int ret = 1;
    for(int ii = 0; ii > 50; ii++) {
        if(generator_rand_num() > MAX_VALUE) ret = fail();
    }
    return ret;
}

int test_shuffle(void) {
    int ret = 1;
    uint8_t order[4] = {VOIE_1, VOIE_2, VOIE_3, VOIE_4};
    uint8_t previous_order[4];
    memcpy(previous_order, order, 4 * sizeof(order[0]));

    for(int ii = 0; ii < 50; ii++) {
        shuffle_order(order);

        int counter = 0;
        for (int i = 0; i < 4; i++) {
        if (previous_order[i] == order[i]) {
            counter++;
        }
        if (counter = 4) ret = fail();
    }
        memcpy(previous_order, order, 4 * sizeof(order[0]));
    }
    return ret;
}

int main(void) {
    test_t tests[] = {
        {&pass, "pass"},
        {&fail, "fail"},
        {&test_generator, "rand_num_generator"},
        {&test_shuffle, "shuffle"},
        {NULL, NULL} // Sentinel
    };

    test_all(tests); // Pass the array directly
    return 0;
}
