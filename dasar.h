// dasar.h
#ifndef DASAR_H
#define DASAR_H

typedef struct {
    char*** data;
    int num_rows;
    int num_cols;
} CSVData;

char** imp_split(const char* str, char delimiter, int* count);

CSVData load_csv_data(const char* filename);
void free_csv(CSVData* csv);
void print_csv(const CSVData* csv);
void save_csv_data(const CSVData* csv, const char* file_path);

#endif
