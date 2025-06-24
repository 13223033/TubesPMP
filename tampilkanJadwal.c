#include <stdio.h>
#include <string.h>
#include "tampilkanJadwal.h"
#include "pelanggaran.h"
#include "dasar.h"

const char* nama_hari[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

void tampilkan_jadwal_harian(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list, int hari) {
    if (hari < 0 || hari >= 7) {
        printf("Hari tidak valid!\n");
        return;
    }

    printf("\n=== JADWAL %s ===\n", nama_hari[hari]);
    printf("Pagi:\n");
    for (int i = 0; i < jadwal_list[hari].jumlah_pagi; i++) {
        int id = jadwal_list[hari].pagi[i];
        for (int j = 0; j < jumlah_dokter; j++) {
            if (dokter_list[j].id == id) {
                printf("- %s (ID: %d)\n", dokter_list[j].nama, id);
                break;
            }
        }
    }

    printf("\nSiang:\n");
    for (int i = 0; i < jadwal_list[hari].jumlah_siang; i++) {
        int id = jadwal_list[hari].siang[i];
        for (int j = 0; j < jumlah_dokter; j++) {
            if (dokter_list[j].id == id) {
                printf("- %s (ID: %d)\n", dokter_list[j].nama, id);
                break;
            }
        }
    }

    printf("\nMalam:\n");
    for (int i = 0; i < jadwal_list[hari].jumlah_malam; i++) {
        int id = jadwal_list[hari].malam[i];
        for (int j = 0; j < jumlah_dokter; j++) {
            if (dokter_list[j].id == id) {
                printf("- %s (ID: %d)\n", dokter_list[j].nama, id);
                break;
            }
        }
    }
}

void tampilkan_jadwal_mingguan(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list) {
    for (int hari = 0; hari < 7; hari++) {
        printf("\n=== %s ===\n", nama_hari[hari]);
        printf("Pagi: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_pagi; i++) {
            int id = jadwal_list[hari].pagi[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }

        printf("\nSiang: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_siang; i++) {
            int id = jadwal_list[hari].siang[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }

        printf("\nMalam: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_malam; i++) {
            int id = jadwal_list[hari].malam[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }
        printf("\n");
    }
}

void tampilkan_jadwal_bulanan(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list) {
    printf("\n=== JADWAL BULANAN ===\n");
    for (int minggu = 0; minggu < 4; minggu++) {
        printf("\nMINGGU KE-%d\n", minggu + 1);
        tampilkan_jadwal_mingguan(dokter_list, jumlah_dokter, jadwal_list);
    }
    printf("\nMINGGU KE-5\n");

    for (int hari = 0; hari < 2; hari++) {
        printf("\n=== %s ===\n", nama_hari[hari]);

        printf("Pagi: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_pagi; i++) {
            int id = jadwal_list[hari].pagi[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }

        printf("\nSiang: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_siang; i++) {
            int id = jadwal_list[hari].siang[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }

        printf("\nMalam: ");
        for (int i = 0; i < jadwal_list[hari].jumlah_malam; i++) {
            int id = jadwal_list[hari].malam[i];
            for (int j = 0; j < jumlah_dokter; j++) {
                if (dokter_list[j].id == id) {
                    printf("%s ", dokter_list[j].nama);
                    break;
                }
            }
        }
        printf("\n");
    }
}

void tampilkan_jadwal_dokter(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list, int id_dokter) {
    int idx = -1;
    for (int i = 0; i < jumlah_dokter; i++) {
        if (dokter_list[i].id == id_dokter) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Dokter dengan ID %d tidak ditemukan!\n", id_dokter);
        return;
    }

    printf("\n=== JADWAL DOKTER %s (ID: %d) ===\n", dokter_list[idx].nama, id_dokter);
    for (int hari = 0; hari < 7; hari++) {
        printf("%s: ", nama_hari[hari]);
        
        int ada_shift = 0;
        for (int i = 0; i < jadwal_list[hari].jumlah_pagi; i++) {
            if (jadwal_list[hari].pagi[i] == id_dokter) {
                printf("Pagi");
                ada_shift = 1;
                break;
            }
        }
        
        for (int i = 0; i < jadwal_list[hari].jumlah_siang; i++) {
            if (jadwal_list[hari].siang[i] == id_dokter) {
                if (ada_shift) printf(", ");
                printf("Siang");
                ada_shift = 1;
                break;
            }
        }
        
        for (int i = 0; i < jadwal_list[hari].jumlah_malam; i++) {
            if (jadwal_list[hari].malam[i] == id_dokter) {
                if (ada_shift) printf(", ");
                printf("Malam");
                ada_shift = 1;
                break;
            }
        }
        
        if (!ada_shift) {
            printf("Libur");
        }
        printf("\n");
    }
}

void menu_tampilkan_jadwal(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list) {
    int pilih;
    do {
        printf("\n=== MENU TAMPILKAN JADWAL ===\n");
        printf("1. Tampilkan jadwal harian\n");
        printf("2. Tampilkan jadwal mingguan\n");
        printf("3. Tampilkan jadwal bulanan\n");
        printf("4. Tampilkan jadwal dokter\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilih);

        if (pilih == 1) {
            int hari;
            printf("\nPilih hari (1-7):\n");
            for (int i = 0; i < 7; i++) {
                printf("%d. %s\n", i+1, nama_hari[i]);
            }
            printf("Pilihan: ");
            scanf("%d", &hari);
            if (hari >= 1 && hari <= 7) {
                tampilkan_jadwal_harian(dokter_list, jumlah_dokter, jadwal_list, hari-1);
                // informasi pelanggaran
                printf("\n[Pelanggaran] ");
                PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 0, hari-1, 0);
            } else {
                printf("Pilihan tidak valid!\n");
            }

            konfirmasi();
        } else if (pilih == 2) {
            tampilkan_jadwal_mingguan(dokter_list, jumlah_dokter, jadwal_list);
            // informasi pelanggaran
            printf("\n[Pelanggaran] ");
            PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 0, 0, 1);

            konfirmasi();
        } else if (pilih == 3) {
            tampilkan_jadwal_bulanan(dokter_list, jumlah_dokter, jadwal_list);

            // informasi pelanggaran
            printf("\n[Pelanggaran] ");
            PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, 0, 0, 2);

            konfirmasi();
        } else if (pilih == 4) {
            int id;
            printf("Masukkan ID dokter: ");
            scanf("%d", &id);
            tampilkan_jadwal_dokter(dokter_list, jumlah_dokter, jadwal_list, id);

            // informasi pelanggaran
            printf("\n[Pelanggaran] ");
            PrintPelanggaran(dokter_list, jadwal_list, jumlah_dokter, id, 0, 1);

            konfirmasi();
        } else if (pilih == 0) {
            printf("Kembali ke menu utama...\n");
        } else {
            printf("Pilihan tidak valid!\n");
            konfirmasi();
        }
        
    } while (pilih != 0);
}