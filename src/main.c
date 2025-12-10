#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "data_warga.h"
#include "rekam_medis.h"
#include "cek_stunting.h"
#include "ibu_hamil.h"
#include "jadwal_kegiatan.h"
#include "inventaris.h"
#include "laporan_keuangan.h"

int main() {
    protectFolder();
    int pilih;

    while (1) {
        clearScreen();
        printf("===================================================\n");
        printf("SIPANDU (Sistem Informasi Posyandu Digital Terpadu)\n");
        printf("===================================================\n");
        printf("1. CRUD Data Warga\n");
        printf("2. CRUD Rekam Medis\n");
        printf("3. Cek Stunting Balita\n");
        printf("4. Cek Kesehatan Ibu Hamil\n");
        printf("5. CRUD Jadwal Kegiatan\n");
        printf("6. CRUD Inventaris\n");
        printf("7. CRUD Laporan Keuangan\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1: menuWarga(); break;
            case 2: menuRekam(); break;
            case 3: cekStunting(); break;
            case 4: cekIbuHamil(); break;
            case 5: menuJadwal(); break;
            case 6: menuInventaris(); break;
            case 7: menuKeuangan(); break;
            case 0: exit(0);
            default:
                printf("Pilihan tidak ada!\n");
                pauseScreen();
        }
    }
}
