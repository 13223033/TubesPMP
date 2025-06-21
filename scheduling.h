#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "dasar.h"

int cek_1preferensi(Dokter daftar_dokter[100], int indeks_dokter);
void isi_jadwal(Dokter daftar_dokter[100], Jadwal list_jadwal[7], int *hari, int indeks_dokter, int pref);
int shift_prioritas(Dokter daftar_dokter[100], int jumlah_dokter, int hari_pagi, int hari_siang, int hari_malam);
void isi_jadwalPrioritas(Dokter daftar_dokter[100], Jadwal list_jadwal[7], int jumlah_dokter, int prioritas,
                        int *hari_pagi, int *hari_siang, int *hari_malam, int idx, int *progress);
void reset_hari(int *hari_pagi, int *iterasi_pagi, int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam);
void assign_sisa(Dokter daftar_dokter[100], Jadwal list_jadwal[7], int idx, int *hari_pagi, int *iterasi_pagi,
                int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam);
void reset_jadwal(Jadwal list_jadwal[7]);
void scheduling(Dokter daftar_dokter[100], int jumlah_dokter, Jadwal list_jadwal[7]);

#endif