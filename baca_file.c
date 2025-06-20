#include <stdio.h>
#include "dasar.h"

int baca_dokter(const Dokter *dokter_list, int jumlah) {
    if (jumlah <= 0) {
        printf("Tidak ada data dokter untuk ditampilkan.\n");
        return -1;
    }

    printf("\n=== DAFTAR DOKTER ===\n");
    print_dokter_list(dokter_list, jumlah);
    return 0;
}

int baca_jadwal(const Jadwal *jadwal_list, int jumlah) {
    if (jumlah <= 0) {
        printf("Tidak ada data jadwal untuk ditampilkan.\n");
        return -1;
    }

    printf("\n=== DAFTAR JADWAL ===\n");
    print_jadwal_list(jadwal_list, jumlah);
    return 0;
}
