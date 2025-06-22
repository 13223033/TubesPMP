#ifndef PENGELOLAAN_H
#define PENGELOLAAN_H

#include "dasar.h"  

// Fungsi menu utama pengelolaan
void menu_pengelolaan_dokter(const char *nama_file);


int tambah_dokter(Dokter *list, int *jumlah,
                  const char *nama, int maks_shift,
                  int pagi, int siang, int malam);

int hapus_dokter(Dokter *list, int *jumlah, int id);

#endif
