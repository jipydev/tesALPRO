#include <stdio.h>
#include <string.h>
#include "inventaris.h"
#include "utils.h"

#define FILE_INV "db/inventaris.txt"
#define FILE_TEMP "db/tmp.txt"

typedef struct {
    char barang[50];
    int jumlah;
} Inventaris;

void tambahInv() {
    FILE *f = fopen(FILE_INV, "a");
    Inventaris i;

    printf("Nama barang: "); getchar(); fgets(i.barang, 50, stdin); trim(i.barang);
    printf("Jumlah: "); scanf("%d", &i.jumlah);

    fprintf(f, "%s|%d\n", i.barang, i.jumlah);
    fclose(f);

    printf("Inventaris ditambah!\n");
    pauseScreen();
}

void lihatInv() {
    FILE *f = fopen(FILE_INV, "r");
    Inventaris i;

    printf("\n=== DATA INVENTARIS ===\n");
    while (fscanf(f, "%49[^|]|%d\n", i.barang, &i.jumlah) != EOF)
        printf("%s → %d pcs\n", i.barang, i.jumlah);

    fclose(f);
    pauseScreen();
}

void editInv() {
    char cari[50];
    printf("Nama barang yang ingin diedit: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_INV, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Inventaris i;
    int found = 0;

    while (fscanf(f, "%49[^|]|%d\n", i.barang, &i.jumlah) != EOF) {
        if (strcmp(i.barang, cari) == 0) {
            found = 1;
            printf("Barang baru: "); fgets(i.barang, 50, stdin); trim(i.barang);
            printf("Jumlah baru: "); scanf("%d", &i.jumlah);
        }
        fprintf(tmp, "%s|%d\n", i.barang, i.jumlah);
    }

    fclose(f); fclose(tmp);
    remove(FILE_INV);
    rename(FILE_TEMP, FILE_INV);

    if (found) printf("Inventaris berhasil diubah!\n");
    else printf("Barang tidak ditemukan.\n");

    pauseScreen();
}

void hapusInv() {
    char cari[50];
    printf("Nama barang yang ingin dihapus: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_INV, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Inventaris i;
    int found = 0;

    while (fscanf(f, "%49[^|]|%d\n", i.barang, &i.jumlah) != EOF) {
        if (strcmp(i.barang, cari) == 0) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%s|%d\n", i.barang, i.jumlah);
    }

    fclose(f); fclose(tmp);
    remove(FILE_INV);
    rename(FILE_TEMP, FILE_INV);

    if (found) printf("Barang berhasil dihapus!\n");
    else printf("Nama tidak ditemukan.\n");

    pauseScreen();
}

void menuInventaris() {
    int p;
    do {
        clearScreen();
        printf("=== MENU INVENTARIS ===\n");
        printf("1. Tambah\n2. Lihat\n3. Edit\n4. Hapus\n0. Kembali\nPilih: ");
        scanf("%d", &p);

        if (p == 1) tambahInv();
        if (p == 2) lihatInv();
        if (p == 3) editInv();
        if (p == 4) hapusInv();

    } while (p != 0);
}
