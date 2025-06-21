#ifndef PELANGGARAN_H
#define PELANGGARAN_H

#include "dasar.h"

int FindIdx(Dokter dokter_list[], int id, int jumlah_dokter);
void PrintPelanggaran(Dokter dokter[], Jadwal jadwal[], int jumlah_dokter, int id, int hari, int tipewaktu);

#endif
