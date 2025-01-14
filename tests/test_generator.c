#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "../generator.h"

void test_generate_random_value() {
    for (int i = 0; i < 100; i++) {
        uint32_t value = generate_random_value();
        assert(value < MAX_VALUE); // Vérifie que la valeur est dans la plage autorisée
    }
    printf("test_generate_random_value passed.\n");
}

void test_generate_voie_order() {
    uint8_t order[VOIE_COUNT];
    generate_voie_order(order);

    // Vérifie que chaque voie est présente une fois
    int voie_counts[VOIE_COUNT] = {0};
    for (int i = 0; i < VOIE_COUNT; i++) {
        assert(order[i] >= 1 && order[i] <= VOIE_COUNT); // Vérifie les indices valides
        voie_counts[order[i] - 1]++;
    }

    for (int i = 0; i < VOIE_COUNT; i++) {
        assert(voie_counts[i] == 1); // Chaque voie doit apparaître exactement une fois
    }
    printf("test_generate_voie_order passed.\n");
}

void test_create_value_frame() {
    uint32_t value = 0x123456;
    uint8_t voie = 2;
    value_frame_t frame = create_value_frame(voie, value);

    // Vérifie les valeurs dans le frame
    assert(frame.header == voie);
    assert(frame.value[0] == (value & 0xFF));
    assert(frame.value[1] == ((value >> 8) & 0xFF));
    assert(frame.value[2] == ((value >> 16) & 0xFF));
    printf("test_create_value_frame passed.\n");
}

void test_create_status_frame() {
    uint8_t voie = 4;
    status_frame_t frame = create_status_frame(voie);

    // Vérifie les valeurs dans le frame
    assert(frame.header == voie);
    assert(frame.value == 0x00);
    printf("test_create_status_frame passed.\n");
}

void test_copy_frame_to_buffer() {
    uint8_t source[] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t buffer[4] = {0};
    copy_frame_to_buffer(buffer, source, sizeof(source));

    // Vérifie que les données sont copiées correctement
    assert(memcmp(buffer, source, sizeof(source)) == 0);
    printf("test_copy_frame_to_buffer passed.\n");
}

void test_print_frame() {
    uint8_t frame[] = {0x01, 0x02, 0x03, 0x04};
    print_frame(frame, sizeof(frame));
    // Ce test est visuel, vérifiez l'affichage
    printf("test_print_frame passed.\n");
}

void test_generate_frames() {
    long_frame_t frames = generate_frames();

    // Vérifie que les données dans le tableau sont raisonnables
    // (Ce test dépend des définitions exactes de `TAILLE_TABLEAU` et du format des frames)
    assert(frames.frame[0] != 0); // Vérifie qu'il y a des données générées
    printf("test_generate_frames passed.\n");
}

int main() {
    test_generate_random_value();
    test_generate_voie_order();
    test_create_value_frame();
    test_create_status_frame();
    test_copy_frame_to_buffer();
    test_print_frame();
    test_generate_frames();

    printf("All tests passed.\n");
    return 0;
}
