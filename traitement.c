#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "pretraitement.h"

// Fonction de comparaison pour qsort
static int comparer_timestamp(const void *a, const void *b) {
    const valeur_voie_t *val1 = (const valeur_voie_t *)a;
    const valeur_voie_t *val2 = (const valeur_voie_t *)b;
    
    if (val1->horodatage < val2->horodatage) return -1;
    if (val1->horodatage > val2->horodatage) return 1;
    return 0;
}

// Données de test
valeur_voie_t valeurs_voie1[9] = {
    {VOIE_1, 1736569146, {0xCE, 0xFC, 0x51}},
    {VOIE_1, 1736569139, {0xD4, 0x0F, 0x90}},
    {VOIE_1, 1736569145, {0xE9, 0x4E, 0x3D}},
    {VOIE_1, 1736569141, {0x23, 0x91, 0xE9}},
    {VOIE_1, 1736569138, {0x1A, 0xB0, 0x8F}},
    {VOIE_1, 1736569140, {0xB7, 0xCD, 0xE6}},
    {VOIE_1, 1736569144, {0x63, 0x33, 0x6C}},
    {VOIE_1, 1736569143, {0x48, 0xC5, 0xDE}},
    {VOIE_1, 1736569142, {0x92, 0xFD, 0x67}}
};

void enregistrement_donnees(valeur_voie_t *valeurs, size_t taille) {
    // Trier le tableau selon les timestamps
    qsort(valeurs, taille, sizeof(valeur_voie_t), comparer_timestamp);
    
    printf("Voie | Timestamp    | Valeurs (hex)\n");
    printf("----------------------------------\n");
    
    for (size_t i = 0; i < taille; i++) {
        printf("%4d | %11ld | 0x%02X 0x%02X 0x%02X\n",
               valeurs[i].voie,
               valeurs[i].horodatage,
               valeurs[i].valeur[0],
               valeurs[i].valeur[1],
               valeurs[i].valeur[2]);
    }
    printf("\n");
}
