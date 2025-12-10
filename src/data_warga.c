#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_warga.h"
#include "utils.h"

#define FILE_WARGA "db/data_warga.txt"
#define FILE_TEMP "db/temp.txt"

typedef struct {
    int id;
    char nama[50];
    int umur;
} Warga;

void tambahWarga() {
    FILE *f = fopen(FILE_WARGA, "a");
    if (!f) { printf("Gagal membuka file!\n"); return; }

    Warga w;
    printf("ID: "); scanf("%d", &w.id);
    printf("Nama: "); getchar(); fgets(w.nama, 50, stdin); trim(w.nama);
    printf("Umur: "); scanf("%d", &w.umur);

    fprintf(f, "%d|%s|%d\n", w.id, w.nama, w.umur);
    fclose(f);

    printf("Data warga ditambahkan!\n");
    pauseScreen();
}

void lihatWarga() {
    FILE *f = fopen(FILE_WARGA, "r");
    if (!f) { printf("Belum ada data.\n"); pauseScreen(); return; }

    Warga w;
    printf("\n=== DATA WARGA ===\n");
    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        printf("ID:%d | %s | Umur:%d\n", w.id, w.nama, w.umur);
    }
    fclose(f);
    pauseScreen();
}

void editWarga() {
    int editId;
    printf("Masukkan ID yang ingin diedit: ");
    scanf("%d", &editId);

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    if (!f || !tmp) return;

    Warga w;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == editId) {
            found = 1;
            printf("Nama baru: "); getchar(); fgets(w.nama, 50, stdin); trim(w.nama);
            printf("Umur baru: "); scanf("%d", &w.umur);
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    fclose(f); fclose(tmp);
    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    if (found) printf("Data berhasil diubah!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

void hapusWarga() {
    int hapusId;
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%d", &hapusId);

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Warga w;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == hapusId) {
            found = 1;  
            continue;
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    fclose(f); fclose(tmp);
    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    if (found) printf("Data berhasil dihapus!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

void menuWarga() {
    int p;
    do {
        clearScreen();
        printf("=== MENU CRUD WARGA ===\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("3. Edit Data\n");
        printf("4. Hapus Data\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        switch (p) {
            case 1: tambahWarga(); break;
            case 2: lihatWarga(); break;
            case 3: editWarga(); break;
            case 4: hapusWarga(); break;
        }
    } while (p != 0);
}
