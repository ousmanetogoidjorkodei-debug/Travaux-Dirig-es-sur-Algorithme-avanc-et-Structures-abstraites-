/*
 * TD4 : Arbres Binaires de Recherche (ABR)
 * Exercice 1 : Insertion, recherche, occurrences, parcours, tri
 * Exercice 2 : Verifier si un arbre est un ABR
 * Exercice 3 : Trouver le plus petit element
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ===================================================
   DEFINITION DES STRUCTURES
   =================================================== */

/* Noeud d'arbre */
typedef int element_type;
typedef struct tree_node *tree_ptr;

struct tree_node {
    element_type element;
    tree_ptr left;
    tree_ptr right;
};
typedef tree_ptr SEARCH_TREE;

/* Liste chainee (reutilisee pour construire une liste triee) */
struct Element { int val; struct Element *suivant; };
typedef struct Element LISTE;

/* ===================================================
   FONCTIONS UTILITAIRES LISTE
   =================================================== */

int InsererElementEnFin(LISTE **L, int valeur) {
    LISTE *e = (LISTE*) malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = NULL;
    if (*L == NULL) { *L = e; return 1; }
    LISTE *ptr = *L;
    while (ptr->suivant) ptr = ptr->suivant;
    ptr->suivant = e;
    return 1;
}

int InsererElementEnTete(LISTE **L, int valeur) {
    LISTE *e = (LISTE*) malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = *L; *L = e;
    return 1;
}

void AfficheListe(LISTE *L) {
    if (!L) { printf("[vide]\n"); return; }
    while (L) { printf("%d", L->val); if (L->suivant) printf(" -> "); L = L->suivant; }
    printf(" -> NULL\n");
}

/* ===================================================
   EXERCICE 1 : FONCTIONS SUR L'ABR
   =================================================== */

/* 1. Inserer une valeur dans l'ABR
      Complexite : O(h) ou h = hauteur de l'arbre
      Meilleur cas : O(log n), Pire cas : O(n) */
SEARCH_TREE insert(element_type x, SEARCH_TREE T) {
    if (T == NULL) {
        T = (SEARCH_TREE) malloc(sizeof(struct tree_node));
        if (!T) { printf("Memoire insuffisante\n"); exit(0); }
        T->element = x;
        T->left = T->right = NULL;
    } else if (x <= T->element)
        T->left  = insert(x, T->left);
    else
        T->right = insert(x, T->right);
    return T;
}

/* 2. Chercher une valeur dans l'ABR
      Complexite : O(h) */
tree_ptr RechercherElement(SEARCH_TREE Arbre, element_type e) {
    if (Arbre == NULL)         return NULL;
    if (e == Arbre->element)   return Arbre;
    else if (e > Arbre->element)
        return RechercherElement(Arbre->right, e);
    else
        return RechercherElement(Arbre->left,  e);
}

/* 3. Nombre d'occurrences d'une valeur
      Complexite : O(n) — parcours complet */
void NombreOccurences(SEARCH_TREE A, element_type e, int *nombre) {
    if (A != NULL) {
        NombreOccurences(A->left,  e, nombre);
        if (A->element == e) (*nombre)++;
        NombreOccurences(A->right, e, nombre);
    }
}

/* 4. Affichage infixe (donne les valeurs en ordre croissant)
      Complexite : O(n) */
void ParcoursInfixe(tree_ptr Arbre) {
    if (Arbre != NULL) {
        ParcoursInfixe(Arbre->left);
        printf("%d ", Arbre->element);
        ParcoursInfixe(Arbre->right);
    }
}

/* Affichage prefixe (racine, gauche, droite) */
void ParcoursPrefixe(tree_ptr Arbre) {
    if (Arbre != NULL) {
        printf("%d ", Arbre->element);
        ParcoursPrefixe(Arbre->left);
        ParcoursPrefixe(Arbre->right);
    }
}

/* 5. Construire une liste triee a partir d'un ABR (parcours infixe)
      Complexite : O(n) */
void ConstListeTriee(SEARCH_TREE A, LISTE **L) {
    if (A != NULL) {
        ConstListeTriee(A->left, L);
        InsererElementEnFin(L, A->element);
        ConstListeTriee(A->right, L);
    }
}

/* 6. Construire un ABR a partir d'une liste
      Complexite : O(n log n) en moyenne */
