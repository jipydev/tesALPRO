#ifndef UTILS_H
#define UTILS_H

/* =======================
   Fungsi Tampilan
   ======================= */
void clearScreen();     // membersihkan layar
void pauseScreen();     // pause sebelum lanjut

/* =======================
   Fungsi Input Aman
   ======================= */
int inputInt(const char *label);                      
void inputString(const char *label, char *output, int max);

/* =======================
   Manajemen Folder
   ======================= */
void protectFolder();   // memastikan folder db/ ada

#endif
