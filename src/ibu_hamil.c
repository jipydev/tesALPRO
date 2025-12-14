#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ibu_hamil.h"
#include "utils.h"

#define FILE_HAMIL "db/ibu_hamil.txt"
#define FILE_TMP   "db/tmp_hamil.txt"

typedef struct {
    int id;
    char nama[50];
    int usia_minggu;
    float berat;
    int sistolik;
    int diastolik;
    float hb;
    char tanggal[20];
    char status[50];
} IbuHamil;

/* =======================
   LOGIKA STATUS KESEHATAN
   ======================= */
void tentukanStatus(IbuHamil *i) {
    if (i->hb < 11)
        strcpy(i->status, "ANEMIA");
    else if (i->sistolik >= 140 || i->diastolik >= 90)
        strcpy(i->status, "HIPERTENSI");
    else
        strcpy(i->status, "NORMAL");
}

/* =======================
   TAMBAH DATA
   ======================= */
void tambahIbuHamil() {
    clearScreen();
    printf("=== TAMBAH DATA IBU HAMIL ===\n");

    IbuHamil i;
    int id = inputInt("ID: ");

    FILE *f = fopen(FILE_HAMIL, "r");

    /* CEK ID DUPLIKAT */
    if (f) {
        while (fscanf(f,
            "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
            &i.id, i.nama, &i.usia_minggu, &i.berat,
            &i.sistolik, &i.diastolik, &i.hb,
            i.tanggal, i.status) != EOF) {

            if (i.id == id) {
                printf("ID sudah terdaftar!\n");
                fclose(f);
                pauseScreen();
                return;
            }
        }
        fclose(f);
    }

    i.id = id;
    inputString("Nama ibu: ", i.nama, sizeof(i.nama));
    i.usia_minggu = inputInt("Usia kehamilan (minggu): ");

    printf("Berat badan (kg): ");
    scanf("%f", &i.berat);
    while (getchar() != '\n');

    i.sistolik = inputInt("Tekanan sistolik: ");
    i.diastolik = inputInt("Tekanan diastolik: ");

    printf("HB (g/dL): ");
    scanf("%f", &i.hb);
    while (getchar() != '\n');

    inputString("Tanggal (contoh: 12-09-2025): ",
                i.tanggal, sizeof(i.tanggal));

    tentukanStatus(&i);

    f = fopen(FILE_HAMIL, "a");
    if (!f) {
        printf("Gagal membuka file.\n");
        pauseScreen();
        return;
    }

    fprintf(f, "%d|%s|%d|%.1f|%d|%d|%.1f|%s|%s\n",
            i.id, i.nama, i.usia_minggu, i.berat,
            i.sistolik, i.diastolik, i.hb,
            i.tanggal, i.status);

    fclose(f);
    printf("Data berhasil ditambahkan!\n");
    pauseScreen();
}

/* =======================
   TAMPILKAN SEMUA
   ======================= */
void tampilkanSemuaIbuHamil() {
    clearScreen();
    FILE *f = fopen(FILE_HAMIL, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    IbuHamil i;
    printf("=== DATA IBU HAMIL ===\n");

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        printf("ID:%d | %s | HB:%.1f | TD:%d/%d | %s | %s\n",
               i.id, i.nama, i.hb,
               i.sistolik, i.diastolik,
               i.status, i.tanggal);
    }

    fclose(f);
    pauseScreen();
}

/* =======================
   CARI BY ID
   ======================= */
