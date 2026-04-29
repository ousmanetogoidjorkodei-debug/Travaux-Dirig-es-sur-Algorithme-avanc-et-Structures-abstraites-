/*
 * TD1 : Les Structures
 * Exercice 1 : Structure Point (coordonnees 2D)
 * Exercice 2 : Structure Heure (hh:mm:ss)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TMAX 20

/* ===================================================
   EXERCICE 1 : STRUCTURE POINT
   =================================================== */

/* Definition de la structure Point */
typedef struct {
    int abs;  /* abscisse (x) */
    int ord;  /* ordonnee (y) */
} Point;

/* Saisir un point au clavier */
Point SaisirPoint() {
    Point p;
    printf("Donner les coordonnees du point (x y) : ");
    scanf("%d %d", &p.abs, &p.ord);
    return p;
}

/* Afficher un point sous le format (x,y) */
void AfficherPoint(Point p) {
    printf("(%d, %d)\n", p.abs, p.ord);
}

/* Distance par valeur */
float DistTransVal(Point p) {
    return sqrt(p.abs * p.abs + p.ord * p.ord);
}

/* Distance par adresse */
float DistTransAdr(Point *p) {
    return sqrt(p->abs * p->abs + p->ord * p->ord);
}

/* Tri a bulles d'un tableau de points par distance croissante */
void tritab(Point t[], int taille) {
    int i, j;
    Point aux;
    for (i = 0; i < taille - 1; i++)
        for (j = i + 1; j < taille; j++)
            if (DistTransVal(t[i]) > DistTransVal(t[j])) {
                aux  = t[i];
                t[i] = t[j];
                t[j] = aux;
            }
}

/* ===================================================
   EXERCICE 2 : STRUCTURE HEURE
   =================================================== */

typedef struct {
    int hh;
    int mm;
    int ss;
} Heure;

/* Heure -> secondes */
int HeureEnSecondes(Heure h) {
    return (h.hh * 3600 + h.mm * 60 + h.ss);
}

/* Secondes -> Heure */
Heure SecondesEnHeure(int sec) {
    Heure h;
    h.hh = sec / 3600;
    sec  = sec % 3600;
    h.mm = sec / 60;
    sec  = sec % 60;
    h.ss = sec;
    return h;
}

/* Addition de deux heures */
Heure AddHeures(Heure h1, Heure h2) {
    return SecondesEnHeure(HeureEnSecondes(h1) + HeureEnSecondes(h2));
}

/* Difference entre deux heures (h2 - h1) */
Heure DiffHeures(Heure h1, Heure h2) {
    int diff = HeureEnSecondes(h2) - HeureEnSecondes(h1);
    if (diff < 0) diff = -diff; /* valeur absolue */
    return SecondesEnHeure(diff);
}

void AfficherHeure(Heure h) {
    printf("%02d:%02d:%02d\n", h.hh, h.mm, h.ss);
}

/* ===================================================
   PROGRAMME PRINCIPAL DE TEST
   =================================================== */

int main() {
    printf("===== TEST EXERCICE 1 : POINTS =====\n\n");

    /* Tableau statique */
    Point TStat[TMAX];
    int taille, i;

    srand(time(NULL));
    taille = 5;

    /* Remplissage aleatoire */
    for (i = 0; i < taille; i++) {
        TStat[i].abs = rand() % 100;
        TStat[i].ord = rand() % 100;
    }

    printf("Points avant tri :\n");
    for (i = 0; i < taille; i++) {
        printf("  Point %d : ", i);
        AfficherPoint(TStat[i]);
        printf("    Distance a l'origine : %.2f\n", DistTransVal(TStat[i]));
    }

    tritab(TStat, taille);

    printf("\nPoints apres tri par distance croissante :\n");
    for (i = 0; i < taille; i++) {
        printf("  Point %d : ", i);
        AfficherPoint(TStat[i]);
        printf("    Distance : %.2f\n", DistTransVal(TStat[i]));
    }

    /* Tableau dynamique */
    Point *TDyn = (Point*) malloc(taille * sizeof(Point));
    for (i = 0; i < taille; i++) {
        TDyn[i].abs = rand() % 100;
        TDyn[i].ord = rand() % 100;
    }
    printf("\nTableau dynamique (avant tri) :\n");
    for (i = 0; i < taille; i++) AfficherPoint(TDyn[i]);
    tritab(TDyn, taille);
    printf("Tableau dynamique (apres tri) :\n");
    for (i = 0; i < taille; i++) AfficherPoint(TDyn[i]);
    free(TDyn);

    printf("\n===== TEST EXERCICE 2 : HEURES =====\n\n");

    Heure h1 = {1, 30, 45};
    Heure h2 = {2, 45, 20};

    printf("Heure 1 : "); AfficherHeure(h1);
    printf("Heure 2 : "); AfficherHeure(h2);

    printf("h1 en secondes : %d\n", HeureEnSecondes(h1));

    Heure somme = AddHeures(h1, h2);
    printf("Addition h1 + h2 : "); AfficherHeure(somme);

    Heure diff = DiffHeures(h1, h2);
    printf("Difference |h2 - h1| : "); AfficherHeure(diff);

    return 0;
}
