// main.c
#include <stdio.h>
#include <string.h>
#include "dasar.h"

int main() {
    Dokter dokter_list[100];
    int jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, 100);

    if (jumlah_dokter < 0) {
        printf("Terjadi kesalahan saat membaca file.\n");
        return 1;
    }

    print_dokter_list(dokter_list, jumlah_dokter);

    // Tambahkan 1 dokter baru
    if (jumlah_dokter < 100) {
        Dokter baru;
        baru.id = dokter_list[jumlah_dokter - 1].id + 1; // id baru otomatis
        strcpy(baru.nama, "Andi");
        baru.maks_shift = 20;
        baru.pagi = 1;
        baru.siang = 0;
        baru.malam = 1;

        dokter_list[jumlah_dokter] = baru;
        jumlah_dokter++; // penting!
        printf("\nData dokter baru ditambahkan.\n\n");
    } else {
        printf("\nKapasitas penuh, tidak bisa tambah dokter baru.\n\n");
    }

    // Cetak ulang dan simpan
    print_dokter_list(dokter_list, jumlah_dokter);
    dokter_to_csv("data_dokter.csv", dokter_list, jumlah_dokter);

    Jadwal jadwal_list[100];
    int jumlah_jadwal = csv_to_jadwal("jadwal.csv", jadwal_list, 100);

    if (jumlah_jadwal > 0) {
        print_jadwal_list(jadwal_list, jumlah_jadwal);
        jadwal_to_csv("jadwal.csv", jadwal_list, jumlah_jadwal); // atau simpan ke file lain
    }


    return 0;
}
