#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rekam_medis.h"
#include "utils.h"

#define FILE_REKAM "db/rekam_medis.txt"
#define FILE_TEMP  "db/temp.txt"

void tambahRekamAction() {
    clearScreen();
    FILE *f = fopen(FILE_REKAM, "a");
    if (!f) { printf("Gagal membuka file!\n"); pauseScreen(); return; }

    Rekam r;

    printf("Nama pasien: ");
    getchar(); fgets(r.nama, 50, stdin); trim(r.nama);

    printf("Keluhan: ");
    fgets(r.keluhan, 100, stdin); trim(r.keluhan);

    fprintf(f, "%s|%s\n", r.nama, r.keluhan);
    fclose(f);

    printf("\nRekam medis BERHASIL ditambahkan!\n");
    pauseScreen();
}

void tambahRekam() {
    int p;
    do {
        clearScreen();
        printf("=== MENU TAMBAH REKAM MEDIS ===\n");
        printf("1. Tambah Data\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        if (p == 1) tambahRekamAction();

    } while (p != 0);
}

/* =======================
   LIHAT REKAM MEDIS
   ======================= */

void tampilkanSemuaRekam() {
    clearScreen();
    FILE *f = fopen(FILE_REKAM, "r");
    if (!f) { printf("Belum ada data.\n"); pauseScreen(); return; }

    Rekam r;
    printf("=== SEMUA REKAM MEDIS ===\n");
    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF) {
        printf("Nama: %s | Keluhan: %s\n", r.nama, r.keluhan);
    }
    fclose(f);

    pauseScreen();
}

void cariRekamByNama() {
    clearScreen();
    char keyword[50];

    printf("Masukkan nama pasien: ");
    getchar(); fgets(keyword, 50, stdin);
    trim(keyword);

    FILE *f = fopen(FILE_REKAM, "r");
    if (!f) { printf("Belum ada data.\n"); pauseScreen(); return; }

    Rekam r;
    int found = 0;

    printf("\n=== HASIL PENCARIAN ===\n");
    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF) {
        if (strstr(r.nama, keyword) != NULL) {
            printf("Nama: %s | Keluhan: %s\n", r.nama, r.keluhan);
            found = 1;
        }
    }

    if (!found) printf("Tidak ditemukan data '%s'.\n", keyword);

    fclose(f);
    pauseScreen();
}

void lihatRekam() {
    int p;

    do {
        clearScreen();
        printf("=== MENU LIHAT REKAM MEDIS ===\n");
        printf("1. Tampilkan Semua\n");
        printf("2. Cari Nama\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        if (p == 1) tampilkanSemuaRekam();
        if (p == 2) cariRekamByNama();

    } while (p != 0);
}

/* =======================
   EDIT REKAM MEDIS
   ======================= */

void editRekamAction() {
    clearScreen();
    char cari[50];

    printf("Nama pasien yang ingin diedit: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_REKAM, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    if (!f || !tmp) { printf("Gagal membuka file.\n"); pauseScreen(); return; }

    Rekam r;
    int found = 0;

    while (fscanf(f, "%49[^|]|%99[^\n]\n", r.nama, r.keluhan) != EOF) {
        if (strcmp(r.nama, cari) == 0) {
            found = 1;
            printf("Keluhan baru: ");
            fgets(r.keluhan, 100, stdin); trim(r.keluhan);
        }
        fprintf(tmp, "%s|%s\n", r.nama, r.keluhan);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_REKAM);
    rename(FILE_TEMP, FILE_REKAM);

    if (found) printf("Rekam medis berhasil diubah!\n");
    else printf("Nama tidak ditemukan.\n");

    pauseScreen();
}

void editRekam() {
    int p;

    do {
        clearScreen();
        printf("=== MENU EDIT REKAM MEDIS ===\n");
        printf("1. Edit Data\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        if (p == 1) editRekamAction();

    } while (p != 0);
}

/* =======================
   HAPUS REKAM MEDIS
   ======================= */

void hapusRekamAction() {
    clearScreen();
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

    if (found) printf("Rekam medis berhasil dihapus!\n");
    else printf("Nama tidak ditemukan.\n");

    pauseScreen();
}

void hapusRekam() {
    int p;

    do {
        clearScreen();
        printf("=== MENU HAPUS REKAM MEDIS ===\n");
        printf("1. Hapus Data\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        if (p == 1) hapusRekamAction();

    } while (p != 0);
}

/* =======================
   MENU UTAMA REKAM MEDIS
   ======================= */

void menuRekam() {
    int p;
    do {
        clearScreen();
        printf("=== MENU CRUD REKAM MEDIS ===\n");
        printf("1. Tambah Rekam\n");
        printf("2. Lihat Rekam\n");
        printf("3. Edit Rekam\n");
        printf("4. Hapus Rekam\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        if (p == 1) tambahRekam();
        if (p == 2) lihatRekam();
        if (p == 3) editRekam();
        if (p == 4) hapusRekam();

    } while (p != 0);
}
