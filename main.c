// main.c
#include <stdio.h>
#include "dasar.h"

int main() {
    /*
    Ini contoh fungsi main sekarang.
    */

    CSVData data = load_csv_data("data_dokter.csv");

    printf("Isi CSV:\n");
    print_csv(&data);

    // Simpan ke file lain
    save_csv_data(&data, "data_dokter.csv");

    // Bebaskan memori
    free_csv(&data);

    return 0;
}
