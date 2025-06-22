#include <stdio.h>
#include <stdlib.h>
#include "pelanggaran.h"

enum Shift{
    SHIFT_PAGI = 1,
    SHIFT_SIANG = 2,
    SHIFT_MALAM = 3
};

int cek_1preferensi(Dokter daftar_dokter[], int indeks_dokter){
    int preferensi = 0;
    if (daftar_dokter[indeks_dokter].pagi == 1){ // hanya pagi
        if (daftar_dokter[indeks_dokter].siang == 0 && daftar_dokter[indeks_dokter].malam == 0){
            preferensi = SHIFT_PAGI;
        }
    }
    else if (daftar_dokter[indeks_dokter].siang == 1){ // hanya siang
        if (daftar_dokter[indeks_dokter].pagi == 0 && daftar_dokter[indeks_dokter].malam == 0){
            preferensi = SHIFT_SIANG;
        }
    }
    else if (daftar_dokter[indeks_dokter].malam == 1){ // hanya malam
        if (daftar_dokter[indeks_dokter].pagi == 0 && daftar_dokter[indeks_dokter].siang == 0){
            preferensi = SHIFT_MALAM;
        }
    }
    return preferensi;
}

void isi_jadwal(Dokter daftar_dokter[], Jadwal list_jadwal[], int *hari, int indeks_dokter, int pref){
    if (pref == SHIFT_PAGI){
        list_jadwal[*hari].pagi = realloc(list_jadwal[*hari].pagi, (list_jadwal[*hari].jumlah_pagi + 1) * sizeof(int));
        list_jadwal[*hari].pagi[list_jadwal[*hari].jumlah_pagi] = daftar_dokter[indeks_dokter].id;
        list_jadwal[*hari].jumlah_pagi++;
    }
    else if (pref == SHIFT_SIANG){
        list_jadwal[*hari].siang = realloc(list_jadwal[*hari].siang, (list_jadwal[*hari].jumlah_siang + 1) * sizeof(int));
        list_jadwal[*hari].siang[list_jadwal[*hari].jumlah_siang] = daftar_dokter[indeks_dokter].id;
        list_jadwal[*hari].jumlah_siang++;
    }
    else if (pref == SHIFT_MALAM){
        list_jadwal[*hari].malam = realloc(list_jadwal[*hari].malam, (list_jadwal[*hari].jumlah_malam + 1) * sizeof(int));
        list_jadwal[*hari].malam[list_jadwal[*hari].jumlah_malam] = daftar_dokter[indeks_dokter].id;
        list_jadwal[*hari].jumlah_malam++;
    }
    daftar_dokter[indeks_dokter].shift_assigned++;
    *hari += 1;
}

void isi_arrNotAssigned(Dokter daftar_dokter[], int indeks, int **arr_notAssigned, int *notAssigned){
    *notAssigned += 1;
    *arr_notAssigned = realloc(*arr_notAssigned, (*notAssigned)*sizeof(int));
    (*arr_notAssigned)[*notAssigned - 1] = daftar_dokter[indeks].id;
}

int shift_prioritas(Dokter daftar_dokter[], int jumlah_dokter, int hari_pagi, int hari_siang, int hari_malam){
    // hitung kekosongan tiap shift
    int pagi_kosong = 7 - hari_pagi;
    int siang_kosong = 7 - hari_siang;
    int malam_kosong = 7 - hari_malam;

    int available_pagi = 0; int available_siang = 0; int available_malam = 0;
    // hitung berapa banyak dokter yang bisa mengisi
    for (int i = 0; i < jumlah_dokter; i++){
        if (daftar_dokter[i].pagi == 1){
            available_pagi += (daftar_dokter[i].maks_shift - daftar_dokter[i].shift_assigned);
        }
        if (daftar_dokter[i].siang == 1){
            available_siang += (daftar_dokter[i].maks_shift - daftar_dokter[i].shift_assigned);
        }
        if (daftar_dokter[i].malam == 1){
            available_malam += (daftar_dokter[i].maks_shift - daftar_dokter[i].shift_assigned);
        }
    }

    // pilih shift prioritas
    int skor_pagi = available_pagi - pagi_kosong;
    int skor_siang = available_siang - siang_kosong;
    int skor_malam = available_malam - malam_kosong;

    int a, b, c;
    a = b = c = 10000;

    if (hari_pagi < 7) a = skor_pagi;
    if (hari_siang < 7) b = skor_siang;
    if (hari_malam < 7) c = skor_malam;

    int arr[3] = {a, b, c};
    int prioritas = 0;
    int min = 10000;

    for (int i = 0; i < 3; i++){
        if (arr[i] >= 0 && arr[i] < min){
            min = arr[i];
            prioritas = i+1;
        }
    }
    // kasus jika ada skor negatif dan yang lain sudah penuh shift nya
    if (prioritas == 0){
        for (int i = 0; i < 3; i++){
            if (arr[i] < min){
                min = arr[i];
                prioritas = -(i+1);
            }
        }
    }
    return prioritas;
}

