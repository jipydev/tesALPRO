#ifndef DATA_WARGA_H
#define DATA_WARGA_H

// Struktur data warga
typedef struct {
    int id;
    char nama[50];
    int umur;
} Warga;

// Deklarasi fungsi CRUD
void tambahWarga();
void lihatWarga();
void editWarga();
void hapusWarga();
void menuWarga();

// Deklarasi fungsi tambahan
void tampilkanSemuaWarga();
void cariWargaById();
void cariWargaByNama();

#endif
