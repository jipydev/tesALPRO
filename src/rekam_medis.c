#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rekam_medis.h"
#include "utils.h"

#define FILE_REKAM "db/rekam_medis.txt"
#define FILE_TEMP "db/temp.txt"

typedef struct {
    char nama[50];
    char keluhan[100];
} Rekam;

void tambahRekam() {
    FILE *f = fopen(FILE_REKAM, "a");
    if (!f) { printf("Gagal membuka file!\n"); return; }

    Rekam r;
    printf("Nama pasien: "); getchar(); fgets(r.nama, 50, stdin); trim(r.nama);
    printf("Keluhan: "); fgets(r.keluhan, 100, stdin); trim(r.keluhan);

    fprintf(f, "%s|%s\n", r.nama, r.keluhan);
    fclose(f);

    printf("Rekam medis ditambahkan!\n");
    pauseScreen();
}

void lihatRekam() {
    FILE *f = fopen(FILE_REKAM, "r");
    if (!f) { printf("Belum ada data.\n"); pauseScreen(); return; }

    Rekam r;
    printf("\n=== DATA REKAM MEDIS ===\n");
    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF)
        printf("Nama: %s | Keluhan: %s\n", r.nama, r.keluhan);

    fclose(f);
    pauseScreen();
}

void editRekam() {
    char cari[50];
    printf("Nama pasien yang ingin diedit: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_REKAM, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Rekam r;
    int found = 0;

    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF) {
        if (strcmp(r.nama, cari) == 0) {
            found = 1;
            printf("Keluhan baru: ");
            fgets(r.keluhan, 100, stdin);
            trim(r.keluhan);
        }
        fprintf(tmp, "%s|%s\n", r.nama, r.keluhan);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_REKAM);
    rename(FILE_TEMP, FILE_REKAM);

    if (found) printf("Rekam berhasil diubah!\n");
    else printf("Nama tidak ditemukan.\n");

    pauseScreen();
}

void hapusRekam() {
    char cari[50];
    printf("Nama pasien yang ingin dihapus: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_REKAM, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Rekam r;
    int found = 0;

    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF) {
        if (strcmp(r.nama, cari) == 0) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%s|%s\n", r.nama, r.keluhan);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_REKAM);
    rename(FILE_TEMP, FILE_REKAM);

    if (found) printf("Rekam berhasil dihapus!\n");
    else printf("Nama tidak ditemukan.\n");

    pauseScreen();
}

void menuRekam() {
    int p;
    do {
        clearScreen();
        printf("=== CRUD REKAM MEDIS ===\n");
        printf("1. Tambah\n2. Lihat\n3. Edit\n4. Hapus\n0. Kembali\nPilih: ");
        scanf("%d", &p);

        if (p == 1) tambahRekam();
        if (p == 2) lihatRekam();
        if (p == 3) editRekam();
        if (p == 4) hapusRekam();

    } while (p != 0);
}
