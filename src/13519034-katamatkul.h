#ifndef _KATAMATKUL_H_
#define _KATAMATKUL_H_

#define NMax 50
#define Nil NULL
#include "13519034-mesinkar.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char TabKata[NMax];
    int Length;
}Kata;

typedef struct matkul *address;
typedef struct prereq *addrpreq;
typedef struct prereq{
    address pre; 
    addrpreq next;
}prereq;
typedef struct infotype{
    Kata nama;
    int banyak;
    addrpreq trail;
}infotype;
typedef struct matkul{
    infotype info;
    address next;
}matkul;

typedef struct {
    address First;
}List;

#define First(L) ((L).First);
#define Info(P) (P)->info
#define Next(P) (P)->next

typedef struct kuliah{
    Kata matakuliah[25];
    int length;
}kuliah;

typedef struct hasil{
    int banyaksem;
    kuliah diambil[10];
}hasil;

//FUNGSI DAN PROSEDUR
boolean isKataSama(Kata k1, Kata k2);
void salinkata(Kata k1, Kata *k2);
void printKata(Kata kata);

void CreateList (List *L);
address Alokasi (infotype X);
void Dealokasi (address *P);
addrpreq Alokpreq(address r);
void Dealokpreq (addrpreq *P);

void bacaTeks(List *L);
void bacabaris(List *L);

address Search(List L, Kata k);
void InsLastList(List *L, Kata k, address *last);
void InsLastPrereq(address *Psekarang, address Pisi);
void hapusSemuaPrereq(List *L, Kata kata);
void hapusPrereq(List *L, address P, Kata kata);
void Delete(List *L, address P);

address alamatNol(List L);
int getBanyakMatkul(List L);

void salinGraf(List L);
void cetakRencanaMatkul (hasil jawab);

#endif