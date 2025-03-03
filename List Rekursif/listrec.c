#include "listrec.h"
#include <stdio.h>

/* Manajemen Memori */
Address newNode(ElType x)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NIL, dan misalnya
   menghasilkan p, maka INFO(p)=x, NEXT(p)=NIL */
/* Jika alokasi gagal, mengirimkan NIL */
{
    Address p = (Address)malloc(sizeof(Node));
    if (p != NULL) {
        p->info = x;
        p->next = NULL;
    }
    return p;
}

/* Pemeriksaan Kondisi List */
boolean isEmpty(List l)
/* Mengirimkan true jika l kosong dan false jika l tidak kosong */
{
    return l == NULL;
}
boolean isOneElmt(List l)
/* Mengirimkan true jika l berisi 1 elemen dan false jika > 1 elemen atau kosong */
{
    Address p = l;
    return p != NIL && NEXT(p) == NIL;
}

/* Primitif-Primitif Pemrosesan List */
ElType head(List l)
/* Mengirimkan elemen pertama sebuah list l yang tidak kosong */
{
    Address p = l;
    return INFO(p);
}
List tail(List l)
/* Mengirimkan list l tanpa elemen pertamanya, mungkin mengirimkan list kosong */
{
    Address p = l;
    return NEXT(p);
}
List konso(List l, ElType e)
/* Mengirimkan list l dengan tambahan e sebagai elemen pertamanya. e dialokasi terlebih dahulu. 
   Jika alokasi gagal, mengirimkan l */
{
    Address p = newNode(e);
    if (p == NIL) {
        return l;
    }
    else {
        NEXT(p) = l;
        return p;
    }
}
List konsb(List l, ElType e)
/* Mengirimkan list l dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan l */ 
{
    if (isEmpty(l)) {
        return newNode(e);
    }
    else {
        NEXT(l) = konsb(tail(l), e);
        return l;
    }
}
List copy(List l)
/* Mengirimkan salinan list Ll (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan l */ 
{
    if (isEmpty(l)) {
        return NULL; 
    } else {
        Address p = newNode(head(l));
        if (p == NIL) {
            return NULL;
        }
        NEXT(p) = copy(tail(l));
        return p;
    }  
}
List concat(List l1, List l2)
/* Mengirimkan salinan hasil konkatenasi list l1 dan l2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan NIL */
{
    if (isEmpty(l1)) {
        return copy(l2);
    } else {
        Address p = newNode(head(l1));
        if (p == NIL) {
            return NULL;
        }
        NEXT(p) = concat(tail(l1), l2);
        return p;
    }
}

/* Fungsi dan Prosedur Lain */
int length(List l)
/* Mengirimkan banyaknya elemen list l, mengembalikan 0 jika l kosong */
{
    if (isEmpty(l)) return 0;
    else return (1 + length(tail(l)));
}
boolean isMember(List l, ElType x)
/* Mengirimkan true jika x adalah anggota list l dan false jika tidak */
{
    if (isEmpty(l)) return false;
    else {
        return (head(l) == x || isMember(tail(l), x));
    }
}
void displayList(List l)
/* I.S. List l mungkin kosong */
/* F.S. Jika list tidak kosong, nilai list dicetak ke bawah */
/*      Dipisahkan dengan newline (\n) dan diakhiri dengan newline */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak:
  1
  20
  30
 */
/* Jika list kosong, tidak menuliskan apa-apa  */
{
    if (isEmpty(l)) {
        return;
    }
    else {
        printf("%d\n", INFO(l));
        displayList(tail(l));
    }
}

List insertAt(List l, ElType e, int idx) {
    if (idx == 0) {
        return konso(l, e);
    }
    else {
        NEXT(l) = insertAt(tail(l), e, idx-1);
        return l;
    }
}

List deleteFirst(List l) {
    if (l == NIL) {
        return NIL;
    }
    l = NEXT(l);
    return l;
}

List deleteAt(List l, int idx) {
    if (l == NIL || idx == 0) deleteFirst(l);
    else {
        NEXT(l) = deleteAt(tail(l), idx-1);
        return l;
    }
}

List deleteLast(List l) {
    if (l == NIL || NEXT(l) == NIL) return NIL;

    if (NEXT(NEXT(l)) == NIL) {
        NEXT(l) = NIL;
        return l;
    }

    NEXT(l) = deleteLast(NEXT(l));
    return l;
}


/*** Operasi-Operasi Lain ***/
List reverseList (List l)
/* Mengirimkan list baru, list l yang dibalik dengan menyalin semua elemen list.
Semua elemen list baru harus dialokasi */
/* Jika alokasi gagal, hasilnya list kosong */
{
    if (l == NIL) return NIL;
    if (NEXT(l) == NIL) return l;

    List reverse = reverseList(NEXT(l));

    Address new = newNode(INFO(l));
    if (new == NIL) {
        return NIL;
    }

    Address temp = reverse;
    while (NEXT(temp) != NIL) {
        temp = NEXT(temp);
    }
    NEXT(temp) = new;

    return reverse;
}

void splitOddEven (List l, List *l1, List *l2)
/* I.S. l mungkin kosong */
/* F.S. Berdasarkan l, dibentuk dua buah list l1 dan l2 */ 
/* l1 berisi semua elemen l yang genap, sedangkan l2 berisi
semua elemen l yang ganjil; semua dengan urutan yang sama seperti di l */
/* l tidak berubah: Semua elemen l1 dan l2 harus dialokasi */
/* Jika l kosong, maka l1 dan l2 kosong */
{
    if (l == NIL) return;
    if (INFO(l) % 2 == 0) {
        *l1 = konsb(*l1, INFO(l));
    }
    if (INFO(l) % 2 == 1) {
        *l1 = konsb(*l2, INFO(l));
    }
    splitOddEven(NEXT(l), l1, l2);
}

void splitOnX (List l, ElType x, List *l1, List *l2)
/* I.S. l dan x terdefinisi, l1 dan l2 sembarang. */
/* F.S. l1 berisi semua elemen l yang sebelum indeks ke-x 
      l2 berisi semua elemen l setelah indeks ke-x (termasuk indeks ke-x)
*/
{
    *l1 = NIL;
    *l2 = NIL;

    if (l == NIL) return;
    if (x == 0) {
        *l2 = l;
        return;
    }

    List temp = l;
    int idx = 0;
    while (temp != NIL && idx < x-1) {
        temp = NEXT(temp);
        idx++;
    }
    if (temp != NIL && NEXT(temp) != NIL) {
        *l1 = l;
        *l2 = NEXT(temp);
        NEXT(temp) = NIL;
    }
}

ElType getMiddle(List l)
/* I.S. l terdefinisi, bukan list kosong */
/* F.S. Mengembalikan elemen tengah dari List l */
/* Jika jumlah elemen dalam List l ganjil, elemen tengah adalah elemen yang berada di posisi tengah.
   Jika jumlah elemen dalam List l genap, elemen tengah adalah elemen di posisi tengah kedua. */
/* Contoh:
   l = [1, 2, 3, 4, 5]
   elemen tengah = 3

   l = [1, 6, 3, 10]
   elemen tengah = 3 (6 dan 3 berada di tengah, dikembalikan elemen tengah kedua, yaitu 3) */
{
    if (l == NIL) return NIL;
    Address first = l;
    Address second = l;

    while (second != NIL && NEXT(second) != NIL) {
        first = NEXT(first);
        second = NEXT(NEXT(second));
    }
    return INFO(first);
}