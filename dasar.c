// dasar.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dasar.h"

int csv_to_dokter(const char *filename, Dokter *dokter_list, int max_dokter) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file");
        return -1;
    }

    char line[256];
    int count = 0;

    // Lewati header
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) && count < max_dokter) {
        char *token = strtok(line, ",");
        if (!token) continue;

        dokter_list[count].id = atoi(token);

        token = strtok(NULL, ",");
        if (token) strcpy(dokter_list[count].nama, token);

        token = strtok(NULL, ",");
        if (token) dokter_list[count].maks_shift = atoi(token);

        token = strtok(NULL, ",");
        if (token) dokter_list[count].pagi = atoi(token);

        token = strtok(NULL, ",");
        if (token) dokter_list[count].siang = atoi(token);

        token = strtok(NULL, ",\r\n"); // tambahkan \r\n untuk handle Windows line endings
        if (token) dokter_list[count].malam = atoi(token);

        count++;
    }

    fclose(fp);
    return count;
}

void print_dokter_list(const Dokter *list, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        printf("ID: %d, Nama: %s, Maks Shift: %d, Pagi: %d, Siang: %d, Malam: %d\n",
               list[i].id, list[i].nama, list[i].maks_shift,
               list[i].pagi, list[i].siang, list[i].malam);
    }
}

void dokter_to_csv(const char *filename, const Dokter *list, int jumlah) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Gagal membuka file untuk menulis");
        return;
    }

    // Header
    fprintf(fp, "id,nama,maks_shift,pagi,siang,malam\n");

    // Data per baris
    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s,%d,%d,%d,%d\n",
                list[i].id,
                list[i].nama,
                list[i].maks_shift,
                list[i].pagi,
                list[i].siang,
                list[i].malam);
    }

    fclose(fp);
    printf("Data berhasil disimpan ke '%s'.\n", filename);
}


int csv_to_jadwal(const char *filename, Jadwal *jadwal_list, int max_jadwal) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file jadwal");
        return -1;
    }

    char line[256];
    int count = 0;

    fgets(line, sizeof(line), fp); // Lewati header

    while (fgets(line, sizeof(line), fp) && count < max_jadwal) {
        char *token = strtok(line, ",");
        if (!token) continue;

        jadwal_list[count].tanggal = atoi(token);

        token = strtok(NULL, ",");
        if (token) jadwal_list[count].pagi = atoi(token);

        token = strtok(NULL, ",");
        if (token) jadwal_list[count].siang = atoi(token);

        token = strtok(NULL, ",\r\n");
        if (token) jadwal_list[count].malam = atoi(token);

        count++;
    }

    fclose(fp);
    return count;
}

void print_jadwal_list(const Jadwal *list, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        printf("Tanggal: %d, Pagi: %d, Siang: %d, Malam: %d\n",
               list[i].tanggal, list[i].pagi, list[i].siang, list[i].malam);
    }
}

void jadwal_to_csv(const char *filename, const Jadwal *list, int jumlah) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Gagal membuka file untuk menyimpan jadwal");
        return;
    }

    fprintf(fp, "tanggal,pagi,siang,malam\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%d,%d,%d\n",
                list[i].tanggal,
                list[i].pagi,
                list[i].siang,
                list[i].malam);
    }

    fclose(fp);
    printf("Jadwal berhasil disimpan ke '%s'.\n", filename);
}
