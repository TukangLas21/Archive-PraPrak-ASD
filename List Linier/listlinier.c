#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>

Address newNode(ElType val) {
    Address p = (Address)malloc(sizeof(Node));
    if (p != NULL) {
        p->info = val;
        p->next = NULL;
    }
    return p;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    *l = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong */
{
    return l == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
    int i = 0;
    Address p = l;
    while (i < idx) {
        i++;
        p = p->next;
    }
    return p->info;
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
    int i = 0;
    Address p = *l;
    while (i < idx) {
        i++;
        p = p->next;
    }
    p->info = val;
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
    int idx = 0;
    Address p = l;
    while (p != NULL) {
        if (p->info == val) return idx;
        idx++;
        p = p->next;
    }
    return IDX_UNDEF;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
{
    Address p = newNode(val);
    if (p != NULL) {
        p->next = *l;
        *l = p;
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
        Address p = newNode(val);
        if (p != NULL) {
            int i = 0;
            Address loc = *l;
            while (loc->next != NULL) {
                loc = loc->next;
            }
            loc->next = p;
        }
        
    }
}

void insertAt(List *l, ElType val, int idx)
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    if (idx == 0) insertFirst(l, val);
    else {
        Address p = newNode(val);
        if (p != NULL) {
            int i = 0;
            Address loc = *l;
            while (i < idx-1) {
                i++;
                loc = loc->next;
            }
            p->next = loc->next;
            loc->next = p;
        }
    }
    
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
{
    Address p = *l;
    *val = p->info;
    *l = p->next;
    free(p);
}

void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
{
    Address p = *l;
    Address loc = NULL;
    while (p->next != NULL) {
        loc = p;
        p = p->next;
    }
    *val = p->info;
    if (*l == p) *l = NULL; // List jadi kosong
    else {
        loc->next = NULL;
    }
    
    free(p);
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
    if (idx == 0) deleteFirst(l, val);
    else {
        Address loc = *l;
        int i = 0;
        while (i < idx-1) {
            i++;
            loc = loc->next;
        }
        Address p = loc->next;
        *val = p->info;
        loc->next = p->next;
        free(p);
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
    Address p = l;
    if (p != NULL) {
        printf("%d", p->info);
        p = p->next;
        while (p != NULL) {
            printf(",%d", p->info);
            p = p->next;
        }
    }
    
    printf("]");
}

int length(List l)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int i = 0;
    Address p = l;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    return i;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
{
    List l3;
    CreateList(&l3);

    Address p = l1;
    while (p != NULL) {
        insertLast(&l3, p->info);
        p = p->next;
    }

    p = l2;
    while (p != NULL) {
        insertLast(&l3, p->info);
        p = p->next;
    }

    CreateList(&l1);
    CreateList(&l2);

    return l3;
}