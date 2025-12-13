#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "utils.h"

void pauseScreen() {
    printf("\nTekan ENTER untuk melanjutkan...");
    while (getchar() != '\n');
}

void clearScreen() {
    system("cls");
}

void trim(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void protectFolder() {
    struct stat st = {0};
    if (stat("db", &st) == -1) {
        system("mkdir db");
    }
}

/* =========================
      INPUT ANGKA AMAN
   ========================= */
int inputInt(const char *label) {
    char buffer[100];

    while (1) {
        printf("%s", label);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Input gagal!\n");
            continue;
        }

        trim(buffer);

        if (strlen(buffer) == 0) {
            printf("⚠ Tidak boleh kosong!\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; buffer[i]; i++) {
            if (!isdigit(buffer[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Input harus ANGKA!\n");
            continue;
        }

        return atoi(buffer);
    }
}

/* =========================
      INPUT STRING AMAN
   ========================= */
void inputString(const char *label, char *buffer, int size) {
    printf("%s", label);
    fgets(buffer, size, stdin);
    trim(buffer);
}
