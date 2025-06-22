#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "dasar.h"

int cek_1preferensi(Dokter daftar_dokter[], int indeks_dokter);
void isi_jadwal(Dokter daftar_dokter[], Jadwal list_jadwal[], int *hari, int indeks_dokter, int pref);
int shift_prioritas(Dokter daftar_dokter[], int jumlah_dokter, int hari_pagi, int hari_siang, int hari_malam);
void isi_jadwalPrioritas(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int prioritas,
                        int *hari_pagi, int *hari_siang, int *hari_malam, int idx, int *progress, int pelanggaran);
void reset_hari(int *hari_pagi, int *iterasi_pagi, int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam);
void assign_sisa(Dokter daftar_dokter[], Jadwal list_jadwal[], int idx, int *hari_pagi, int *iterasi_pagi,
                int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam);
void scheduling_stage1(Dokter daftar_dokter[], Jadwal list_jadwal[], int *indeks_dokter, int jumlah_dokter, int *hari_pagi, int *hari_siang,
                    int *hari_malam, int **arr_notAssigned_1Pref,int *notAssigned_1Pref, int **arr_notAssigned_multi, int *notAssigned_multi);
void scheduling_stage2(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int *hari_pagi, int *hari_siang, int *hari_malam,
                    int *arr_notAssigned_1Pref, int notAssigned_1Pref, int *arr_notAssigned_multi, int notAssigned_multi);
void scheduling_stage3(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int indeks, int *hari_pagi, int *hari_siang, int *hari_malam);
void scheduling_main(Dokter daftar_dokter[], int jumlah_dokter, Jadwal list_jadwal[]);
void reset_jadwal(Jadwal list_jadwal[]);

#endif