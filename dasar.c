#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** imp_split(const char* str, char delimiter, int* count) 
    // Fungsi imp_split: Memisahkan string berdasarkan karakter delimiter ','.
    // Parameter:
    //   - str: string input yang ingin dipisah
    //   - delimiter: karakter pemisah (diganti menjadi ',')
    //   - count: pointer ke integer untuk menyimpan jumlah elemen hasil split
    // Return:
    //   - Array of strings (char**) hasil split
    {
    int capacity = 10;                          // Kapasitas awal array hasil
    *count = 0;                                 // Inisialisasi jumlah elemen hasil split
    char** result = malloc(capacity * sizeof(char*)); // Alokasi memori awal untuk hasil split

    char buffer[1024];                          // Buffer sementara untuk menyusun string sebelum dipisah
    int buf_index = 0;                          // Indeks buffer

    for (int i = 0; ; i++) {
        char c = str[i];                        // Ambil karakter satu per satu dari string input

        if (c == delimiter || c == '\0') {      // Jika karakter adalah delimiter atau akhir string
            buffer[buf_index] = '\0';           // Akhiri string sementara di buffer dengan null terminator
            result[*count] = strdup(buffer);    // Duplikasi buffer ke memori heap dan simpan di array result
            (*count)++;                         // Tambah jumlah elemen hasil split
            buf_index = 0;                      // Reset buffer untuk kata berikutnya

            // Jika jumlah elemen melebihi kapasitas array saat ini, perbesar alokasi memori
            if (*count >= capacity) {
                capacity *= 2;
                char** temp = realloc(result, capacity * sizeof(char*));
                if (!temp) {
                    perror("Gagal realloc pada imp_split");
                    // Bebaskan memori yang sudah dialokasikan sebelum exit
                    for (int k = 0; k < *count; k++) free(result[k]);
                    free(result);
                    exit(EXIT_FAILURE);
                }
                result = temp;
            }

            // Jika karakter adalah akhir string, hentikan loop
            if (c == '\0') break;
        }
        else if (c == '\n') {
            continue;                           // Abaikan karakter newline, seperti di Python
        }
        else {
            buffer[buf_index++] = c;            // Tambahkan karakter ke buffer
        }
    }

    return result;                              // Kembalikan array of strings hasil split
}

#define MAX_LINE_LEN 1024

typedef struct {
    char*** data;     // Array of rows, masing-masing row adalah array of fields (strings)
    int num_rows;     // Jumlah baris
    int num_cols;     // Jumlah kolom (asumsi semua baris konsisten)
} CSVData;


