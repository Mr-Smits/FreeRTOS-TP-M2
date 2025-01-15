#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "test.h"
#include "../generator.h"

int test_generate_random_value() {
    for (int i = 0; i < 100; i++) {
        uint32_t value = generate_random_value();
        if(value > MAX_VALUE) return(fail());
    }
    return(pass());
}

int test_generate_voie_order() {
    uint8_t order[VOIE_COUNT];
    generate_voie_order(order);

    int voie_counts[VOIE_COUNT] = {0};
    for (int i = 0; i < VOIE_COUNT; i++) {
        if(order[i] <= 0 || order[i] > VOIE_COUNT) return(fail()); // Vérifie les indices valides
        voie_counts[order[i] - 1]++;
    }

    for (int i = 0; i < VOIE_COUNT; i++) {
        if(voie_counts[i] != 1)return(fail()); // Chaque voie doit apparaître exactement une fois
    }
    return(pass());
}

int test_create_value_frame() {
    uint32_t value = 0x123456;
    uint8_t voie = 2;
    value_frame_t frame = create_value_frame(voie, value);

    // Vérifie les valeurs dans le frame
    if(frame.header != voie) return(fail());
    if(frame.value[0] != (value & 0xFF)) return(fail());
    if(frame.value[1] != ((value >> 8) & 0xFF)) return(fail());
    if(frame.value[2] != ((value >> 16) & 0xFF)) return(fail());

    return(pass());
}

int test_create_status_frame() {
    uint8_t voie = 4;
    status_frame_t frame = create_status_frame(voie);

    if(frame.header != voie) return(fail());
    if(frame.value != 0x00) return(fail());

    return(pass());
}

int test_copy_frame_to_buffer() {
    uint8_t source[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t buffer[4] = {0};
    copy_frame_to_buffer(buffer, source, sizeof(source));

    if(memcmp(buffer, source, sizeof(source)) != 0) return(fail());

    return(pass());
}

int test_generate_frames() {
    long_frame_t frames = generate_frames();
    if(frames.frame[0] == 0) return(fail());
    return(pass());
}
