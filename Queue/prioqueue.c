#include <stdio.h>
#include "prioqueue.h"

/* *** Kreator *** */
void CreatePrioQueue(PrioQueue *pq)
/* I.S. sembarang */
/* F.S. Sebuah pq kosong terbentuk dengan kondisi sbb: */
/* - Index head bernilai IDX_UNDEF */
/* - Index tail bernilai IDX_UNDEF */
/* Proses : Melakukan alokasi, membuat sebuah pq kosong */
{
        IDX_HEAD(*pq) = IDX_UNDEF;
        IDX_TAIL(*pq) = IDX_UNDEF;
}

/* ********* Prototype ********* */
boolean isEmpty(PrioQueue pq)
/* Mengirim true jika pq kosong: lihat definisi di atas */
{
        return IDX_HEAD(pq) == IDX_UNDEF && IDX_TAIL(pq) == IDX_UNDEF;
}
boolean isFull(PrioQueue pq)
/* Mengirim true jika tabel penampung elemen pq sudah penuh */
/* yaitu IDX_TAIL akan selalu di belakang IDX_HEAD dalam buffer melingkar*/
{
        return (IDX_TAIL(pq) + 1) % CAPACITY == IDX_HEAD(pq);
}

int length(PrioQueue pq)
/* Mengirimkan banyaknya elemen prioqueue. Mengirimkan 0 jika pq kosong. */
{
        if (isEmpty(pq)) return 0;
        else if (IDX_HEAD(pq) <= IDX_TAIL(pq)) return IDX_TAIL(pq) - IDX_HEAD(pq) + 1;
        else return CAPACITY - IDX_HEAD(pq) + IDX_TAIL(pq) + 1;
}

/* *** Primitif Add/Delete *** */
void enqueue(PrioQueue *pq, ElType val)
/* Proses: Menambahkan val pada pq dengan aturan FIFO */
/* I.S. pq mungkin kosong, tabel penampung elemen pq TIDAK penuh */
/* F.S. val disisipkan pada posisi yang sesuai, IDX_TAIL "mundur" dalam buffer melingkar.,
        pq terurut mengecil */
{
        if (isEmpty(*pq)) {
                IDX_HEAD(*pq) = 0;
                IDX_TAIL(*pq) = 0;
                TAIL(*pq) = val;
        }
        else {
                int idx;
                int len = length(*pq);
                idx = len;
                for (int i = 0; i < len; i++) {
                        if ((*pq).buffer[(IDX_HEAD(*pq) + i) % CAPACITY] <= val) {
                                idx = i;
                                break;
                        }
                }

                for (int i = len-1; i >= idx; i--) {
                        (*pq).buffer[(IDX_HEAD(*pq) + i + 1) % CAPACITY] = (*pq).buffer[(IDX_HEAD(*pq) + i) % CAPACITY];
                }

                (*pq).buffer[(IDX_HEAD(*pq) + idx) % CAPACITY] = val;
                IDX_TAIL(*pq) = (IDX_TAIL(*pq) + 1) % CAPACITY;
        }
}

void dequeue(PrioQueue *pq, ElType *val)
/* Proses: Menghapus val pada pq dengan aturan FIFO */
/* I.S. pq tidak mungkin kosong */
/* F.S. val = nilai elemen HEAD pd I.S., IDX_HEAD "mundur";
        pq mungkin kosong */
{
        int len = length(*pq);
        *val = HEAD(*pq);
        IDX_HEAD(*pq) = (IDX_HEAD(*pq) + 1) % CAPACITY;
        if (len == 1) {
                IDX_HEAD(*pq) = IDX_UNDEF;
                IDX_TAIL(*pq) = IDX_UNDEF;
        }
}

/* *** Display Queue *** */
void displayPrioQueue(PrioQueue pq)
/* Proses : Menuliskan isi PrioQueue dengan traversal, PrioQueue ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. pq boleh kosong */
/* F.S. Jika pq tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 30, 20, 1 akan dicetak: [30,20,1] */
/* Jika Queue kosong : menulis [] */
{      
        int idx = 0;
        int i = IDX_HEAD(pq);
        boolean f = true;

        printf("[");
        while (idx < length(pq)) {
                if (f) {
                        printf("%d", pq.buffer[i]);
                        f = false;
                }
                else {
                        printf(",%d", pq.buffer[(i+idx)%CAPACITY]);
                }
                idx++;
        }
        printf("]\n");
}