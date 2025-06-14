#ifndef DASAR_H
#define DASAR_H

// Struktur Dokter
typedef struct {
    int id;
    char nama[100];
    int maks_shift;
    int pagi;
    int siang;
    int malam;
} Dokter;

// Struktur Jadwal
typedef struct {
    int tanggal;
    int pagi;
    int siang;
    int malam;
} Jadwal;

// Fungsi-fungsi Dokter
int csv_to_dokter(const char *filename, Dokter *dokter_list, int max_dokter);
void print_dokter_list(const Dokter *list, int jumlah);
void dokter_to_csv(const char *filename, const Dokter *list, int jumlah);

// Fungsi-fungsi Jadwal
int csv_to_jadwal(const char *filename, Jadwal *jadwal_list, int max_jadwal);
void print_jadwal_list(const Jadwal *list, int jumlah);
void jadwal_to_csv(const char *filename, const Jadwal *list, int jumlah);

#endif
