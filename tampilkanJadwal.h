#ifndef TAMPILKAN_JADWAL_H
#define TAMPILKAN_JADWAL_H

#include "dasar.h"

void menu_tampilkan_jadwal(const Dokter *dokter_list, int jumlah_dokter, const Jadwal *jadwal_list);
void tampilkan_jadwal_harian(const Dokter *dokter_list, int jumlah_dokter, const Jadwal *jadwal_list, int hari);
void tampilkan_jadwal_mingguan(const Dokter *dokter_list, int jumlah_dokter, const Jadwal *jadwal_list);
void tampilkan_jadwal_bulanan(const Dokter *dokter_list, int jumlah_dokter, const Jadwal *jadwal_list);
void tampilkan_jadwal_dokter(const Dokter *dokter_list, int jumlah_dokter, const Jadwal *jadwal_list, int id_dokter);

#endif