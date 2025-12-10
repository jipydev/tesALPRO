#include <stdio.h>
#include "cek_stunting.h"
#include "utils.h"

void cekStunting() {
    float umur, tinggi;

    clearScreen();
    printf("Umur balita (tahun): ");
    scanf("%f", &umur);

    printf("Tinggi badan (cm): ");
    scanf("%f", &tinggi);

    float standar = umur * 70;

    printf("\nStandar minimal tinggi: %.2f cm\n", standar);

    if (tinggi < standar)
        printf("HASIL: STUNTING ❗\n");
    else
        printf("HASIL: SEHAT ✔\n");

    pauseScreen();
}
