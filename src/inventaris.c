#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventaris.h"
#include "utils.h"

#define FILE_INV  "db/inventaris.txt"
#define FILE_TEMP "db/tmp.txt"

typedef struct {
    int id;
    char barang[50];
    int jumlah;
    char tanggal[20];
} Inventaris;

/* =======================
   TAMBAH INVENTARIS
   ======================= */
void tambahInv() {
    clearScreen();
    printf("=== TAMBAH INVENTARIS ===\n");

    int id = inputInt("Masukkan ID: ");
    FILE *f = fopen(FILE_INV, "r");
    Inventaris i;

    // cek ID duplikat
    if (f) {
        while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                      &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
            if (i.id == id) {
                printf("ID sudah ada!\n");
                fclose(f);
                pauseScreen();
                return;
            }
        }
        fclose(f);
    }

    f = fopen(FILE_INV, "a");
    if (!f) {
        printf("Gagal membuka file.\n");
        pauseScreen();
        return;
    }

    i.id = id;
    inputString("Nama barang: ", i.barang, sizeof(i.barang));
    i.jumlah = inputInt("Jumlah: ");
    inputString("Tanggal (YYYY-MM-DD): ", i.tanggal, sizeof(i.tanggal));

    fprintf(f, "%d|%s|%d|%s\n",
            i.id, i.barang, i.jumlah, i.tanggal);

    fclose(f);
    printf("Inventaris berhasil ditambahkan!\n");
    pauseScreen();
}

/* =======================
   TAMPILKAN SEMUA
   ======================= */
void tampilkanSemuaInv() {
    clearScreen();
    FILE *f = fopen(FILE_INV, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    Inventaris i;
    printf("=== DATA INVENTARIS ===\n");
    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        printf("ID:%d | %s | %d pcs | %s\n",
               i.id, i.barang, i.jumlah, i.tanggal);
    }

    fclose(f);
    pauseScreen();
}

/* =======================
   CARI BERDASARKAN ID
   ======================= */
void cariInvById() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");
    FILE *f = fopen(FILE_INV, "r");

    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    Inventaris i;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (i.id == id) {
            printf("ID:%d\nBarang:%s\nJumlah:%d\nTanggal:%s\n",
                   i.id, i.barang, i.jumlah, i.tanggal);
            found = 1;
            break;
        }
    }

    fclose(f);
    if (!found) printf("ID tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   CARI BERDASARKAN NAMA
   ======================= */
void cariInvByNama() {
    clearScreen();
    char key[50];
    inputString("Masukkan nama barang: ", key, sizeof(key));

    FILE *f = fopen(FILE_INV, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    Inventaris i;
    int found = 0;

    printf("\nHASIL PENCARIAN:\n");
    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (strstr(i.barang, key)) {
            printf("ID:%d | %s | %d pcs | %s\n",
                   i.id, i.barang, i.jumlah, i.tanggal);
            found = 1;
        }
    }

    fclose(f);
    if (!found) printf("Data tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   CARI BERDASARKAN JUMLAH
   ======================= */
void cariInvByJumlah() {
    clearScreen();
    int cari = inputInt("Masukkan jumlah: ");

    FILE *f = fopen(FILE_INV, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    Inventaris i;
    int found = 0;

    printf("\nHASIL PENCARIAN:\n");
    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (i.jumlah == cari) {
            printf("ID:%d | %s | %d pcs | %s\n",
                   i.id, i.barang, i.jumlah, i.tanggal);
            found = 1;
        }
    }

    fclose(f);
    if (!found) printf("Data tidak ditemukan.\n");
    pauseScreen();
}

/* =======================
   CARI BERDASARKAN TANGGAL
   ======================= */
void cariInvByTanggal() {
    clearScreen();
    char cari[20];
    inputString("Masukkan tanggal (YYYY-MM-DD): ", cari, sizeof(cari));

    FILE *f = fopen(FILE_INV, "r");
    if (!f) {
        printf("Belum ada data.\n");
        pauseScreen();
        return;
    }

    Inventaris i;
    int found = 0;

    printf("\nHASIL PENCARIAN:\n");
    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (strcmp(i.tanggal, cari) == 0) {
            printf("ID:%d | %s | %d pcs | %s\n",
                   i.id, i.barang, i.jumlah, i.tanggal);
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
void lihatInv() {
    int p;
    do {
        clearScreen();
        printf("=== LIHAT INVENTARIS ===\n");
        printf("1. Tampilkan Semua\n");
        printf("2. Cari berdasarkan ID\n");
        printf("3. Cari berdasarkan Nama\n");
        printf("4. Cari berdasarkan Jumlah\n");
        printf("5. Cari berdasarkan Tanggal Dibuat\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        switch (p) {
            case 1: tampilkanSemuaInv(); break;
            case 2: cariInvById(); break;
            case 3: cariInvByNama(); break;
            case 4: cariInvByJumlah(); break;
            case 5: cariInvByTanggal(); break;
        }
    } while (p != 0);
}

/* =======================
   EDIT INVENTARIS
   ======================= */
void editInv() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");

    FILE *f = fopen(FILE_INV, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Inventaris i;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (i.id == id) {
            found = 1;
            inputString("Nama barang baru: ", i.barang, sizeof(i.barang));
            i.jumlah = inputInt("Jumlah baru: ");
            inputString("Tanggal baru: ", i.tanggal, sizeof(i.tanggal));
        }
        fprintf(tmp, "%d|%s|%d|%s\n",
                i.id, i.barang, i.jumlah, i.tanggal);
    }

    fclose(f); fclose(tmp);
    remove(FILE_INV);
    rename(FILE_TEMP, FILE_INV);

    if (found) printf("Data berhasil diubah!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

/* =======================
   HAPUS INVENTARIS
   ======================= */
void hapusInv() {
    clearScreen();
    int id = inputInt("Masukkan ID: ");

    FILE *f = fopen(FILE_INV, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Inventaris i;
    int found = 0;

    while (fscanf(f, "%d|%49[^|]|%d|%19[^\n]\n",
                  &i.id, i.barang, &i.jumlah, i.tanggal) != EOF) {
        if (i.id == id) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%d|%s|%d|%s\n",
                i.id, i.barang, i.jumlah, i.tanggal);
    }

    fclose(f); fclose(tmp);
    remove(FILE_INV);
    rename(FILE_TEMP, FILE_INV);

    if (found) printf("Data berhasil dihapus!\n");
    else printf("ID tidak ditemukan.\n");

    pauseScreen();
}

/* =======================
   MENU UTAMA INVENTARIS
   ======================= */
void menuInventaris() {
    int p;
    do {
        clearScreen();
        printf("=== MENU INVENTARIS ===\n");
        printf("1. Tambah Data\n");
        printf("2. Lihat Data\n");
        printf("3. Edit Data\n");
        printf("4. Hapus Data\n");
        printf("0. Kembali\n");

        p = inputInt("Pilih: ");

        switch (p) {
            case 1: tambahInv(); break;
            case 2: lihatInv(); break;
            case 3: editInv(); break;
            case 4: hapusInv(); break;
        }
    } while (p != 0);
}
