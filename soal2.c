/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2024/2025
 *   Modul               : 2 - Data Manipulation and external
 *   Hari dan Tanggal    : 22 April 2026
 *   Nama (NIM)          : M Faza Dzil Ikram (13224017)
 *   Nama File           : soal2.c
 *   Deskripsi           : program baca file external dan memisahkan item dengang waktu yang telah disesuaikan yaitu 08:00 - 18:00, lalu menampilkan item yang diterima dan ditolak 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char name[100];
    int total;
} Item;

int bandingkan (const void *a, const void *b) {
    return strcmp(((Item*)a)->name, ((Item*)b)->name); // fungsi buat sorting nama item yang ada di file sesuai dengan abjad
}


int main() {
    char str[100];
    scanf("%s", str); // input nama file
    // printf("%s", str);
    FILE *fp;
    fp = fopen(str, "r");
    if (fp == NULL){
        printf("File gagal dibuka");
        return 1;
    }
    // printf("File berhasil dibuka");
    /* if (strcmp(str, "file_1") == 0) { // if else untuk buka file sesuai input
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_1", "r");
    } else if (strcmp(str, "file_2") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_2", "r");
    } else if (strcmp(str, "file_3") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_3", "r");
    } else if (strcmp(str, "file_4") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_4", "r");
    } else if (strcmp(str, "file_5") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_5", "r");
    } else if (strcmp(str, "file_6") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_6", "r");
    } else if (strcmp(str, "file_7") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_7", "r");
    } else if (strcmp(str, "file_8") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_8", "r");
    }else if (strcmp(str, "file_9") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_9", "r");
    }else if (strcmp(str, "file_10") == 0) {
        fp = fopen("C:\\Users\\fazad\\Downloads\\Praktikum\\day 2 njay\\soal-2-Ajilaca\\file_10", "r");
    }else {
        printf("File tidak ditemukan.\n");
        return 1;
    } */
    char line[200];
    Item diterima[100];
    Item ditolak[100];

    int jumlah_diterima = 0, jumlah_ditolak = 0;

    while (fgets(line, sizeof(line), fp)) {         // baca file per baris
        if (line[0] == '2') { // skip baris pertama yang dimulai dengan 2, karena dalam file semuanya diawalin dengan angka 2 maka akan selalu skip untuk tanggalnya
        continue;
        }
        char time[10], name[100];
        int jumlah_barang;
        sscanf(line, "%s %s %d", time, name, &jumlah_barang); // pake sscanf buat baca file sesuai dengan memori string charnya
        int hh, mm;
        sscanf(time, "%d:%d", &hh, &mm); 
        int minutes = hh * 60 + mm;                         // konversi ke menit
        int start = 8 * 60;                                 // waktu mulai 08:00
        int end = 18 * 60;                                  // waktu selesai 18:00

        Item *list;
        int *count;
        int found = 0;
        if (minutes >= start && minutes <= end) {           // cek apakah waktu berada di jam kerja
            list = diterima;
            count = &jumlah_diterima;
        } else {
            list = ditolak;
            count = &jumlah_ditolak;
        }
        for (int i = 0; i < *count; i++) {                   // cek apakah item sudah ada di list
            if (strcmp(list[i].name, name) == 0) {
                list[i].total += jumlah_barang;              // jika sudah ada, tambahkan jumlahnya
                found = 1;
                break;
            }
        }
        if (!found) {                                       // jika gaada dilist buat sendiri
            strcpy(list[*count].name, name);
            list[*count].total = jumlah_barang; 
            (*count)++;
        }
     }
fclose(fp);
    qsort(diterima, jumlah_diterima, sizeof(struct Item), bandingkan);
    qsort(ditolak, jumlah_ditolak, sizeof(struct Item), bandingkan);
    printf("DITERIMA\n");
    for (int i = 0; i < jumlah_diterima; i++) {
        printf("%s %d\n", diterima[i].name, diterima[i].total);
    }
    printf("DITOLAK\n");
    for (int i = 0; i < jumlah_ditolak; i++) {
        printf("%s %d\n", ditolak[i].name, ditolak[i].total);
    }
    return 0;

}