void isi_jadwalPrioritas(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int prioritas,
                        int *hari_pagi, int *hari_siang, int *hari_malam, int idx, int *progress, int pelanggaran){
    
    if ((prioritas == SHIFT_PAGI && daftar_dokter[idx].pagi == 1) || (prioritas == -(SHIFT_PAGI) && pelanggaran == 1)){
        isi_jadwal(daftar_dokter, list_jadwal, hari_pagi, idx, 1);
        *progress = 1;
    }
    else if ((prioritas == SHIFT_SIANG && daftar_dokter[idx].siang == 1) || (prioritas == -(SHIFT_SIANG) && pelanggaran == 1)){
        isi_jadwal(daftar_dokter, list_jadwal, hari_siang, idx, 2);
        *progress = 1;
    }
    else if ((prioritas == SHIFT_MALAM && daftar_dokter[idx].malam == 1) || (prioritas == -(SHIFT_MALAM) && pelanggaran == 1)){
        isi_jadwal(daftar_dokter, list_jadwal, hari_malam, idx, 3);
        *progress = 1;
    }
}

void reset_hari(int *hari_pagi, int *iterasi_pagi, int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam){
    if (*hari_pagi == 7){
        *hari_pagi = 0;
        *iterasi_pagi += 1;
    }
    if (*hari_siang == 7){
        *hari_siang = 0;
        *iterasi_siang += 1;
    }
    if (*hari_malam == 7){
        *hari_malam = 0;
        *iterasi_malam += 1;
    }
}

void assign_sisa(Dokter daftar_dokter[], Jadwal list_jadwal[], int idx, int *hari_pagi, int *iterasi_pagi,
                int *hari_siang, int *iterasi_siang, int *hari_malam, int *iterasi_malam){
    
    int pref[3] = {daftar_dokter[idx].pagi, daftar_dokter[idx].siang, daftar_dokter[idx].malam};
    int arr_iterasi[3] = {*iterasi_pagi, *iterasi_siang, *iterasi_malam};
    int arr_hari[3] = {*hari_pagi, *hari_siang, *hari_malam};
    int min_iterasi = 10;
    int min_hari = 7;
    int assign_shift = 0;
    
    // cek iterasi minimum
    for (int i = 0; i < 3; i++){
        if (pref[i] == 1 && arr_iterasi[i] < min_iterasi){
            min_iterasi = arr_iterasi[i];
            min_hari = arr_hari[i];
            assign_shift = i+1;
        }
    }
    // cek shift lain yang iterasi nya == iterasi minimum
    for (int i = assign_shift; i < 3; i++){
        if (pref[i] == 1 && arr_iterasi[i] == min_iterasi){
            if (arr_hari[i] < min_hari){
                min_hari = arr_hari[i];
                assign_shift = i+1; 
            }
        }
    }
    // assign dokter ke shift terpilih
    if (assign_shift == SHIFT_PAGI) isi_jadwal(daftar_dokter, list_jadwal, hari_pagi, idx, SHIFT_PAGI);
    else if (assign_shift == SHIFT_SIANG) isi_jadwal(daftar_dokter, list_jadwal, hari_siang, idx, SHIFT_SIANG);
    else if (assign_shift == SHIFT_MALAM) isi_jadwal(daftar_dokter, list_jadwal, hari_malam, idx, SHIFT_MALAM);
}

