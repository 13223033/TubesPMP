"""
UNTUK TUBES PMP
Untuk sekarang, ini aku masukin di repository sebagai referensi kode python yang mau ditambahin ke dasar.c
Karena agak ribet, untuk sementara baru ditambahin beberapa fungsi penting dulu, lanjutannya nanti ditambahin lagi kalau perlu
"""

"""
File ini berisi fungsi-fungsi umum yang dapat digunakan dalam pengerjaan pada di file lain
Berisi fungsi-fungsi:
1. 
"""

def imp_split(string_awal, delimiter):
    """
    Fungsi split() implementasi, menerima string 'string_awal' yang akan displit berdasarkan pemisah ";" dan mengembalikan
    sebuah list of string.

    !!! Pastikan tipe parameter string!! kalau perlu, gunakan str() dan kembalikan ke tipe awal saat selesai digunakan.
    """
    parts = []                      # Deklarasi list
    part = ''                       # Deklarasi variabel tipe string yang akan
    for char in string_awal:         # terus di append (lihat else) dengan iterasi satu per satu character
        if char == delimiter:        # hingga bertemu dengan pemisah/delimiter (misal ";")
            parts.append(part)      # Lalu, list 'parts' akan di append() dengan part
            part = ''               # dan variabel part direset menjadi kosong
        elif char == '\n':      # !!!!!!!! Ini kasus khusus untuk mengatasi bug pada fungsi csv_to_list() dimana '\n' akan terbaca sebagai data
            continue                # Kemungkinan perlu diperbaiki kedepannya, tetapi untuk sekarang dapat dipakai.
        else:
            part += char            # meng-append part dengan setiap pertambahan char.
    parts.append(part)              # Ketika sampai pada string terakhir yang tidak diakhiri dengan delimiter, lakukan append terakhir
    return parts                    # return parts dengan tipe list of string


def csv_to_list(file_name):
    """
    Menerima file_path sebagai string, menggunakan open() dengan mode 'r' (read). Lalu me-return data sebagai list of list of string.
    Fungsi ini nanti dapat digunakan untuk deklarasi list baru di dalam fungsi lain

    Contoh:
    users_data = csv_to_list("user.csv")
    lalu dapat digunakan untuk mengambil satu baris data dari satu user saja dengan index, misal users_data[0]

    To do: mungkin memerlukan fungsi yang dapat menghasilkan indeks dari suatu masukan di dalam list: done
    """
    import os
    data = []                              # Membuat list of list of string
    file_path = os.path.join(os.path.dirname(__file__), "..", "data", file_name) # Mengizinkan pengguna fungsi agar hanya perlu menulis nama file di folder data. Tidak perlu ditulis seluruh file_path nya
    with open(file_path, 'r') as file:     # "with open() as file", statement untuk memastikan python membuka dan menutup file_path dengan benar, dengan menggunakan variabel file
        for line in file:                  # Untuk setiap baris/line di file:
            row = imp_split(line, ";")     # Membuat variabel row(baris) dengan memisahkan setiap data dalam satu baris dengan fungsi imp_split dengan delimiter ";"
            data.append(row)               # Data sebagai list, akan diappend dengan row sebagai list of string, menjadikannya list of list of string
    return data                            # return data dengan tipe list of list of string


def untukload(file_name, folder_path):
    """
    Menerima file_path sebagai string, menggunakan open() dengan mode 'r' (read). Lalu me-return data sebagai list of list of string.
    Fungsi ini nanti dapat digunakan untuk deklarasi list baru di dalam fungsi lain

    Contoh:
    users_data = csv_to_list("user.csv")
    lalu dapat digunakan untuk mengambil satu baris data dari satu user saja dengan index, misal users_data[0]

    To do: mungkin memerlukan fungsi yang dapat menghasilkan indeks dari suatu masukan di dalam list: done
    """
    import os
    data = []                              # Membuat list of list of string
    file_path = os.path.join(os.path.dirname(__file__), "..", "data", folder_path, file_name) # Mengizinkan pengguna fungsi agar hanya perlu menulis nama file di folder data. Tidak perlu ditulis seluruh file_path nya
    with open(file_path, 'r') as file:     # "with open() as file", statement untuk memastikan python membuka dan menutup file_path dengan benar, dengan menggunakan variabel file
        for line in file:                  # Untuk setiap baris/line di file:
            row = imp_split(line, ";")     # Membuat variabel row(baris) dengan memisahkan setiap data dalam satu baris dengan fungsi imp_split dengan delimiter ";"
            data.append(row)               # Data sebagai list, akan diappend dengan row sebagai list of string, menjadikannya list of list of string
    return data                            # return data dengan tipe list of list of string


