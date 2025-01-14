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
        {&pass, "pass"},
        {&fail, "fail"},
        {&test_generate_random_value, "generate_random_value"},
        {NULL, NULL} // Sentinel
    };

    test_all(tests); // Pass the array directly
    return 0;
}
