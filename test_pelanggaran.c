#include <stdio.h>
#include <stdlib.h>
#include "dasar.h"
#include "baca_file.h"
#include "pelanggaran.h"

#define MAX_DOKTER 100
#define MAX_JADWAL 31  // Anggap maksimal 31 hari

int main() {
    // Array dokter dan jadwal
    Dokter dokter_list[MAX_DOKTER];
    Jadwal jadwal_list[MAX_JADWAL];

    // Baca data dari file CSV
    int jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, MAX_DOKTER);
    int jumlah_jadwal = csv_to_jadwal("jadwal_output.csv", jadwal_list, 7);

    // Validasi
    if (jumlah_dokter < 0 || jumlah_jadwal < 0) {
        printf("Gagal membaca data dari file.\n");
        return 1;
    }

    printf("Pelanggaran untuk id 1, hari pertama:\n");
    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 1, 0, 0);

    printf("\n");
    printf("Pelanggaran untuk id 1, seminggu:\n");
    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 1, 0, 1);

    printf("\n");
    printf("Pelanggaran untuk id 1, sebulan:\n");
    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 1, 0, 2);

    printf("\n");
    printf("Pelanggaran total, seminggu:\n");
    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 0, 0, 1);

    printf("\n");
    printf("Pelanggaran total, sebulan:\n");
    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 0, 0, 2);

    // Bebaskan memori dari alokasi array dinamis dalam Jadwal
    for (int i = 0; i < jumlah_jadwal; i++) {
        free(jadwal_list[i].pagi);
        free(jadwal_list[i].siang);
        free(jadwal_list[i].malam);
    }

    return 0;
}