def list_to_csv(new_data, file_name):
    """
    Menerima data baru yang sudah dimanipulasi dari data awal yang dibaca oleh csv_to_list(), serta file_path yang menunjukkan
    letak file csv. yang akan di-overwrite.
    Jadi, fungsi ini menuliskan data yang benar-benar 'baru' dalam file csv, berdasarkan list of list yang dijadikan parameter.
    Gunakan fungsi ini jika terjadi perubahan pada list setelah digunakan csv_to_list()

    Contoh:
    list_to_csv(users_data, "user.csv")
    akan memperbarui data yang telah diubah dari user.csv

    Kesimpulan:
    - Penggunaaan:
      -- Gunakan csv_to_list() dengan memasukkan data tersebut dalam suatu list
      -- List dapat diubah-ubah sesuai keperluan
      -- Ketika selesai diubah-ubah, gunakan list_to_csv() untuk memperbarui data di file csv.
    """
    import os
    file_path = os.path.join(os.path.dirname(__file__), "..", "data", file_name) # Mengizinkan pengguna fungsi agar hanya perlu menulis nama file di folder data. Tidak perlu ditulis seluruh file_path nya
    with open(file_path, 'w') as file:  # Statement memastikan python membuka dan menutup file csv. dengan benar, menggunakan variabel 'file'
        for row in new_data:            # Iterasi untuk setiap baris di parameter list 'new_data'
            line = ''                   # Buat variabel line kosong yang akan di konkatenasi dengan ";" dan data-data selanjutnya
            for i in range(len(row)):   # Gunakan panjang row sebagai range iterasi untuk
                line += row[i]              # men-konkatenasi line dengan data-data pada baris
                if i < len(row) - 1:    # Memastikan akan ditambahkan ";" setelah setiap data
                    line += ';'
            line += '\n'                # Baris baru pada setiap row
            file.write(line)            # Tulis di csv.


def in_list(x, list):
    """
    def in_list(x: char/string, list: list of string) -> bool

    Menerima parameter char/string 'x' dan mengecek apakah x ada di dalam parameter 'list'
    """
    for i in range(len(list)):
        if list[i] == x:
            return True
    return False


def in_column(x, file_name, column):
    """
    def in_column(x: string, file_path: string, column: integer) -> bool

    Menerima parameter string file_path (letak file yang dicek) dan mengecek apakah string parameter x ada di dalam kolom 'column' file tersebut.
    Dilakukan dengan memasukkan data di csv ke list of list of string data, dan mengecek apakah x ada di kolom 'colummn' list of list data tersebut.
    Hal ini dilakukan untuk memvalidasi banyak skenario di spesifikasi. Misal, jika sudah ada monster Zuko, maka tidak dapat membeli
    monster Zuko di shop, karena monster sudah dimiliki.
    """
    data = csv_to_list(file_name) # Memasukkan data di dalam csv ke list of list of string 'data'
    for i in range(1, len(data)):    # Mengecek tiap sublist di dalam list of list data
        if data[i][column] == x:  # Jika ditemukan x di dalam kolom 'column' sublist tersebut,
            return True           # return True --statement break
    return False                  # Jika tidak, default return False


def char_in_string(character, stringinput):
    """
    def char_in_string(character: char/string, stringinput: string) -> bool

    Menerima parameter 'character' dan mengecek apakah char tersebut ada di dalam 'stringinput'.
    """
    for i in range(len(stringinput)):
        if stringinput[i] == character:
            return True
    return False


def get_index(x, file_name):
    """
    def get_index(x: string, file_path: string) -> tuple integer

    Fungsi ini hanya addition untuk fungsi isMember().
    Menerima parameter yang sama persis dengan fungsi isMember(), tetapi menghasilkan tuple index(i, j) yaitu indeks
    dimana data 'x' ditemukan. Dapat menggunakan isMember() sebagai validasi awal.

    Contoh penggunaan:
    if isMember() == True:
        indeks_baris, indeks_kolom = get_index()
    """
    data = csv_to_list(file_name)
    for i in range(len(data)):
        for j in range(len(data[i])):
            if data[i][j] == x:
                return i, j
    return None, None


def get_row(x, file_name, column):
    """
    Mirip dengan get_index, hanya memeriksa pada satu kolom
    Fungsi cukup jelas.
    """
    data = csv_to_list(file_name)
    for i in range(len(data)):
        if data[i][column] == x:
            return i
    return None


