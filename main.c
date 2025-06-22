#include <stdio.h>
#include <stdlib.h>
#include "dasar.h"
#include "baca_file.h"
#include "pelanggaran.h"
#include "pengelolaan.h"


#define MAX_DOKTER 100
#define MAX_JADWAL 31  // Anggap maksimal 31 hari

int main() {
    // Array dokter dan jadwal
    Dokter dokter_list[MAX_DOKTER];
    Jadwal jadwal_list[MAX_JADWAL];

    // Baca data dari file CSV
    int jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, MAX_DOKTER);
    int jumlah_jadwal = csv_to_jadwal("jadwal.csv", jadwal_list, MAX_JADWAL);

    // Validasi
    if (jumlah_dokter < 0 || jumlah_jadwal < 0) {
        printf("Gagal membaca data dari file.\n");
        return 1;
    }

     // Tampilkan dataMore actions
    baca_dokter(dokter_list, jumlah_dokter);
    baca_jadwal(jadwal_list, jumlah_jadwal);

    // Simpan ulang untuk uji write
    dokter_to_csv("dokter_output.csv", dokter_list, jumlah_dokter);
    jadwal_to_csv("jadwal_output.csv", jadwal_list, jumlah_jadwal);

    // Bebaskan memori dari alokasi array dinamis dalam Jadwal
    for (int i = 0; i < jumlah_jadwal; i++) {
        free(jadwal_list[i].pagi);
        free(jadwal_list[i].siang);
        free(jadwal_list[i].malam);
    }

    return 0;
}
