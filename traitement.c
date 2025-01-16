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
