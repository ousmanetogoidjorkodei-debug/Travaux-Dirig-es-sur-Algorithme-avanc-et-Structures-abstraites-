/*
 * TD2 : Complexite et Recursivite
 * Exercice 1 : Minimum d'un tableau
 * Exercice 2 : MiniMax d'une matrice
 * Exercice 3 : Puissance recursive et rapide
 * Exercice 4 : Fonctions rec1 et rec2
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10
#define LIGNES 3
#define COLS   3

/* ===================================================
   EXERCICE 1 : INDICE DU MINIMUM
   Complexite : O(n)
   =================================================== */

int indiceMin(int tab[], int taille) {
    int i;
    int index = 0;                   /* 1 affectation */
    for (i = 1; i < taille; i++) {   /* n comparaisons de boucle */
        if (tab[i] < tab[index])     /* n-1 comparaisons */
            index = i;
    }
    return index;
    /* T(n) = 1 + n + (n-1) + (n-1) = 4n - 2  => O(n) */
}

/* ===================================================
   EXERCICE 2 : MINIMAX D'UNE MATRICE
   Complexite : O(n*m)
   =================================================== */

int MiniMax(int tab[LIGNES][COLS]) {
    int i, j, max, minimax;
    for (i = 0; i < LIGNES; i++) {
        max = tab[i][0];
        for (j = 1; j < COLS; j++) {
            if (tab[i][j] > max)
                max = tab[i][j];
        }
        if (i == 0)
            minimax = max;
        else if (minimax > max)
            minimax = max;
    }
    return minimax;
    /* T(n,m) = 4*m*n + 3*n - 2  => O(n*m) */
}

/* ===================================================
   EXERCICE 3 : PUISSANCE RECURSIVE ET RAPIDE
   =================================================== */

/* Version naive : O(n) */
int puissance(int a, int i) {
    if (i == 0) return 1;
    else        return a * puissance(a, i - 1);
}

/* Version rapide (exponentiation rapide) : O(log n) */
int expRapide(int a, int i) {
    if (i == 0)
        return 1;
    else if (i % 2 == 0)
        return expRapide(a * a, i / 2);        /* carre */
    else
        return a * expRapide(a * a, i / 2);    /* impair */
}

/* Somme : sum(a^i, i=0 a n) — Complexite : O(n^2) */
int somme(int a, int n) {
    if (n == 0) return 1;
    else        return puissance(a, n) + somme(a, n - 1);
}

/* ===================================================
   EXERCICE 4 : rec1 et rec2
   =================================================== */

/* rec1 : calcule 2^n, complexite O(n) */
int rec1(int n) {
    if (n == 0) return 1;
    else        return 2 * rec1(n - 1);
}

/* rec2 : calcule aussi 2^n, mais complexite O(2^n) ! */
int rec2(int n) {
    if (n == 0) return 1;
    else        return rec2(n - 1) + rec2(n - 1);
}

/* ===================================================
   PROGRAMME PRINCIPAL DE TEST
   =================================================== */

int main() {
    printf("===== TEST EXERCICE 1 : MINIMUM =====\n");
    int tab[] = {5, 2, 4, 2, 1, 7, 9, 4, 1, 1};
    int taille = 10;
    printf("Tableau : 5 2 4 2 1 7 9 4 1 1\n");
    printf("Indice du premier minimum : %d\n", indiceMin(tab, taille));
    printf("(Valeur min = %d)\n\n", tab[indiceMin(tab, taille)]);

    printf("===== TEST EXERCICE 2 : MINIMAX =====\n");
    int matrice[LIGNES][COLS] = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    printf("Matrice : {2,3,4} {5,6,7} {8,9,10}\n");
    printf("MiniMax = %d\n\n", MiniMax(matrice));

    printf("===== TEST EXERCICE 3 : PUISSANCE =====\n");
    printf("puissance(2, 10) = %d  [O(n)]\n",  puissance(2, 10));
    printf("expRapide(2, 10) = %d  [O(log n)]\n", expRapide(2, 10));
    printf("somme(2, 4) = %d  (1+2+4+8+16 = 31) [O(n^2)]\n\n", somme(2, 4));

    printf("===== TEST EXERCICE 4 : rec1 et rec2 =====\n");
    printf("rec1(5) = %d  (calcule 2^5, O(n))\n",   rec1(5));
    printf("rec2(5) = %d  (calcule 2^5, O(2^n))\n", rec2(5));
    printf("Attention : rec2 est BEAUCOUP plus lent que rec1 !\n");

    return 0;
}
