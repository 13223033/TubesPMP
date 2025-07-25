#include <stdio.h>
#include <stdlib.h>
#include "dasar.h"
#include "pelanggaran.h"
#include "pengelolaan.h"
#include "scheduling.h"
#include "tampilkanJadwal.h"

#define MAX_DOKTER 100

int main() {
    // Array dokter dan jadwal
    Dokter dokter_list[MAX_DOKTER];
    Jadwal jadwal_list[7] = {0};

    // Baca data dari file CSV
    int jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, MAX_DOKTER);
    int jumlah_jadwal = csv_to_jadwal("jadwal.csv", jadwal_list, 7);

    int jadwal_created = 0;
    if (jumlah_jadwal) jadwal_created = 1;

    // Validasi
    if (jumlah_dokter < 0) {
        printf("Gagal membaca data dari file.\n");
        return 1;
    }

    int pilih;
    do {
        puts("\n=== MENU UTAMA ===");
        puts("1. Tampilkan jadwal");
        puts("2. Pengelolaan dokter");
        puts("3. Buat jadwal");
        puts("0. Keluar");
        printf("Pilihan: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            if (!jadwal_created) {
                printf("Jadwal belum dibuat! Silakan pilih opsi 3 untuk membuat jadwal terlebih dahulu.\n");
                konfirmasi();
            } else {
                menu_tampilkan_jadwal(dokter_list, jumlah_dokter, jadwal_list);
            }
        } else if (pilih == 2) {
            menu_pengelolaan_dokter("data_dokter.csv");

            // Baca ulang data dokter setelah perubahan
            jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, MAX_DOKTER);
        }
        else if (pilih == 3){
            reset_jadwal(jadwal_list, dokter_list, jumlah_dokter, 1);
            scheduling_main(dokter_list, jumlah_dokter, jadwal_list);

            jadwal_to_csv("jadwal.csv", jadwal_list, 7);
            dokter_to_csv("data_dokter.csv", dokter_list, jumlah_dokter);

            jadwal_created = 1;
            printf("Jadwal berhasil dibuat!\n");
            konfirmasi();
        }
        else if (pilih == 0) {
            printf("Keluar dari program.\n");
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            konfirmasi();
            continue;
        }

    } while (pilih != 0);

    // Simpan5
    dokter_to_csv("data_dokter.csv", dokter_list, jumlah_dokter);
    jadwal_to_csv("jadwal.csv", jadwal_list, 7);

    // Bebaskan memori dari alokasi array dinamis dalam Jadwal
    reset_jadwal(jadwal_list, dokter_list, jumlah_dokter, 0);

    return 0;
}
