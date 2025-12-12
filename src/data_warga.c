#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_warga.h"
#include "utils.h"

#define FILE_WARGA "db/data_warga.txt"
#define FILE_TEMP "db/temp.txt"



void tambahWarga() {
    clearScreen();
    printf("=== TAMBAH DATA WARGA ===\n");
    printf("Masukkan 0 untuk kembali.\n\n");

    int inputId;
    printf("ID: ");
    scanf("%d", &inputId);

    if (inputId == 0) return; // <-- kembali

    // Cek apakah ID sudah ada
    FILE *f = fopen(FILE_WARGA, "r");
    Warga temp;

    if (f) {
        while (fscanf(f, "%d|%49[^|]|%d\n", &temp.id, temp.nama, &temp.umur) != EOF) {
            if (temp.id == inputId) {
                printf("\nERROR: ID sudah terpakai!\n");
                pauseScreen();
                fclose(f);
                return;
            }
        }
        fclose(f);
    }

    Warga w;
    w.id = inputId;

    printf("Nama: ");
    getchar();
    fgets(w.nama, 50, stdin);
    trim(w.nama);

    printf("Umur: ");
    scanf("%d", &w.umur);

    f = fopen(FILE_WARGA, "a");
    fprintf(f, "%d|%s|%d\n", w.id, w.nama, w.umur);
    fclose(f);

    printf("\nData warga BERHASIL ditambahkan!\n");
    pauseScreen();
}



void lihatWarga() {
    int p;
    do {
        clearScreen();
        printf("=== LIHAT DATA WARGA ===\n");
        printf("1. Tampilkan Semua\n");
        printf("2. Cari berdasarkan ID\n");
        printf("3. Cari berdasarkan Nama\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &p);

        switch (p) {
            case 1: tampilkanSemuaWarga(); break;
            case 2: cariWargaById(); break;
            case 3: cariWargaByNama(); break;
        }
    } while (p != 0);
}


void tampilkanSemuaWarga() {
    clearScreen();
    printf("=== DATA WARGA ===\n");

    FILE *f = fopen(FILE_WARGA, "r");
    if (!f) {
        printf("Belum ada data!\n");
        pauseScreen();
        return;
    }

    Warga w;
    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        printf("ID:%d | %s | Umur:%d\n", w.id, w.nama, w.umur);
    }
    fclose(f);

    pauseScreen();
}

void cariWargaByNama() {
    clearScreen();
    char keyword[50];

    printf("Masukkan nama yang dicari: ");
    getchar();
    fgets(keyword, 50, stdin);
    trim(keyword);

    FILE *f = fopen(FILE_WARGA, "r");
    if (!f) {
        printf("Belum ada data!\n");
        pauseScreen();
        return;
    }

    Warga w;
    int found = 0;

    printf("\n=== HASIL PENCARIAN ===\n");
    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (strstr(w.nama, keyword) != NULL) {
            printf("ID:%d | Nama:%s | Umur:%d\n", w.id, w.nama, w.umur);
            found = 1;
        }
    }
    fclose(f);

    if (!found) printf("Tidak ada data cocok dengan '%s'.\n", keyword);
    pauseScreen();
}

void cariWargaById() {
    clearScreen();
    int id;
    printf("Masukkan ID yang dicari: ");
    scanf("%d", &id);

    FILE *f = fopen(FILE_WARGA, "r");
    if (!f) {
        printf("Belum ada data!\n");
        pauseScreen();
        return;
    }

    Warga w;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == id) {
            printf("\n=== DATA DITEMUKAN ===\n");
            printf("ID: %d\nNama: %s\nUmur: %d\n", w.id, w.nama, w.umur);
            found = 1;
            break;
        }
    }
    fclose(f);

    if (!found) printf("Data dengan ID %d tidak ditemukan.\n", id);
    pauseScreen();
}



void editWarga() {
    clearScreen();
    printf("=== EDIT DATA WARGA ===\n");
    printf("Masukkan 0 untuk kembali.\n\n");

    int editId;
    printf("ID yang ingin diedit: ");
    scanf("%d", &editId);

    if (editId == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    if (!f || !tmp) return;

    Warga w;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == editId) {
            found = 1;

            printf("\nNama baru (0 untuk batal): ");
            getchar();
            fgets(w.nama, 50, stdin);
            trim(w.nama);
            if (strcmp(w.nama, "0") == 0) { fclose(f); fclose(tmp); return; }

            printf("Umur baru: ");
            scanf("%d", &w.umur);
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    if (found) printf("Data berhasil diubah!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}


void hapusWarga() {
    clearScreen();
    printf("=== HAPUS DATA WARGA ===\n");
    printf("Masukkan 0 untuk kembali.\n\n");

    int hapusId;
    printf("ID yang ingin dihapus: ");
    scanf("%d", &hapusId);

    if (hapusId == 0) return;

    FILE *f = fopen(FILE_WARGA, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Warga w;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d\n", &w.id, w.nama, &w.umur) != EOF) {
        if (w.id == hapusId) {
            found = 1;
            continue; // skip → menghapus
        }
        fprintf(tmp, "%d|%s|%d\n", w.id, w.nama, w.umur);
    }

    fclose(f);
    fclose(tmp);

    remove(FILE_WARGA);
    rename(FILE_TEMP, FILE_WARGA);

    if (found) printf("Data berhasil dihapus!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}


void menuWarga() {
    int p;
    while (1) {  // loop selamanya sampai break
        clearScreen();
        printf("=== MENU CRUD WARGA ===\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("3. Edit Data\n");
        printf("4. Hapus Data\n");
        printf("0. Kembali\n");
        printf("Pilih: ");

        // Validasi input (harus angka)
        if (scanf("%d", &p) != 1) {
            printf("\nInput tidak valid! Harus angka.\n");
            getchar();          // buang karakter salah
            pauseScreen();
            continue;           // kembali ke menu
        }

        switch (p) {
            case 1: tambahWarga(); break;
            case 2: lihatWarga(); break;
            case 3: editWarga(); break;
            case 4: hapusWarga(); break;
            case 0:
                return; // kembali ke menu utama
            default:
                printf("\nPilihan tidak tersedia!\n");
                pauseScreen();
        }
    }
}