def write_csv(x, file_name, index):
    """
    Fungsi prosedural sederhana untuk menuliskan sesuatu dalam csv dengan parameter indeks tertentu

    x adalah apa yang ingin ditulis di csv. Indeks berupa tuple, gunakan parentesis "()"
    """
    data = csv_to_list(file_name) # Memasukkan data di dalam csv ke dalam sebuah list 'data'
    row, column = index           # Mendeklarasikan tuple index sebagai baris dan kolom
    data[row][column] = x         # Mengubah data di list 'data' pada indeks (row, column) dengan x
    list_to_csv(data, file_name)  # Menulis ulang data baru di dalam list ke dalam csv


def read_csv(file_name, index):
    """
    Fungsi sederhana untuk membaca data pada indeks tertentu dalam csv

    Indeks berupa tuple, gunakan parentesis "()"
    """
    data = csv_to_list(file_name) # Memasukkan data di dalam csv ke dalam sebuah list 'data'
    row, column = index           # Mendeklarasikan tuple index sebagai baris dan kolom
    return data[row][column]      # Mengembalikan sebuah string yang terdapat pada list 'data'


def insert_to_csv(list, file_name, on_row):
    """
    def insert_to_csv(list:list of string, file_name: string, on_row: integer)

    Memasukkan suatu list/array ke dalam csv pada baris 'on_row'
    """
    data = csv_to_list(file_name)

    first_half = []
    for i in range(on_row):
        first_half.append(data[i])

    second_half = []
    for i in range(on_row, len(data)):
        second_half.append(data[i])

    new_data = first_half
    new_data.append(list)
    new_data.extend(second_half)
    list_to_csv(new_data, file_name)


def csv_sort(file_name, priority_columns):
    """
    def csv_sort(file_name: string, priority_columns: list of integer)

    Mengurutkan suatu file csv dengan urutan kolom prioritas 'priority_columns' berupa list of integer
    """
    # Fungsi pembantu untuk membuat list sementara
    def sorting_key(item):
        return tuple(item[col_index] for col_index in priority_columns)
    
    # Implementasi bubble sort
    data = csv_to_list(file_name)
    n = len(data)
    for i in range(n - 1):
        for j in range(1, n - i - 1):
            if sorting_key(data[j]) > sorting_key(data[j + 1]):
                # Tukar jika elemen selanjutnya lebih kecil
                data[j], data[j + 1] = data[j + 1], data[j]
    
    # Menulis data baru ke csv
    list_to_csv(data, file_name)


def remove_from_list(list, element):
    new_list = []
    for item in list:
        if item != element:
            new_list.append(item)
    return new_list

def isneg(x:str):
    if x[0] == '-':
        return True
    else:
        return False
        
def jadineg(x):
    if x[0] == '-':
        x.replace("-" , '')
        x = int(x)*-1
    return x

def isnum(x):
    try:
        int(x)
        return True
    except ValueError:
        return False

def savedata(new_data, file_name, folder_path):
    """
    Menerima data baru yang sudah dimanipulasi dari data awal yang dibaca oleh csv_to_list(), serta file_path yang menunjukkan
    letak file csv. yang akan di-overwrite.
    Jadi, fungsi ini menuliskan data yang benar-benar 'baru' dalam file csv, berdasarkan list of list yang dijadikan parameter.
    Gunakan fungsi ini jika terjadi perubahan pada list setelah digunakan csv_to_list()

    Contoh:
    list_to_csv(users_data, "user.csv")
    akan memperbarui data yang telah diubah dari user.csv

    Kesimpulan:
    - Penggunaaan:
      -- Gunakan csv_to_list() dengan memasukkan data tersebut dalam suatu list
      -- List dapat diubah-ubah sesuai keperluan
      -- Ketika selesai diubah-ubah, gunakan list_to_csv() untuk memperbarui data di file csv.
    """
    import os
    file_path = os.path.join(os.path.dirname(__file__), "..", "data", folder_path, file_name) # Mengizinkan pengguna fungsi agar hanya perlu menulis nama file di folder data. Tidak perlu ditulis seluruh file_path nya
    with open(file_path, 'w') as file:  # Statement memastikan python membuka dan menutup file csv. dengan benar, menggunakan variabel 'file'
        for row in new_data:            # Iterasi untuk setiap baris di parameter list 'new_data'
            line = ''                   # Buat variabel line kosong yang akan di konkatenasi dengan ";" dan data-data selanjutnya
            for i in range(len(row)):   # Gunakan panjang row sebagai range iterasi untuk
                line += row[i]              # men-konkatenasi line dengan data-data pada baris
                if i < len(row) - 1:    # Memastikan akan ditambahkan ";" setelah setiap data
                    line += ';'
            line += '\n'                # Baris baru pada setiap row
            file.write(line)            # Tulis di csv.