#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

/* =======================
   MEMBERSIHKAN LAYAR
   ======================= */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* =======================
   PAUSE LAYAR
   ======================= */
void pauseScreen() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
}

/* =======================
   INPUT INTEGER AMAN
   - Hanya menerima angka
   - Menolak huruf & simbol
   - Tidak infinite loop
   ======================= */
int inputInt(const char *label) {
    char buffer[50];
    int valid;

    while (1) {
        printf("%s", label);
        fgets(buffer, sizeof(buffer), stdin);

        // hapus newline
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            printf("Tidak boleh kosong!\n");
            continue;
        }

        valid = 1;
        for (int i = 0; buffer[i]; i++) {
            if (!isdigit(buffer[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Input harus berupa angka!\n");
            continue;
        }

        return atoi(buffer);
    }
}

/* =======================
   INPUT STRING AMAN
   - Bisa huruf, angka, strip
   - Tidak bentrok inputInt
   ======================= */
void inputString(const char *label, char *output, int max) {
    while (1) {
        printf("%s", label);
        fgets(output, max, stdin);

        // hapus newline
        output[strcspn(output, "\n")] = 0;

        if (strlen(output) == 0) {
            printf("Tidak boleh kosong!\n");
        } else {
            return;
        }
    }
}

/* =======================
   PROTEKSI FOLDER DATABASE
   - Membuat folder db/
   - Mencegah fopen gagal
   ======================= */
void protectFolder() {
#ifdef _WIN32
    system("if not exist db mkdir db");
#else
    system("mkdir -p db");
#endif
}
