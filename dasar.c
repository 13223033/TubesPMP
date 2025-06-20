#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dasar.h"

// ------------ DOKTER ------------

int csv_to_dokter(const char *filename, Dokter *dokter_list, int max_dokter) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file dokter");
        return -1;
    }

    char line[256];
    int count = 0;

    fgets(line, sizeof(line), fp); // Lewati header

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

        token = strtok(NULL, ",");
        if (token) dokter_list[count].malam = atoi(token);

        token = strtok(NULL, ",\r\n");
        if (token) dokter_list[count].shift_assigned = atoi(token);

        count++;
    }

    fclose(fp);
    return count;
}

void print_dokter_list(const Dokter *list, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        printf("ID: %d, Nama: %s, Maks Shift: %d, Pagi: %d, Siang: %d, Malam: %d, Assigned: %d\n",
               list[i].id, list[i].nama, list[i].maks_shift,
               list[i].pagi, list[i].siang, list[i].malam,
               list[i].shift_assigned);
    }
}

void dokter_to_csv(const char *filename, const Dokter *list, int jumlah) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Gagal membuka file untuk menulis dokter");
        return;
    }

    fprintf(fp, "id,nama,maks_shift,pagi,siang,malam,shift_assigned\n");

    for (int i = 0; i < jumlah; i++) {
        fprintf(fp, "%d,%s,%d,%d,%d,%d,%d\n",
                list[i].id, list[i].nama, list[i].maks_shift,
                list[i].pagi, list[i].siang, list[i].malam,
                list[i].shift_assigned);
    }

    fclose(fp);
    printf("Data dokter disimpan ke '%s'.\n", filename);
}

// ------------ JADWAL ------------

int csv_to_jadwal(const char *filename, Jadwal *jadwal_list, int max_jadwal) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file jadwal");
        return -1;
    }

    char line[512];
    int count = 0;

    fgets(line, sizeof(line), fp); // Lewati header

    while (fgets(line, sizeof(line), fp) && count < max_jadwal) {
        Jadwal *jadwal = &jadwal_list[count];
        char *token;

        token = strtok(line, ",");
        jadwal->pagi = token ? parse_id_list(token, &jadwal->jumlah_pagi) : NULL;

        token = strtok(NULL, ",");
        jadwal->siang = token ? parse_id_list(token, &jadwal->jumlah_siang) : NULL;

        token = strtok(NULL, ",");
        jadwal->malam = token ? parse_id_list(token, &jadwal->jumlah_malam) : NULL;

        // Lewati jumlah_pagi, jumlah_siang, jumlah_malam
        for (int i = 0; i < 3; i++) strtok(NULL, ",");

        count++;
    }

    fclose(fp);
    return count;
}

void print_jadwal_list(const Jadwal *list, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        printf("Hari %d:\n", i + 1);
        printf("  Pagi : ");
        for (int j = 0; j < list[i].jumlah_pagi; j++)
            printf("%d ", list[i].pagi[j]);
        printf("\n  Siang: ");
        for (int j = 0; j < list[i].jumlah_siang; j++)
            printf("%d ", list[i].siang[j]);
        printf("\n  Malam: ");
        for (int j = 0; j < list[i].jumlah_malam; j++)
            printf("%d ", list[i].malam[j]);
        printf("\n");
    }
}

void jadwal_to_csv(const char *filename, const Jadwal *list, int jumlah) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Gagal membuka file untuk menyimpan jadwal");
        return;
    }

    fprintf(fp, "pagi,siang,malam,jumlah_pagi,jumlah_siang,jumlah_malam\n");

    char pagi_buf[128], siang_buf[128], malam_buf[128];

    for (int i = 0; i < jumlah; i++) {
        join_id_list(pagi_buf, list[i].pagi, list[i].jumlah_pagi);
        join_id_list(siang_buf, list[i].siang, list[i].jumlah_siang);
        join_id_list(malam_buf, list[i].malam, list[i].jumlah_malam);

        fprintf(fp, "%s,%s,%s,%d,%d,%d\n",
                pagi_buf, siang_buf, malam_buf,
                list[i].jumlah_pagi,
                list[i].jumlah_siang,
                list[i].jumlah_malam);
    }

    fclose(fp);
    printf("Jadwal berhasil disimpan ke '%s'.\n", filename);
}

void free_jadwal_list(Jadwal *jadwal_list, int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        free(jadwal_list[i].pagi);
        free(jadwal_list[i].siang);
        free(jadwal_list[i].malam);
    }
}

// ------------ UTIL ------------

int *parse_id_list(const char *str, int *jumlah) {
    int *arr = malloc(20 * sizeof(int)); // kapasitas awal
    *jumlah = 0;

    char buffer[256];
    strncpy(buffer, str, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ";");

    while (token && *jumlah < 20) {
        arr[*jumlah] = atoi(token);
        (*jumlah)++;
        token = strtok(NULL, ";");
    }

    return arr;
}

void join_id_list(char *buffer, const int *arr, int jumlah) {
    buffer[0] = '\0';
    for (int i = 0; i < jumlah; i++) {
        char temp[12];
        sprintf(temp, "%d", arr[i]);
        strcat(buffer, temp);
        if (i < jumlah - 1)
            strcat(buffer, ";");
    }
}
