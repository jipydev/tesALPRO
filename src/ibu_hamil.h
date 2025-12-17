#ifndef IBU_HAMIL_H
#define IBU_HAMIL_H

/* =======================
   STRUKTUR DATA
   ======================= */
typedef struct {
    int id;
    char nama[50];
    int usiaKehamilan;   // minggu
    float beratBadan;   // kg
    char resiko[30];    // NORMAL / RISIKO TINGGI
} IbuHamil;

/* =======================
   MENU UTAMA
   ======================= */
void menuIbuHamil();

/* =======================
   CRUD DATA
   ======================= */
void tambahIbuHamil();
void lihatIbuHamil();
void editIbuHamil();
void hapusIbuHamil();

/* =======================
   SUBMENU LIHAT
   ======================= */
void tampilkanSemuaIbuHamil();
void cariIbuHamilById();
void cariIbuHamilByNama();

/* =======================
   LOGIKA KESEHATAN
   ======================= */
void tentukanResiko(IbuHamil *i);

#endif
