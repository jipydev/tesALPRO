#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_warga.h"
#include "utils.h"

#define FILE_WARGA "db/data_warga.txt"
#define FILE_TEMP  "db/temp.txt"

typedef struct {
    int id;
    char nama[50];
    int umur;
} Warga;

/* ================= TAMBAH ================= */
void tambahWarga() {
    clearScreen();
    printf("=== TAMBAH DATA WARGA ===\n");

    int id = inputInt("Masukkan ID (0 = batal): ");
    if (id == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    Warga w;

    if (f) {
        while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
            if (w.id == id) {
                printf("ID sudah ada!\n");
                fclose(f);
                pauseScreen();
                return;
            }
        }
        fclose(f);
    }

    f = fopen(FILE_WARGA, "a");
    if (!f) return;

    w.id = id;
    inputString("Nama: ", w.nama, sizeof(w.nama));
    w.umur = inputInt("Umur: ");

    fprintf(f, "%d|%s|%d\n", w.id, w.nama, w.umur);
    fclose(f);

    printf("Data berhasil ditambahkan!\n");
    pauseScreen();
}

/* ================= LIHAT ================= */
void tampilkanSemuaWarga() {
    clearScreen();
    FILE *f = fopen(FILE_WARGA, "r");
    Warga w;

    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    printf("=== DATA WARGA ===\n");
    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        printf("ID:%d | %s | Umur:%d\n", w.id, w.nama, w.umur);
    }
    fclose(f);
    pauseScreen();
}

void cariWargaById() {
    clearScreen();
    int id = inputInt("Masukkan ID (0 = kembali): ");
    if (id == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    Warga w;
    int found = 0;

    while (f && fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == id) {
            printf("Ditemukan:\nID:%d\nNama:%s\nUmur:%d\n", w.id, w.nama, w.umur);
            found = 1;
            break;
        }
    }

    if (!found) printf("Data tidak ditemukan.\n");
    if (f) fclose(f);
    pauseScreen();
}

void cariWargaByNama() {
    clearScreen();
    char key[50];
    inputString("Masukkan nama: ", key, sizeof(key));

    FILE *f = fopen(FILE_WARGA, "r");
    Warga w;
    int found = 0;

    while (f && fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (strstr(w.nama, key)) {
            printf("ID:%d | %s | Umur:%d\n", w.id, w.nama, w.umur);
            found = 1;
        }
    }

    if (!found) printf("Tidak ditemukan.\n");
    if (f) fclose(f);
    pauseScreen();
}

void lihatWarga() {
    int p;
    do {
        clearScreen();
        printf("=== LIHAT DATA WARGA ===\n");
        printf("1. Tampilkan Semua\n");
        printf("2. Cari ID\n");
        printf("3. Cari Nama\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        if (p == 1) tampilkanSemuaWarga();
        else if (p == 2) cariWargaById();
        else if (p == 3) cariWargaByNama();

    } while (p != 0);
}

/* ================= EDIT ================= */
void editWarga() {
    clearScreen();
    int id = inputInt("Masukkan ID (0 = batal): ");
    if (id == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Warga w;
    int found = 0;

    while (f && fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == id) {
            found = 1;
            inputString("Nama baru: ", w.nama, sizeof(w.nama));
            w.umur = inputInt("Umur baru: ");
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    if (f) fclose(f);
    fclose(tmp);

    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    printf(found ? "Data diupdate!\n" : "ID tidak ditemukan!\n");
    pauseScreen();
}

/* ================= HAPUS ================= */
void hapusWarga() {
    clearScreen();
    int id = inputInt("Masukkan ID (0 = batal): ");
    if (id == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Warga w;
    int found = 0;

    while (f && fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == id) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    if (f) fclose(f);
    fclose(tmp);

    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    printf(found ? "Data dihapus!\n" : "ID tidak ditemukan!\n");
    pauseScreen();
}

/* ================= MENU ================= */
void menuWarga() {
    int p;
    do {
        clearScreen();
        printf("=== CRUD DATA WARGA ===\n");
        printf("1. Tambah\n");
        printf("2. Lihat\n");
        printf("3. Edit\n");
        printf("4. Hapus\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        if (p == 1) tambahWarga();
        else if (p == 2) lihatWarga();
        else if (p == 3) editWarga();
        else if (p == 4) hapusWarga();

    } while (p != 0);
}
