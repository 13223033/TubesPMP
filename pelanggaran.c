#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dasar.h"

/* Function Dasar Cari Index Dokter sesuai ID*/
int FindIdx(Dokter dokter_list[], int id, int jumlah_dokter) {
    int idx;
    for (int i = 0; i < jumlah_dokter; i++) {
        if (dokter_list[i].id == id) {
            idx = i;
            break;
        }
    }
    return(idx);
}

/* Function Pelanggaran Spesifik Dokter*/
// Harian
void PelanggaranDokterHarian(Dokter dokter, Jadwal jadwal, int *totalpelanggaran) {
    // pelanggaran pagi
    for (int i = 0; i < jadwal.jumlah_pagi; i++) {
        if (jadwal.pagi[i] == dokter.id) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran siang
    for (int i = 0; i < jadwal.jumlah_siang; i++) {
        if (jadwal.siang[i] == dokter.id) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran malam
    for (int i = 0; i < jadwal.jumlah_malam; i++) {
        if (jadwal.malam[i] == dokter.id) {
            (*totalpelanggaran)++;
        }
    }
}

// Mingguan
void PelanggaranDokterMingguan(Dokter dokter, Jadwal jadwal[], int *totalpelanggaran) {
    for (int i = 0; i < 7; i++) {
        PelanggaranDokterHarian(dokter, jadwal[i], totalpelanggaran);
    }
}

// Bulanan
void PelanggaranDokterBulanan(Dokter dokter, Jadwal jadwal[], int *totalpelanggaran) {
    PelanggaranDokterMingguan(dokter, jadwal, totalpelanggaran);
    (*totalpelanggaran) *= 4;

    PelanggaranDokterHarian(dokter, jadwal[0], totalpelanggaran);
    PelanggaranDokterHarian(dokter, jadwal[1], totalpelanggaran);
}

/* Function Pelanggaran Nonspesifik Dokter (Total)*/
// Harian
void PelanggaranTotalHarian(Dokter dokter[], Jadwal jadwal, int jumlah_dokter, int *totalpelanggaran) {
    // pelanggaran pagi
    for (int i = 0; i < jadwal.jumlah_pagi; i++) {
        int id = jadwal.pagi[i];
        int idx = FindIdx(dokter, id, jumlah_dokter);
        if (!dokter[idx].pagi) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran siang
    for (int i = 0; i < jadwal.jumlah_siang; i++) {
        int id = jadwal.siang[i];
        int idx = FindIdx(dokter, id, jumlah_dokter);
        if (!dokter[idx].siang) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran malam
    for (int i = 0; i < jadwal.jumlah_malam; i++) {
        int id = jadwal.malam[i];
        int idx = FindIdx(dokter, id, jumlah_dokter);
        if (!dokter[idx].malam) {
            (*totalpelanggaran)++;
        }
    }
}

// Mingguan
void PelanggaranTotalMingguan(Dokter dokter[], Jadwal jadwal[], int jumlah_dokter, int *totalpelanggaran) {
    for (int i = 0; i < 7; i++) {
        PelanggaranTotalHarian(dokter, jadwal[i], jumlah_dokter, totalpelanggaran);
    }
}

// Bulanan
void PelanggaranTotalBulanan(Dokter dokter[], Jadwal jadwal[], int jumlah_dokter, int *totalpelanggaran) {
    PelanggaranTotalMingguan(dokter, jadwal, jumlah_dokter, totalpelanggaran);
    (*totalpelanggaran) *= 4;

    PelanggaranTotalHarian(dokter, jadwal[0], jumlah_dokter, totalpelanggaran);
    PelanggaranTotalHarian(dokter, jadwal[1], jumlah_dokter, totalpelanggaran);
}

/* Function utama, print pelanggaran*/
// Spesifikasi:
// id           : id dokter, spesifik ikuti id, nonspesifik = 0
// hari         : index hari, spesifik ikuti index, nonspesifik = 0
// tipewaktu    : harian 0, mingguan 1, bulanan 2
void PrintPelanggaran(Dokter dokter[], Jadwal jadwal[], int jumlah_dokter, int id, int hari, int tipewaktu) {
    int totalpelanggaran = 0;

    if (id == 0) {     // Nonspesifik dokter (pelanggaran total)
        switch (tipewaktu) {
            case 0:
                PelanggaranTotalHarian(dokter, jadwal[hari], jumlah_dokter, &totalpelanggaran);
                break;
            case 1:
                PelanggaranTotalMingguan(dokter, jadwal, jumlah_dokter, &totalpelanggaran);
                break;
            case 2:
                PelanggaranTotalBulanan(dokter, jadwal, jumlah_dokter, &totalpelanggaran);
        }
    } else {            // Spesifik dokter (pelanggaran dokter)
        int idx = FindIdx(dokter, id, jumlah_dokter);
        switch (tipewaktu) {
            case 0:
                PelanggaranDokterHarian(dokter[idx], jadwal[hari], &totalpelanggaran);
                break;
            case 1:
                PelanggaranDokterMingguan(dokter[idx], jadwal, &totalpelanggaran);
                break;
            case 2:
                PelanggaranDokterBulanan(dokter[idx], jadwal, &totalpelanggaran);
        }
    }

    printf("%s jadwal %s: %d\n",
        id == 0 ? "Total pelanggaran" : "Pelanggaran",
        tipewaktu == 0 ? "harian" : tipewaktu == 1 ? "mingguan" : "bulanan",
        totalpelanggaran);
} 