void scheduling_stage1(Dokter daftar_dokter[], Jadwal list_jadwal[], int *indeks_dokter, int jumlah_dokter, int *hari_pagi, int *hari_siang,
                    int *hari_malam, int **arr_notAssigned_1Pref,int *notAssigned_1Pref, int **arr_notAssigned_multi, int *notAssigned_multi){
    
    while ((*indeks_dokter < jumlah_dokter) && (*hari_pagi < 7 || *hari_siang < 7 || *hari_malam < 7)){
        switch (cek_1preferensi(daftar_dokter, *indeks_dokter))
        {
        case 1:
            if (*hari_pagi < 7) isi_jadwal(daftar_dokter, list_jadwal, hari_pagi, *indeks_dokter, SHIFT_PAGI);
            else isi_arrNotAssigned(daftar_dokter, *indeks_dokter, arr_notAssigned_1Pref, notAssigned_1Pref);
            break;

        case 2:
            if (*hari_siang < 7) isi_jadwal(daftar_dokter, list_jadwal, hari_siang, *indeks_dokter, SHIFT_SIANG);
            else isi_arrNotAssigned(daftar_dokter, *indeks_dokter, arr_notAssigned_1Pref, notAssigned_1Pref);
            break;

        case 3:
            if (*hari_malam < 7) isi_jadwal(daftar_dokter, list_jadwal, hari_malam, *indeks_dokter, SHIFT_MALAM);
            else isi_arrNotAssigned(daftar_dokter, *indeks_dokter, arr_notAssigned_1Pref, notAssigned_1Pref);
            break;

        default:
            isi_arrNotAssigned(daftar_dokter, *indeks_dokter, arr_notAssigned_multi, notAssigned_multi);
            break;
        }
        *indeks_dokter += 1;
    }
}

void scheduling_stage2(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int *hari_pagi, int *hari_siang, int *hari_malam,
                    int *arr_notAssigned_1Pref, int notAssigned_1Pref, int *arr_notAssigned_multi, int notAssigned_multi){
    
    int progress = 0; int done = 0; int available = 0; int pelanggaran = 0; int count = 0;
    while (*hari_pagi < 7 || *hari_siang < 7 || *hari_malam < 7){
        // jika ada dokter multi pref
        if (notAssigned_multi > 0 && done != 1){
            progress = 0; available = 0; int tidak_bersedia = 0;
            for (int i = 0; i < notAssigned_multi; i++){
                // cari indeks nya di list dokter
                int idx = FindIdx(daftar_dokter, arr_notAssigned_multi[i], jumlah_dokter);
                if (daftar_dokter[idx].shift_assigned > 0) continue;
                
                available += 1;
                int prioritas = shift_prioritas(daftar_dokter, jumlah_dokter, *hari_pagi, *hari_siang, *hari_malam);
                isi_jadwalPrioritas(daftar_dokter, list_jadwal, jumlah_dokter, prioritas, hari_pagi, hari_siang, hari_malam, idx, &progress, 0);
                if (*hari_pagi == 7 && *hari_siang == 7 && *hari_malam == 7) break;
                if (prioritas < 0) pelanggaran == 1; break; // tidak tersedia dokter yang sesuai preferensinya
                if (progress == 0) tidak_bersedia += 1;
            }
            if (available == tidak_bersedia) done = 1; // dokter notAssigned_multi tidak ada yang sesuai preferensi nya
        }
        // isi shift kosong dengan melakukan loop ulang list dokter.
        else if (notAssigned_multi == 0 || done == 1){
            progress = 0;
            for (int idx = 0; idx < jumlah_dokter; idx++){
                if (daftar_dokter[idx].shift_assigned >= daftar_dokter[idx].maks_shift) continue;
                
                available += 1;
                int prioritas = shift_prioritas(daftar_dokter, jumlah_dokter, *hari_pagi, *hari_siang, *hari_malam);
                isi_jadwalPrioritas(daftar_dokter, list_jadwal, jumlah_dokter, prioritas, hari_pagi, hari_siang, hari_malam, idx, &progress, 0);
                if (*hari_pagi == 7 && *hari_siang == 7 && *hari_malam == 7) break;
                if (prioritas < 0) pelanggaran = 1; break; // tidak tersedia dokter yang sesuai preferensinya 
            }
        }
        // terpaksa pelanggaran
        else if (pelanggaran == 1){
            progress = 0; int perintah = 1; available = 0;
            for (int idx = 0; idx < jumlah_dokter; idx++){
                if (daftar_dokter[idx].shift_assigned >= daftar_dokter[idx].maks_shift) continue;
                available += 1;
                // isi dulu dokter yang belum di-assign
                if (count == 0){
                    if (daftar_dokter[idx].shift_assigned > 0) perintah = 0;
                }
                if (perintah == 1){
                    int prioritas = shift_prioritas(daftar_dokter, jumlah_dokter, *hari_pagi, *hari_siang, *hari_malam);
                    isi_jadwalPrioritas(daftar_dokter, list_jadwal, jumlah_dokter, prioritas, hari_pagi, hari_siang, hari_malam, idx, &progress, 1);
                    if (*hari_pagi == 7 && *hari_siang == 7 && *hari_malam == 7) break;
                }
            }
            count += 1;
        }
        // semua dokter sudah bekerja pada beban maksimum, cegah infinite loop
        if ((available == 0) && (notAssigned_multi == 0 || done == 1)) printf("Tidak ada lagi dokter yang dapat dipekerjakan"); break;
    }
}

