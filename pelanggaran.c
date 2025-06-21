#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dasar.h"

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
void PelanggaranTotalHarian(Dokter dokter[], Jadwal jadwal, int *totalpelanggaran) {
    // pelanggaran pagi
    for (int i = 0; i < jadwal.jumlah_pagi; i++) {
        int id = jadwal.pagi[i];
        if (!dokter[id].pagi) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran siang
    for (int i = 0; i < jadwal.jumlah_siang; i++) {
        int id = jadwal.siang[i];
        if (!dokter[id].siang) {
            (*totalpelanggaran)++;
        }
    }

    // pelanggaran malam
    for (int i = 0; i < jadwal.jumlah_malam; i++) {
        int id = jadwal.malam[i];
        if (!dokter[id].malam) {
            (*totalpelanggaran)++;
        }
    }
}

// Mingguan
void PelanggaranTotalMingguan(Dokter dokter[], Jadwal jadwal[], int *totalpelanggaran) {
    for (int i = 0; i < 7; i++) {
        PelanggaranTotalHarian(dokter, jadwal[i], totalpelanggaran);
    }
}

// Bulanan
void PelanggaranTotalBulanan(Dokter dokter[], Jadwal jadwal[], int *totalpelanggaran) {
    PelanggaranTotalMingguan(dokter, jadwal, totalpelanggaran);
    (*totalpelanggaran) *= 4;

    PelanggaranTotalHarian(dokter, jadwal[0], totalpelanggaran);
    PelanggaranTotalHarian(dokter, jadwal[1], totalpelanggaran);
}

/* Function utama, print pelanggaran*/
// Spesifikasi:
// id           : index dokter, spesifik ikuti index, nonspesifik = -1
// hari         : index hari, spesifik ikuti index, nonspesifik pakai 0 saja
// tipewaktu    : harian 0, mingguan 1, bulanan 2
void PrintPelanggaran(Dokter dokter[], Jadwal jadwal[], int id, int hari, int tipewaktu) {
    int totalpelanggaran = 0;

    if (id == -1) {     // Nonspesifik dokter (pelanggaran total)
        switch (tipewaktu) {
            case 0:
                PelanggaranTotalHarian(dokter, jadwal[hari], &totalpelanggaran);
                break;
            case 1:
                PelanggaranTotalMingguan(dokter, jadwal, &totalpelanggaran);
                break;
            case 2:
                PelanggaranTotalBulanan(dokter, jadwal, &totalpelanggaran);
        }
    } else {            // Spesifik dokter (pelanggaran dokter)
        switch (tipewaktu) {
            case 0:
                PelanggaranDokterHarian(dokter[id], jadwal[hari], &totalpelanggaran);
                break;
            case 1:
                PelanggaranDokterMingguan(dokter[id], jadwal, &totalpelanggaran);
                break;
            case 2:
                PelanggaranDokterBulanan(dokter[id], jadwal, &totalpelanggaran);
        }
    }

    printf("%s %s: %d\n",
        id == -1 ? "Total pelanggaran" : "Pelanggaran",
        tipewaktu == 0 ? "harian" : tipewaktu == 1 ? "mingguan" : "bulanan",
        totalpelanggaran);
} 