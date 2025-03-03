#include "list_circular.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
    return FIRST(l) == NULL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
    FIRST(*l) = NULL;
}

/****************** Manajemen Memori ******************/
Address allocate(ElType val)
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */
{
    Address p = (Address)malloc(sizeof(ElmtList));
    if (p != NULL) {
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}
void deallocate(Address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */
{
    free(P);
    P = NULL;
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
Address search(List l, ElType val)
/* Mencari apakah ada elemen list dengan INFO(P)= val */
/* Jika ada, mengirimkan Address elemen tersebut. */
/* Jika tidak ada, mengirimkan NULL */
{
    Address p = FIRST(l);
    if (p != NULL) {
        do
        {
            if (INFO(p) == val) return p;
            p = NEXT(p);
        } while (p != FIRST(l));
    }
    return NULL;
}

boolean addrSearch(List l, Address p)
/* Mencari apakah ada elemen list l yang beralamat p */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    Address loc = FIRST(l);
    do
    {
        if (loc == p) return true;
        loc = NEXT(loc);
    } while (loc != FIRST(l));
    return false;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */
{
    Address p = allocate(val);
    if (p != NULL) {
        if (isEmpty(*l)) { // List kosong
            FIRST(*l) = p;
            NEXT(p) = p;
        }
        else {
            Address loc = FIRST(*l);
            while (NEXT(loc) != FIRST(*l)) {
                loc = NEXT(loc);
            }
            NEXT(p) = FIRST(*l);
            NEXT(loc) = p;
            FIRST(*l) = p;
        }
    }
}
void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (isEmpty(*l)) insertFirst(l, val);
    else {
        Address p = allocate(val);
        if (p != NULL) {
            // Cari elemen terakhir
            Address loc = FIRST(*l);
            while (NEXT(loc) != FIRST(*l)) {
                loc = NEXT(loc);
            }
            NEXT(loc) = p;
            NEXT(p) = FIRST(*l);
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType * val)
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama list l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Alamat elemen terakhir di-dealokasi */
{
    Address p = FIRST(*l);
    if (NEXT(p) == FIRST(*l)) {
        FIRST(*l) = NULL;
    }
    else {
        Address loc = FIRST(*l);
        while (NEXT(loc) != FIRST(*l)) {
            loc = NEXT(loc);
        }   
        FIRST(*l) = NEXT(FIRST(*l));
        NEXT(loc) = FIRST(*l);
    }
    *val = INFO(p);
    deallocate(p);
}
void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. x adalah elemen terakhir list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      Last element baru adalah predesesor elemen pertama yg lama, jika ada */
/*      Alamat elemen terakhir di-dealokasi */
{
    Address first = FIRST(*l);
    Address p = FIRST(*l);
    if (NEXT(first) == first) {
        *val = INFO(FIRST(*l));
        deallocate(FIRST(*l));
        FIRST(*l) = NULL;
    } else {
        Address loc = first;
        while (NEXT(p) != first) {
            loc = p;
            p = NEXT(p);
        }
        *val = INFO(p);
        deallocate(p);
        NEXT(loc) = first;
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    printf("[");
	if (!isEmpty(l)) {
		Address p = FIRST(l);
		if (NEXT(p) == FIRST(l)) {printf("%d", INFO(p));}
		else {
			while (NEXT(p) != FIRST(l))
			{
				printf("%d", INFO(p));
				if (NEXT(p) != FIRST(l)) {printf(",");}
				p = NEXT(p);
				}
				printf("%d", INFO(p));
		}
	}
	printf("]");
}