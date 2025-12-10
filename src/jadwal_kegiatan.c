#include <stdio.h>
#include <string.h>
#include "jadwal_kegiatan.h"
#include "utils.h"

#define FILE_JADWAL "db/jadwal_kegitan.txt"
#define FILE_TEMP "db/tmp.txt"

typedef struct {
    char kegiatan[50];
    char tanggal[30];
} Jadwal;

void tambahJadwal() {
    FILE *f = fopen(FILE_JADWAL, "a");
    Jadwal j;

    printf("Nama kegiatan: "); getchar(); fgets(j.kegiatan, 50, stdin); trim(j.kegiatan);
    printf("Tanggal: "); fgets(j.tanggal, 30, stdin); trim(j.tanggal);

    fprintf(f, "%s|%s\n", j.kegiatan, j.tanggal);
    fclose(f);

    printf("Jadwal ditambahkan!\n");
    pauseScreen();
}

void lihatJadwal() {
    FILE *f = fopen(FILE_JADWAL, "r");
    Jadwal j;

    printf("\n=== DAFTAR JADWAL ===\n");
    while (fscanf(f, "%49[^|]|%29[^\n]\n", j.kegiatan, j.tanggal) != EOF)
        printf("%s — %s\n", j.kegiatan, j.tanggal);

    fclose(f);
    pauseScreen();
}

void editJadwal() {
    char cari[50];
    printf("Nama kegiatan yang ingin diedit: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_JADWAL, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Jadwal j;

    int found = 0;

    while (fscanf(f, "%49[^|]|%29[^\n]\n", j.kegiatan, j.tanggal) != EOF) {
        if (strcmp(j.kegiatan, cari) == 0) {
            found = 1;
            printf("Kegiatan baru: "); fgets(j.kegiatan, 50, stdin); trim(j.kegiatan);
            printf("Tanggal baru: "); fgets(j.tanggal, 30, stdin); trim(j.tanggal);
        }
        fprintf(tmp, "%s|%s\n", j.kegiatan, j.tanggal);
    }

    fclose(f); fclose(tmp);
    remove(FILE_JADWAL);
    rename(FILE_TEMP, FILE_JADWAL);

    if (found) printf("Jadwal berhasil diubah!\n");
    else printf("Kegiatan tidak ditemukan.\n");

    pauseScreen();
}

void hapusJadwal() {
    char cari[50];
    printf("Nama kegiatan yang ingin dihapus: ");
    getchar(); fgets(cari, 50, stdin); trim(cari);

    FILE *f = fopen(FILE_JADWAL, "r");
    FILE *tmp = fopen(FILE_TEMP, "w");
    Jadwal j;

    int found = 0;

    while (fscanf(f, "%49[^|}|%29[^\n]\n", j.kegiatan, j.tanggal) != EOF) {
        if (strcmp(j.kegiatan, cari) == 0) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%s|%s\n", j.kegiatan, j.tanggal);
    }

    fclose(f); fclose(tmp);
    remove(FILE_JADWAL);
    rename(FILE_TEMP, FILE_JADWAL);

    if (found) printf("Jadwal dihapus!\n");
    else printf("Kegiatan tidak ditemukan.\n");

    pauseScreen();
}

void menuJadwal() {
    int p;
    do {
        clearScreen();
        printf("=== MENU JADWAL ===\n");
        printf("1. Tambah\n2. Lihat\n3. Edit\n4. Hapus\n0. Kembali\nPilih: ");
        scanf("%d", &p);

        if (p == 1) tambahJadwal();
        if (p == 2) lihatJadwal();
        if (p == 3) editJadwal();
        if (p == 4) hapusJadwal();

    } while (p != 0);
}
