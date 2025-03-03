#include "mesinkata.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    Word kata;
    int nilai;
} HashStr2Num;

HashStr2Num strtoNum[37] = {
    {.kata = {"nol", 3}, .nilai = 0},
    {.kata = {"satu", 4}, .nilai = 1},
    {.kata = {"dua", 3}, .nilai = 2},
    {.kata = {"tiga", 4}, .nilai = 3},
    {.kata = {"empat", 5}, .nilai = 4},
    {.kata = {"lima", 4}, .nilai = 5},
    {.kata = {"enam", 4}, .nilai = 6},
    {.kata = {"tujuh", 5}, .nilai = 7},
    {.kata = {"delapan", 7}, .nilai = 8},
    {.kata = {"sembilan", 8}, .nilai = 9},
    {.kata = {"sepuluh", 7}, .nilai = 10},
    {.kata = {"sebelas", 7}, .nilai = 11},
    {.kata = {"dua belas", 9}, .nilai = 12},
    {.kata = {"tiga belas", 10}, .nilai = 13},
    {.kata = {"empat belas", 11}, .nilai = 14},
    {.kata = {"lima belas", 10}, .nilai = 15},
    {.kata = {"enam belas", 10}, .nilai = 16},
    {.kata = {"tujuh belas", 11}, .nilai = 17},
    {.kata = {"delapan belas", 13}, .nilai = 18},
    {.kata = {"sembilan belas", 14}, .nilai = 19},
    {.kata = {"dua puluh", 9}, .nilai = 20},
    {.kata = {"tiga puluh", 10}, .nilai = 30},
    {.kata = {"empat puluh", 11}, .nilai = 40},
    {.kata = {"lima puluh", 10}, .nilai = 50},
    {.kata = {"enam puluh", 10}, .nilai = 60},
    {.kata = {"tujuh puluh", 11}, .nilai = 70},
    {.kata = {"delapan puluh", 13}, .nilai = 80},
    {.kata = {"sembilan puluh", 14}, .nilai = 90},
    {.kata = {"seratus", 7}, .nilai = 100},
    {.kata = {"dua ratus", 9}, .nilai = 200},
    {.kata = {"tiga ratus", 9}, .nilai = 300},
    {.kata = {"empat ratus", 11}, .nilai = 400},
    {.kata = {"lima ratus", 10}, .nilai = 500},
    {.kata = {"enam ratus", 10}, .nilai = 600},
    {.kata = {"tujuh ratus", 11}, .nilai = 700},
    {.kata = {"delapan ratus", 13}, .nilai = 800},
    {.kata = {"sembilan ratus", 14}, .nilai = 900}
};

#define mapsize sizeof(strtoNum) 
#define hashsize sizeof(HashStr2Num) 

boolean isKataInMap (Word w1, Word w2) {
    if (w1.Length != w2.Length) return false;
    else {
        for (int i = 0; i < w1.Length; i++) {
            if (w1.TabWord[i] != w2.TabWord[i]) return false;
        }
        return true;
    }
}

int nilaiKata (Word w) {
    int i = 0;
    while (i < mapsize / hashsize && !isKataInMap(w, strtoNum[i].kata)) i++;

    if (i == mapsize / hashsize) return -1;
    else return strtoNum[i].nilai;
}

void bikinKata (Word w1, Word w2, Word *w3) {
    int count = 0;
    for (int i = 0; i < w1.Length; i++) {
        w3->TabWord[count] = w1.TabWord[i];
        count++;
    }
    w3->TabWord[count] = ' ';
    count++;

    for (int i = 0; i < w2.Length; i++) {
        w3->TabWord[count] = w2.TabWord[i];
        count++;
    }
    w3->Length = count;
}

int limit(int x) {
    if (x >= 1000) return 1000;
    else if (x >= 100 && x < 1000) return 100;
    else if (x >= 10 && x < 100) return 10;
    else return 0;
}

void printKata(Word w) {
    for (int i = 0; i < w.Length; i++) {
        printf("%c", w.TabWord[i]);
    }
}

int main() {
    Word w1, w2, w3;
    int sum, b = 0;
    int a = 1000;

    STARTWORD();
    w2 = currentWord;
    while (!EndWord) {
        w1 = w2;
        ADVWORD();
        w2 = currentWord;
        bikinKata(w1, w2, &w3);

        if (nilaiKata(w3) != -1) {
            b = nilaiKata(w3);
            ADVWORD();
            w2 = currentWord;
        }
        else if (nilaiKata(w1) != -1) {
            b = nilaiKata(w1);
        }
        else b = -1;

        if (b != -1 && b < limit(a)) {
            sum += b;
            a = b;
        }
        else {
            if (a != 1000) {
                printf("%d", sum);
                printf(" ");

                if (b == -1) {
                    printKata(w1);

                    if (!EndWord) printf(" ");
                }
            }
            else {
                printKata(w1);
                if (!EndWord) printf(" ");
            }
            
            if (b != -1) {
                sum = b;
                a = b;
            }
            else {
                sum = 0;
                a = 1000;
            }
        }
    }

    if (nilaiKata(w3) != -1) printf("%d", sum);
    else if (nilaiKata(w1) != -1) printf("%d", sum);

    printf("\n");
    return 0;
}