void cariIbuHamilById() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");

    FILE *f = fopen(FILE_HAMIL, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    IbuHamil i;
    int found = 0;

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        if (i.id == id) {
            printf("\nNama: %s\nHB: %.1f\nTD: %d/%d\nStatus: %s\nTanggal: %s\n",
                   i.nama, i.hb, i.sistolik, i.diastolik, i.status, i.tanggal);
            found = 1;
            break;
        }
    }

    fclose(f);
    if (!found) printf("ID tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   CARI BY STATUS
   ======================= */
void cariIbuHamilByStatus() {
    clearScreen();
    char cari[20];
    inputString("Masukkan status (NORMAL/ANEMIA/HIPERTENSI): ",
                cari, sizeof(cari));

    FILE *f = fopen(FILE_HAMIL, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    IbuHamil i;
    int found = 0;

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        if (strcmp(i.status, cari) == 0) {
            printf("ID:%d | %s | %s | %s\n",
                   i.id, i.nama, i.status, i.tanggal);
            found = 1;
        }
    }

    fclose(f);
    if (!found) printf("Data tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   CARI BY TANGGAL
   ======================= */
void cariIbuHamilByTanggal() {
    clearScreen();
    char cari[20];
    inputString("Masukkan tanggal (contoh: 12-09-2025): ",
                cari, sizeof(cari));

    FILE *f = fopen(FILE_HAMIL, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    IbuHamil i;
    int found = 0;

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        if (strcmp(i.tanggal, cari) == 0) {
            printf("ID:%d | %s | %s\n",
                   i.id, i.nama, i.status);
            found = 1;
        }
    }

    fclose(f);
    if (!found) printf("Data tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   SUBMENU LIHAT
   ======================= */
void lihatIbuHamil() {
    int p;
    do {
        clearScreen();
        printf("=== LIHAT DATA IBU HAMIL ===\n");
        printf("1. Tampilkan Semua\n");
        printf("2. Cari berdasarkan ID\n");
        printf("3. Cari berdasarkan Status\n");
        printf("4. Cari berdasarkan Tanggal\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        switch (p) {
            case 1: tampilkanSemuaIbuHamil(); break;
            case 2: cariIbuHamilById(); break;
            case 3: cariIbuHamilByStatus(); break;
            case 4: cariIbuHamilByTanggal(); break;
        }
    } while (p != 0);
}

/* =======================
   EDIT DATA
   ======================= */
void editIbuHamil() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");

    FILE *f = fopen(FILE_HAMIL, "r");
    FILE *tmp = fopen(FILE_TMP, "w");
    IbuHamil i;
    int found = 0;

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        if (i.id == id) {
            found = 1;
            inputString("Nama baru: ", i.nama, sizeof(i.nama));
            i.usia_minggu = inputInt("Usia kehamilan baru: ");

            printf("Berat badan baru: ");
            scanf("%f", &i.berat);
            while (getchar() != '\n');

            i.sistolik = inputInt("Sistolik baru: ");
            i.diastolik = inputInt("Diastolik baru: ");

            printf("HB baru: ");
            scanf("%f", &i.hb);
            while (getchar() != '\n');

            inputString("Tanggal baru: ", i.tanggal, sizeof(i.tanggal));
            tentukanStatus(&i);
        }

        fprintf(tmp, "%d|%s|%d|%.1f|%d|%d|%.1f|%s|%s\n",
                i.id, i.nama, i.usia_minggu, i.berat,
                i.sistolik, i.diastolik, i.hb,
                i.tanggal, i.status);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_HAMIL);
    rename(FILE_TMP, FILE_HAMIL);

    if (found) printf("Data berhasil diubah!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

/* =======================
   HAPUS DATA
   ======================= */
void hapusIbuHamil() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");

    FILE *f = fopen(FILE_HAMIL, "r");
    FILE *tmp = fopen(FILE_TMP, "w");
    IbuHamil i;
    int found = 0;

    while (fscanf(f,
        "%d|%49[^|]|%d|%f|%d|%d|%f|%19[^|]|%49[^\n]\n",
        &i.id, i.nama, &i.usia_minggu, &i.berat,
        &i.sistolik, &i.diastolik, &i.hb,
        i.tanggal, i.status) != EOF) {

        if (i.id == id) {
            found = 1;
            continue;
        }

        fprintf(tmp, "%d|%s|%d|%.1f|%d|%d|%.1f|%s|%s\n",
                i.id, i.nama, i.usia_minggu, i.berat,
                i.sistolik, i.diastolik, i.hb,
                i.tanggal, i.status);
    }

    fclose(f);
    fclose(tmp);
    remove(FILE_HAMIL);
    rename(FILE_TMP, FILE_HAMIL);

    if (found) printf("Data berhasil dihapus!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

/* =======================
   MENU UTAMA
   ======================= */
void menuIbuHamil() {
    int p;
    do {
        clearScreen();
        printf("=== MENU CEK IBU HAMIL ===\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("3. Edit Data\n");
        printf("4. Hapus Data\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        if (p == 1) tambahIbuHamil();
        else if (p == 2) lihatIbuHamil();
        else if (p == 3) editIbuHamil();
        else if (p == 4) hapusIbuHamil();

    } while (p != 0);
}
