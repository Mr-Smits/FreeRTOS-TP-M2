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