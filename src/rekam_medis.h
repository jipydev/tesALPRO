#ifndef REKAM_H
#define REKAM_H

typedef struct {
    char nama[50];
    char keluhan[100];
} Rekam;

void menuRekam();
void tambahRekam();
void lihatRekam();
void tampilkanSemuaRekam();
void cariRekamByNama();
void editRekam();
void hapusRekam();

#endif
