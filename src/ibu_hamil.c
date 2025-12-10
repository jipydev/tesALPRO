#include <stdio.h>
#include "ibu_hamil.h"
#include "utils.h"

void cekIbuHamil() {
    float hb;

    clearScreen();
    printf("Masukkan kadar HB (g/dL): ");
    scanf("%f", &hb);

    if (hb < 11)
        printf("\nHASIL: ANEMIA — Risiko tinggi!\n");
    else
        printf("\nHASIL: NORMAL ✔\n");

    pauseScreen();
}
