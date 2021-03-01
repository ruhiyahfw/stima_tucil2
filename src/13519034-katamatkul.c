#include "13519034-katamatkul.h"
#include "13519034-mesinkar.h"

boolean isKataSama(Kata k1, Kata k2){
    if (k1.Length == k2.Length){
        int i = 0;
        boolean sama = true;
        while (sama && i < k1.Length){
            if (k1.TabKata[i] != k2.TabKata[i]){
                sama=false;
            }
            else{
                i++;
            }
        }
        return sama;
    }
    else{
        return false;
    }
}

void salinkata(Kata k1, Kata *k2){
    for (int i = 0; i < k1.Length; i++){
        k2->TabKata[i] = k1.TabKata[i];
    }
    k2->Length = k1.Length;
}

void printKata(Kata kata){
    for (int i = 0; i<kata.Length; i++){
        printf("%c",kata.TabKata[i]);
    }
}

void CreateList (List *L){
    (*L).First = Nil;
}

address Alokasi (infotype X){
    address P;
    P = (address) malloc (1*sizeof(matkul));
    if (P != Nil){
        Info(P) = X;
        Next(P) = Nil;
        return P;
    }
    else{
        return Nil;
    }
}

void Dealokasi (address *P){
    free(*P);
}

addrpreq Alokpreq(address r){
    addrpreq P;
    P = (addrpreq) malloc (1*sizeof(prereq));
    if (P != Nil){
        P->pre = r;
        P->next = Nil;
        return P;
    }
    else{
        return Nil;
    }
}

void Dealokpreq (addrpreq *P){
    free (*P);
}

address Search(List L, Kata k){
    address P;
    boolean found = false;
    P = First(L);
    while (!found && P != Nil){
        if (isKataSama(P->info.nama, k)){
            found = true;
        }
        else{
            P = Next(P);
        }
    }
    return P;
}

address alamatNol(List L){
    address P;
    boolean found=false;
    P = First(L);
    while (!found && P != Nil){
        if (P->info.banyak == 0){
            found = true;
        }
        else{
            P = Next(P);
        }
    }
    return P;
}

void bacabaris(List *L){
    //baca matkulnya dulu
    Kata kata;
    address node; //untuk alamat matkul sekarang
    address P;
    int i = 0;
    while (CC != ',' && CC != '.'){
        kata.TabKata[i] = CC;
        i++;
        ADV();
    }
    kata.Length = i;

    node = Search(*L,kata);
    if (node == Nil){
        InsLastList(L,kata, &node);
    }

    if (CC != '.'){ // artinya punya prereq
        //baca pre-requisites nya
        ADV();
        while (CC != '\n' && CC !='\0' && CC !='.'){
            // baca kata
            Kata kata1;
            i = 0;
            while (CC != ',' && CC != '.'){
                kata1.TabKata[i] = CC;
                i++;
                ADV();
            }
            kata1.Length=i;            

            // cari udah didaftarkan belum terus isi prereq
            P = Search(*L,kata1);
            if (P != Nil){
                InsLastPrereq(&node, P);
            }
            else{
                address dummy;
                InsLastList(L,kata1,&dummy);
                InsLastPrereq(&node, dummy);
            }
            // setelan akhir
            node->info.banyak++;
            if (CC == '.'){
                ADV();
            }
            ADV();
        }
    }
    else{
        ADV();
        ADV();
    }
}

void bacaTeks(List *L){
    while (CC != '\0'){
        bacabaris(L);
        ADV();
    }
}

void InsLastList(List *L, Kata k, address *P){
    address last;
    infotype in;

    in.banyak = 0;
    salinkata(k, &in.nama);
    in.trail=Nil;
    *P = Alokasi(in);
    if (*P != Nil){
        if (L->First==Nil){
            Next(*P) = First(*L);
            L->First = *P;
        }
        else{
            last = First(*L);
            while (Next(last) != Nil){
                last = Next(last);
            }
            Next(last) = *P;
        }
    }
}

void InsLastPrereq(address *Psekarang, address Pisi){
    addrpreq alm, pred;
    addrpreq P = Alokpreq(Pisi);
    if (P != Nil){
        alm = (*Psekarang)->info.trail;
        pred = Nil;
        while (alm != Nil){
            pred = alm;
            alm = alm->next;
        }
        if (pred != Nil){
            alm = P;
            Next(pred) = alm;
        }
        else{
            (*Psekarang)->info.trail = P;
        }
    }
}

int getBanyakMatkul(List L){
    address P;
    int i = 0;
    P = First(L);
    while (P != Nil){
        P = Next(P);
        i++;
    }
    return i;
}

void hapusSemuaPrereq(List *L, Kata kata){
    address P = First(*L);
    while (P != Nil){
        hapusPrereq(L,P,kata);
        P = Next(P);
    }
}

void hapusPrereq(List *L, address P, Kata kata){
    addrpreq alm, pred, hapus;
    int dihapus = 0;
    pred = Nil;
    alm = P->info.trail;
    while (alm != Nil){
        if (isKataSama(alm->pre->info.nama,kata)){
            if (pred == Nil){
                P->info.trail = Next(alm);
                hapus = alm;
                alm = alm->next;
                Dealokpreq(&hapus);
            }
            else{
                Next(pred) = Next(alm);
                hapus = alm;
                alm= alm->next;
                Dealokpreq(&hapus);
            } 
            dihapus++;
        }
        else{
            pred = alm;
            alm = Next(alm);
        }
    }
    P->info.banyak = P->info.banyak - dihapus;
}

void Delete(List *L, address P){
    address prec, now;
    boolean found = false;
    prec = Nil;
    now = First(*L);
    while (now != Nil && now != P){
        prec = now;
        now = Next(now);
    }
    if (prec == Nil){
        (*L).First = Next(P);
        Dealokasi(&P);
    }
    else{
        Next(prec) = Next(P);
        Dealokasi(&P);
    }
}

void salinGraf (List L){
    address P = L.First;
    while (P != Nil){
        printf("Induknya: \n");
        printKata(P->info.nama);
        printf("\n");
        printf("banyak anak = %d\n",P->info.banyak);
        if (P->info.banyak > 0){
            addrpreq alm;
            alm = P->info.trail;
            printf("anaknya: ");
            while (alm != Nil){
                printKata(alm->pre->info.nama);
                printf(",");
                alm = Next(alm);
            }
        }
        P = Next(P);
        printf("\n\n");
    }
}

void cetakRencanaMatkul (hasil jawab){
    for (int i = 0; i < jawab.banyaksem; i++){
        printf("Semester %d : ",i+1);
        for (int j = 0; j < jawab.diambil[i].length; j++){
            printKata(jawab.diambil[i].matakuliah[j]);
            if (j != jawab.diambil[i].length - 1){
                printf(", ");
            }
        }
        printf("\n");
    }
}