// RUHIYAH FARADISHI WIDIAPUTRI
// 13519034

#include <stdio.h>
#include "13519034-mesinkar.h"
#include "13519034-katamatkul.h"
#include "13519034-boolean.h"

int main(){
    //KAMUS
    char namafile[50];
    List data;
    hasil jawaban;

    // menyimpan dari txt dan menyimpannya
    printf("Masukkan directory file matkul (misalnya ../test/tes1.txt): \n");
    scanf("%s",namafile);
    START(namafile);
    CreateList(&data); // membuat graf yang berupa adjacency list
    bacaTeks(&data); // menyimpan isi file txt ke dalam bentuk adjacency list representasi multilist

    // mencari susunan matkul yang harus diambil per semester
    int banymatkul = getBanyakMatkul(data);
    int sem = 0;
    while (banymatkul != 0 ){
        address P = data.First;
        int i = 0;
        // menyimpan matkul dengan 0 pre-requisite ke semester
        while (P != Nil){
            if (P->info.banyak == 0){
                salinkata(P->info.nama, &jawaban.diambil[sem].matakuliah[i]);
                i++;
                banymatkul--;
            }
            P = Next(P);
        }
        jawaban.diambil[sem].length = i;
        // menghapus node yang sudah dicatat ke jawaban serta menghapus busur keluar dari node tersebut.
        for (int k=0; k<i; k++){
            P = Search(data, jawaban.diambil[sem].matakuliah[k]);
            hapusSemuaPrereq(&data,P->info.nama);
            Delete(&data, P);
        }
        sem++;
    }
    jawaban.banyaksem = sem;

    // mencetak hasil pencarian ke layar
    cetakRencanaMatkul(jawaban);

    return 0;
}

