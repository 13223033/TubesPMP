#include <stdio.h>
#include <stdlib.h>
#include "dasar.h"
#include "baca_file.h"
#include "pelanggaran.h"
#include "pengelolaan.h"
#include "scheduling.h"
#include "tampilkanJadwal.h"

#define MAX_DOKTER 100
#define MAX_JADWAL 31  // Anggap maksimal 31 hari

int main() {
    // Array dokter dan jadwal
    Dokter dokter_list[MAX_DOKTER];
    Jadwal jadwal_list[MAX_JADWAL] = {0};

    // Baca data dari file CSV
    int jumlah_dokter = csv_to_dokter("data_dokter.csv", dokter_list, MAX_DOKTER);
    // int jumlah_jadwal = csv_to_jadwal("jadwal.csv", jadwal_list, MAX_JADWAL);

    int jadwal_created = 0;

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
        puts("4. Cek pelanggaran");
        puts("0. Keluar");
        printf("Pilihan: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            if (!jadwal_created) {
                printf("Jadwal belum dibuat! Silakan pilih opsi 3 untuk membuat jadwal terlebih dahulu.\n");
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

            jadwal_created = 1;
            printf("Jadwal berhasil dibuat!\n");
        }
        else if (pilih == 4){
            if (!jadwal_created) {
                printf("Jadwal belum dibuat! Silakan pilih opsi 3 untuk membuat jadwal terlebih dahulu.\n");
            } else {
                int id = 0; int opsi_pelanggaran;
                puts("\n=== MENU CEK PELANGGARAN ===");
                puts("1. Lihat pelanggaran dokter tertentu");
                puts("2. Lihat total pelanggaran semua dokter");
                printf("Pilihan: ");
                scanf("%d", &opsi_pelanggaran);

                if (opsi_pelanggaran == 1 || opsi_pelanggaran == 2){
                    if (opsi_pelanggaran == 1){
                        printf("\nMasukkan id dokter: ");
                        scanf("%d", &id);
                    }

                    printf("\nPelanggaran untuk id %d, hari pertama:\n", id);
                    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 0);

                    printf("\n");
                    printf("Pelanggaran untuk id %d, seminggu:\n", id);
                    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 1);

                    printf("\n");
                    printf("Pelanggaran untuk id %d, sebulan:\n", id);
                    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 2);

                    printf("\n");
                    printf("Pelanggaran total, seminggu:\n", id);
                    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 1);

                    printf("\n");
                    printf("Pelanggaran total, sebulan:\n", id);
                    PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 2);
                }
            }
        }

    } while (pilih != 0);

    // Simpan ulang untuk uji write
    dokter_to_csv("dokter_output.csv", dokter_list, jumlah_dokter);
    jadwal_to_csv("jadwal_output.csv", jadwal_list, 7);

    // Bebaskan memori dari alokasi array dinamis dalam Jadwal
    reset_jadwal(jadwal_list, dokter_list, jumlah_dokter, 0);

    return 0;
}