CSVData load_csv_data(const char* filename) 
    /**
     * load_csv_data - Membaca file CSV dan mengubahnya menjadi struktur CSVData
     * 
     * filename: nama file CSV yang akan dibaca, dalam string.
     * 
     * Return:
     *   Struct CSVData yang berisi:
     *     - data: array 2D berisi string hasil parsing CSV (rows x columns)
     *     - num_rows: jumlah baris yang berhasil dibaca
     *     - num_cols: jumlah kolom (diambil dari baris pertama)
     * 
     * Deskripsi:
     *   Fungsi ini membuka file CSV, membaca setiap baris, memecahnya menjadi array string berdasarkan delimiter koma (','), lalu menyimpan semua data ke dalam struktur CSVData.
     *   Kapasitas array baris akan bertambah secara dinamis sesuai kebutuhan. Jika ditemukan baris dengan jumlah kolom berbeda dari baris pertama, fungsi hanya memberikan peringatan, tidak menghentikan proses.
     */
    {
    CSVData csv;
    csv.num_rows = 0;
    csv.num_cols = 0;

    int capacity = 10; // Kapasitas awal untuk jumlah baris
    csv.data = malloc(capacity * sizeof(char**));  // Alokasi awal array baris
    if (!csv.data) {
        perror("Gagal alokasi memori csv.data");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(filename, "r");  // Buka file CSV
    if (!file) {
        perror("Gagal membuka file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];  // Buffer untuk membaca baris
    while (fgets(line, sizeof(line), file)) {
        int num_fields;
        char** fields = imp_split(line, ',', &num_fields);  // Pecah baris menjadi fields

        if (csv.num_rows == 0) {
            csv.num_cols = num_fields;  // Tentukan jumlah kolom dari baris pertama
        } else if (num_fields != csv.num_cols) {
            fprintf(stderr, "Peringatan: Baris %d memiliki %d kolom (diharapkan %d)\n",
                    csv.num_rows + 1, num_fields, csv.num_cols);
        }

        // Perbesar kapasitas jika perlu
        if (csv.num_rows >= capacity) {
            capacity *= 2;
            char*** temp = realloc(csv.data, capacity * sizeof(char**));
            if (!temp) {
                perror("Gagal realloc csv.data");
                exit(EXIT_FAILURE);
            }
            csv.data = temp;
        }

        csv.data[csv.num_rows++] = fields;  // Simpan data baris ke array
    }

    fclose(file);  // Tutup file
    return csv;    // Kembalikan struct berisi data CSV
}


void free_csv(CSVData* csv) 
    /**
     * free_csv - Membebaskan memori yang dialokasikan untuk data CSV
     * 
     * csv: pointer ke struct CSVData yang akan dibersihkan memori-nya
     * 
     * Deskripsi:
     *   Fungsi ini membebaskan semua string di tiap kolom, lalu membebaskan array kolom per baris, dan terakhir membebaskan array baris utama.
     *   Setelah membebaskan memori, pointer dan hitungan baris/kolom direset.
     */
    {
    for (int i = 0; i < csv->num_rows; i++) {
        for (int j = 0; j < csv->num_cols; j++) {
            free(csv->data[i][j]);
        }
        free(csv->data[i]);
    }
    free(csv->data);

    // Reset struct supaya aman jika dipakai ulang setelah free
    csv->data = NULL;
    csv->num_rows = 0;
    csv->num_cols = 0;
}


void print_csv(const CSVData* csv) 
    // Fungsi untuk menampilkan isi CSV ke layar
    // Parameter:
    //   - csv: pointer ke struktur CSVData yang berisi data CSV yang sudah diparsing
    {
    // Loop setiap baris
    for (int i = 0; i < csv->num_rows; i++) {
        // Loop setiap kolom pada baris ke-i
        for (int j = 0; j < csv->num_cols; j++) {
            printf("%s", csv->data[i][j]);  // Tampilkan field saat ini
            
            // Tambahkan koma sebagai pemisah kecuali di kolom terakhir
            if (j < csv->num_cols - 1) {
                printf(", ");
            }
        }
        printf("\n");  // Baris baru setelah semua kolom ditampilkan
    }
}

void save_csv_data(const CSVData* csv, const char* file_path) 
    /**
     * save_csv_data - Menyimpan data CSV yang sudah dimanipulasi ke file CSV baru (overwrite)
     * 
     * csv: pointer ke CSVData yang berisi data yang ingin disimpan
     * file_path: path file CSV tujuan yang akan di-overwrite
     * 
     * Deskripsi:
     *   Fungsi ini menulis kembali data CSV dari struktur CSVData ke dalam file teks,
     *   tiap baris dipisah oleh newline, tiap kolom dipisah oleh koma ','.
     *   File lama akan ditimpa (overwrite).
     */
    {
    FILE* file = fopen(file_path, "w");    // Buka file untuk tulis, overwrite jika sudah ada
    if (!file) {
        perror("Gagal membuka file untuk menulis");
        return;
    }

    // Iterasi tiap baris data CSV
    for (int i = 0; i < csv->num_rows; i++) {
        // Iterasi tiap kolom dalam baris
        for (int j = 0; j < csv->num_cols; j++) {
            fprintf(file, "%s", csv->data[i][j]);  // Tulis data kolom
            if (j < csv->num_cols - 1) {
                fputc(',', file);                    // Tambahkan koma sebagai delimiter, kecuali kolom terakhir
            }
        }
        fputc('\n', file);  // Akhiri baris dengan newline
    }

    fclose(file);  // Tutup file setelah selesai menulis
}