void scheduling_stage3(Dokter daftar_dokter[], Jadwal list_jadwal[], int jumlah_dokter, int indeks, int *hari_pagi, int *hari_siang, int *hari_malam){
    
    *hari_pagi = *hari_siang = *hari_malam = 0;
    int iterasi_pagi = 0; int iterasi_siang = 0; int iterasi_malam = 0;
    
    // assign dokter 1 preferensi yang belum di-assign
    for (int idx = 0; idx < jumlah_dokter; idx++){
        if (daftar_dokter[idx].shift_assigned > 0) continue;
        int pref = cek_1preferensi(daftar_dokter, idx);
        if (pref == SHIFT_PAGI) isi_jadwal(daftar_dokter, list_jadwal, hari_pagi, idx, SHIFT_PAGI);
        else if (pref == SHIFT_SIANG) isi_jadwal(daftar_dokter, list_jadwal, hari_siang, idx, SHIFT_SIANG);
        else if (pref == SHIFT_MALAM) isi_jadwal(daftar_dokter, list_jadwal, hari_malam, idx, SHIFT_MALAM);

        reset_hari(hari_pagi, &iterasi_pagi, hari_siang, &iterasi_siang, hari_malam, &iterasi_malam);
    }

    // assign dokter multi pref yang belum di-assign
    for (int idx = 0; idx < jumlah_dokter; idx++){
        if (daftar_dokter[idx].shift_assigned > 0) continue;
        assign_sisa(daftar_dokter, list_jadwal, idx, hari_pagi, &iterasi_pagi, hari_siang, &iterasi_siang, hari_malam, &iterasi_malam);
        reset_hari(hari_pagi, &iterasi_pagi, hari_siang, &iterasi_siang, hari_malam, &iterasi_malam);
    }
}

void reset_jadwal(Jadwal list_jadwal[]){
    for (int i = 0; i < 7; i++){
        free(list_jadwal[i].pagi);
        free(list_jadwal[i].siang);
        free(list_jadwal[i].malam);
        list_jadwal[i].pagi = NULL;
        list_jadwal[i].siang = NULL;
        list_jadwal[i].malam = NULL;
        list_jadwal[i].jumlah_pagi = 0;
        list_jadwal[i].jumlah_siang = 0;
        list_jadwal[i].jumlah_malam = 0;
    }
}

void scheduling_main(Dokter daftar_dokter[], int jumlah_dokter, Jadwal list_jadwal[]){
    // looping dokter
    int hari_pagi = 0;
    int hari_siang = 0;
    int hari_malam = 0;
    int indeks_dokter = 0;
    int *arr_notAssigned_multi = NULL;
    int *arr_notAssigned_1Pref = NULL;
    int notAssigned_multi = 0;
    int notAssigned_1Pref = 0;

    // pengisian pertama mengutamakan dokter dengan 1 preferensi
    scheduling_stage1(daftar_dokter, list_jadwal, &indeks_dokter, jumlah_dokter, &hari_pagi, &hari_siang, &hari_malam,
                    &arr_notAssigned_1Pref, &notAssigned_1Pref, &arr_notAssigned_multi, &notAssigned_multi);
    
    // keluar dari stage 1 bisa ada 3 kasus
    // 1. perfect, dokter pas untuk 21 shift per minggu
    // 2. belum semua shift terisi penuh
    // 3. 21 shift terisi tetapi ada sisa dokter

    // kasus 1
    if (indeks_dokter == jumlah_dokter && notAssigned_multi == 0 && notAssigned_1Pref == 0
        && hari_pagi == 7 && hari_siang == 7 && hari_malam == 7){
        return;
    }

    // kasus 2 (shift belum semuanya terisi)
    scheduling_stage2(daftar_dokter, list_jadwal, jumlah_dokter, &hari_pagi, &hari_siang, &hari_malam,
                    arr_notAssigned_1Pref, notAssigned_1Pref, arr_notAssigned_multi, notAssigned_multi);

    // kasus 3 (assign sisa dokter)
    scheduling_stage3(daftar_dokter, list_jadwal, jumlah_dokter, indeks_dokter, &hari_pagi, &hari_siang, &hari_malam);
    
    // free arr_notAssigned
    free(arr_notAssigned_multi);
    free(arr_notAssigned_1Pref);
}
