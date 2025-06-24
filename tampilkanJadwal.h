#ifndef TAMPILKAN_JADWAL_H
#define TAMPILKAN_JADWAL_H

#include "dasar.h"

void menu_tampilkan_jadwal(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list);
void tampilkan_jadwal_harian(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list, int hari);
void tampilkan_jadwal_mingguan(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list);
void tampilkan_jadwal_bulanan(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list);
void tampilkan_jadwal_dokter(Dokter *dokter_list, int jumlah_dokter, Jadwal *jadwal_list, int id_dokter);

#endif