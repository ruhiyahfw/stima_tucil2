/* File: 13519034-mesinkar.c */
/* Implementasi Mesin Karakter */

#include "13519034-mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE * teks;
static int retval;

void START(char* namafile) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	teks = fopen(namafile,"r");
       EOP = false;
	ADV();
}

void ADV() {
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = 
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(teks,"%c",&CC);
	if (retval == EOF) {
              fclose(teks);
              EOP = true;
 	}
}