SEARCH_TREE ArbreAPartirDeListe(LISTE *L) {
    SEARCH_TREE A = NULL;
    while (L != NULL) {
        A = insert(L->val, A);
        L = L->suivant;
    }
    return A;
}

/* 7. Trier une liste via ABR
      Complexite : O(n log n) en moyenne */
LISTE* TrierListe(LISTE *L) {
    SEARCH_TREE A = ArbreAPartirDeListe(L);
    LISTE *ptr = NULL;
    ConstListeTriee(A, &ptr);
    return ptr;
}

/* ===================================================
   EXERCICE 2 : VERIFIER SI UN ARBRE EST UN ABR
   Complexite : O(n)
   Idee : le parcours infixe d'un ABR donne une liste triee
   =================================================== */
int EstCeQueABR(SEARCH_TREE A) {
    if (A == NULL) return 0;
    if (!A->left && !A->right) return 1;  /* feuille = ABR */

    LISTE *L = NULL;
    ConstListeTriee(A, &L);

    while (L->suivant != NULL) {
        if (L->val > L->suivant->val) return 0;  /* pas trie => pas ABR */
        L = L->suivant;
    }
    return 1;
}

/* ===================================================
   EXERCICE 3 : PLUS PETIT ELEMENT D'UN ABR
   Dans un ABR, le plus petit est le plus a gauche.
   Complexite : O(h)
   =================================================== */
element_type LePlusPetit(SEARCH_TREE A) {
    while (A->left != NULL)
        A = A->left;
    return A->element;
}

/* ===================================================
   PROGRAMME PRINCIPAL DE TEST
   =================================================== */

int main() {
    srand(time(NULL));
    SEARCH_TREE A = NULL;
    int i, n, nbre;
    tree_ptr ptr;

    printf("===== EXERCICE 1 : ABR =====\n");

    /* Creer un ABR avec 10 entiers aleatoires */
    printf("Insertion de 10 entiers aleatoires dans l'ABR...\n");
    for (i = 1; i <= 10; i++)
        A = insert(rand() % 20, A);

    printf("Parcours infixe (ordre croissant) : ");
    ParcoursInfixe(A); printf("\n");

    printf("Parcours prefixe : ");
    ParcoursPrefixe(A); printf("\n");

    /* Rechercher un element */
    n = 5;
    ptr = RechercherElement(A, n);
    if (ptr)
        printf("Valeur %d trouvee dans l'ABR.\n", n);
    else
        printf("Valeur %d absente de l'ABR.\n", n);

    /* Nombre d'occurrences */
    nbre = 0;
    NombreOccurences(A, n, &nbre);
    printf("Nombre d'occurrences de %d : %d\n", n, nbre);

    /* Construire une liste triee */
    LISTE *LT = NULL;
    ConstListeTriee(A, &LT);
    printf("Liste triee construite depuis l'ABR : ");
    AfficheListe(LT);

    /* Creer une liste non triee et la trier */
    LISTE *L = NULL;
    for (i = 1; i <= 8; i++) InsererElementEnTete(&L, rand() % 20);
    printf("\nListe non triee : "); AfficheListe(L);
    L = TrierListe(L);
    printf("Liste apres tri par ABR : "); AfficheListe(L);

    /* ===== Ex2 : Est-ce un ABR ? ===== */
    printf("\n===== EXERCICE 2 : EST-CE UN ABR ? =====\n");
    printf("L'arbre A est %sABR.\n", EstCeQueABR(A) ? "un " : "PAS un ");

    /* Creer un arbre qui n'est PAS un ABR */
    SEARCH_TREE B = (SEARCH_TREE) malloc(sizeof(struct tree_node));
    B->element = 10;
    B->left    = (SEARCH_TREE) malloc(sizeof(struct tree_node));
    B->right   = (SEARCH_TREE) malloc(sizeof(struct tree_node));
    B->left->element  = 5;  B->left->left  = B->left->right  = NULL;
    B->right->element = 3;  B->right->left = B->right->right = NULL; /* viole la propriete ABR */
    printf("Arbre B (construit manuellement, invalide) est %sABR.\n",
           EstCeQueABR(B) ? "un " : "PAS un ");

    /* ===== Ex3 : Plus petit element ===== */
    printf("\n===== EXERCICE 3 : PLUS PETIT ELEMENT =====\n");
    printf("Plus petit element de A : %d\n", LePlusPetit(A));

    return 0;
}
