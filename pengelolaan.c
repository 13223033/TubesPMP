#include <stdio.h>
#include <string.h>
#include "pengelolaan.h"
#include "dasar.h"

#define MAX_DOKTER 100

int tambah_dokter(Dokter *list, int *jumlah,
                         const char *nama, int maks_shift,
                         int pagi, int siang, int malam)
{
    if (*jumlah >= MAX_DOKTER) return 0;

    int id_baru = (*jumlah == 0) ? 1 : list[*jumlah - 1].id + 1;

    list[*jumlah].id = id_baru;
    strncpy(list[*jumlah].nama, nama, sizeof(list[*jumlah].nama) - 1);
    list[*jumlah].nama[sizeof(list[*jumlah].nama) - 1] = '\0';
    list[*jumlah].maks_shift = maks_shift;
    list[*jumlah].pagi = pagi;
    list[*jumlah].siang = siang;
    list[*jumlah].malam = malam;
    list[*jumlah].shift_assigned = 0;

    (*jumlah)++;
    return 1;
}

int hapus_dokter(Dokter *list, int *jumlah, int id)
{
    int idx = -1;
    for (int i = 0; i < *jumlah; ++i) {
        if (list[i].id == id) { idx = i; break; }
    }
    if (idx == -1) return 0;

    for (int i = idx; i < *jumlah - 1; ++i)
        list[i] = list[i + 1];

    --(*jumlah);
    return 1;
}

void tampilkan_dokter(const Dokter *list, int jumlah)
{
    printf("\n===== DAFTAR DOKTER SAAT INI =====\n");
    print_dokter_list(list, jumlah);
    printf("==================================\n");
}

void menu_pengelolaan_dokter(const char *nama_file)
{
    Dokter dokter_list[MAX_DOKTER];
    int jumlah_dokter = csv_to_dokter(nama_file, dokter_list, MAX_DOKTER);
    if (jumlah_dokter < 0) return;

    int pilih;
    do {
        printf("\n=== MENU PENGELOLAAN DOKTER ===\n");
        printf("1. Tampilkan daftar dokter\n");
        printf("2. Tambah dokter\n");
        printf("3. Hapus dokter\n");
        printf("4. Kembali\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilih) != 1) { fflush(stdin); pilih = 4; }

        if (pilih == 1) {
            tampilkan_dokter(dokter_list, jumlah_dokter);

        } else if (pilih == 2) {
            char nama[100];
            int maks, pg, sg, ml;
            getchar(); // flush newline
            printf("Nama          : "); fgets(nama, sizeof nama, stdin);
            nama[strcspn(nama, "\n")] = '\0';
            printf("Maks shift    : ");  scanf("%d", &maks);
            printf("Pagi  (1/0)   : ");  scanf("%d", &pg);
            printf("Siang (1/0)   : ");  scanf("%d", &sg);
            printf("Malam (1/0)   : ");  scanf("%d", &ml);

            if (tambah_dokter(dokter_list, &jumlah_dokter,
                               nama, maks, pg, sg, ml)) {
                dokter_to_csv(nama_file, dokter_list, jumlah_dokter);
                printf(">> Dokter ditambahkan.\n");
            } else {
                printf(">> Gagal menambahkan dokter (kapasitas penuh).\n");
            }

        } else if (pilih == 3) {
            int id;
            printf("Masukkan ID dokter yang akan dihapus: ");
            scanf("%d", &id);
            if (hapus_dokter(dokter_list, &jumlah_dokter, id)) {
                dokter_to_csv(nama_file, dokter_list, jumlah_dokter);
                printf(">> Dokter berhasil dihapus.\n");
            } else {
                printf(">> Dokter dengan ID tersebut tidak ditemukan.\n");
            }

        } else if (pilih != 4) {
            printf(">> Pilihan tidak valid.\n");
        }

    } while (pilih != 4);
}
