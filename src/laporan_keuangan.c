#include <stdio.h>
#include <string.h>
#include "laporan_keuangan.h"
#include "utils.h"

#define FILE_KEU "db/laporan_keuangan.txt"
#define FILE_TEMP "db/temp.txt"

typedef struct {
    char ket[100];
    int jumlah;
} Keuangan;

void tambahKeu() {
    FILE *f = fopen(FILE_KEU, "a");
    Keuangan k;

    printf("Deskripsi: "); getchar(); fgets(k.ket, 100, stdin); trim(k.ket);
    printf("Jumlah (Rp): "); scanf("%d", &k.jumlah);

    fprintf(f, "%s|%d\n", k.ket, k.jumlah);
    fclose(f);

    printf("Laporan ditambah!\n");
    pauseScreen();
}

void lihatKeu() {
    FILE *f = fopen(FILE_KEU, "r");
    Keuangan k;

    printf("\n=== LAPORAN KEUANGAN ===\n");
    while (fscanf(f, "%99[^|]|%d\n", k.ket, &k.jumlah) != EOF)
        printf("%s — Rp %d\n", k.ket, k.jumlah);

    fclose(f);
    pauseScreen();
}

void editKeu() {
    char cari[100];
    printf("Deskripsi laporan yg ingin diedit: ");
    getchar(); fgets(cari, 100, stdin); trim(cari);

    FILE *f = fopen(FILE_KEU, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Keuangan k;
    int found = 0;

    while (fscanf(f, "%99[^|]|%d\n", k.ket, &k.jumlah) != EOF) {
        if (strcmp(k.ket, cari) == 0) {
            found = 1;
            printf("Deskripsi baru: "); fgets(k.ket, 100, stdin); trim(k.ket);
            printf("Jumlah baru: "); scanf("%d", &k.jumlah);
        }
        fprintf(tmp, "%s|%d\n", k.ket, k.jumlah);
    }

    fclose(f); fclose(tmp);
    remove(FILE_KEU);
    rename(FILE_TEMP, FILE_KEU);

    if (found) printf("Laporan berhasil diubah!\n");
    else printf("Deskripsi tidak ditemukan.\n");

    pauseScreen();
}

void hapusKeu() {
    char cari[100];
    printf("Deskripsi yang ingin dihapus: ");
    getchar(); fgets(cari, 100, stdin); trim(cari);

    FILE *f = fopen(FILE_KEU, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");

    Keuangan k;
    int found = 0;

    while (fscanf(f, "%99[^|]|%d\n", k.ket, &k.jumlah) != EOF) {
        if (strcmp(k.ket, cari) == 0) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%s|%d\n", k.ket, k.jumlah);
    }

    fclose(f); fclose(tmp);
    remove(FILE_KEU);
    rename(FILE_TEMP, FILE_KEU);

    if (found) printf("Laporan dihapus!\n");
    else printf("Deskripsi tidak ditemukan.\n");

    pauseScreen();
}

void menuKeuangan() {
    int p;
    do {
        clearScreen();
        printf("=== MENU KEUANGAN ===\n");
        printf("1. Tambah\n2. Lihat\n3. Edit\n4. Hapus\n0. Kembali\nPilih: ");
        scanf("%d", &p);

        if (p == 1) tambahKeu();
        if (p == 2) lihatKeu();
        if (p == 3) editKeu();
        if (p == 4) hapusKeu();

    } while (p != 0);
}
