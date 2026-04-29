/*
 * TD3 : Listes chainees, Piles, Files
 * Exercice 1 : Creation d'une liste
 * Exercice 2 : Recherche de valeur
 * Exercice 3 : Suppression du minimum
 * Exercice 4 : Fusion de deux listes
 * Exercice 5 : Destruction d'une liste
 * Exercice 6 : Piles (pair/impair)
 * Exercice 7 : Files (palindrome)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ===================================================
   DEFINITION DE LA LISTE CHAINEE
   =================================================== */

struct Element {
    int val;
    struct Element *suivant;
};
typedef struct Element LISTE;

/* ===================================================
   EXERCICE 1 : CREATION D'UNE LISTE
   Complexite : O(1) par insertion => O(n) pour n elements
   =================================================== */

int InsererElementEnTete(LISTE **L, int valeur) {
    LISTE *element = (LISTE*) malloc(sizeof(LISTE));
    if (element == NULL) {
        printf("Probleme d'allocation memoire\n");
        return 0;
    }
    element->val     = valeur;
    element->suivant = *L;
    *L = element;
    return 1;
}

int InsererElementEnFin(LISTE **L, int valeur) {
    LISTE *element = (LISTE*) malloc(sizeof(LISTE));
    if (element == NULL) return 0;
    element->val     = valeur;
    element->suivant = NULL;
    if (*L == NULL) {
        *L = element;
        return 1;
    }
    LISTE *ptr = *L;
    while (ptr->suivant) ptr = ptr->suivant;
    ptr->suivant = element;
    return 1;
}

void AfficheListe(LISTE *L) {
    if (L == NULL) { printf("[liste vide]\n"); return; }
    while (L) {
        printf("%d", L->val);
        if (L->suivant) printf(" -> ");
        L = L->suivant;
    }
    printf(" -> NULL\n");
}

/* ===================================================
   EXERCICE 2 : RECHERCHE DE VALEUR
   Complexite : O(n)
   =================================================== */

int RechercherValeur(LISTE *L, int valeur) {
    LISTE *ptr = L;
    while (ptr) {
        if (ptr->val == valeur) return 1;  /* trouve */
        ptr = ptr->suivant;
    }
    return 0;  /* pas trouve */
}

/* ===================================================
   EXERCICE 3 : SUPPRESSION DU MINIMUM
   Complexite : O(n)
   =================================================== */

int SuppressionValeurMin(LISTE **L) {
    LISTE *ptr = *L, *pMin = NULL, *pPrec = NULL;
    int minim;

    if (!ptr) return 0;  /* liste vide */

    /* Liste a un seul element */
    if (!ptr->suivant) {
        *L = NULL;
        free(ptr);
        return 1;
    }

    /* Chercher le predecesseur du noeud minimum */
    minim = ptr->val;
    while (ptr->suivant) {
        if (minim > ptr->suivant->val) {
            minim = ptr->suivant->val;
            pMin  = ptr;  /* predecesseur du min */
        }
        ptr = ptr->suivant;
    }

    if (!pMin) {
        /* Le min est en tete */
        ptr = *L;
        *L  = (*L)->suivant;
        free(ptr);
    } else {
        ptr          = pMin->suivant;
        pMin->suivant = pMin->suivant->suivant;
        free(ptr);
    }
    return 1;
}

/* ===================================================
   EXERCICE 4 : FUSION DE DEUX LISTES
   C = A1,B1,A2,B2,...
   =================================================== */

LISTE* FusionDe2Listes(LISTE *L1, LISTE *L2) {
    LISTE *ptr1 = L1, *ptr2 = L2, *res = NULL;

    if (L1 == NULL) return L2;
    if (L2 == NULL) return L1;

    while (ptr1 && ptr2) {
        InsererElementEnFin(&res, ptr1->val);
        InsererElementEnFin(&res, ptr2->val);
        ptr1 = ptr1->suivant;
        ptr2 = ptr2->suivant;
    }
    while (ptr1) { InsererElementEnFin(&res, ptr1->val); ptr1 = ptr1->suivant; }
    while (ptr2) { InsererElementEnFin(&res, ptr2->val); ptr2 = ptr2->suivant; }

    return res;
}

/* ===================================================
   EXERCICE 5 : DESTRUCTION D'UNE LISTE
   =================================================== */

void DestructionListe(LISTE **L) {
    LISTE *ptr;
    while (*L != NULL) {
        ptr = *L;
        *L  = (*L)->suivant;
        free(ptr);
    }
}

/* ===================================================
   EXERCICE 6 : PILES (PILE D'ENTIERS)
   =================================================== */

typedef struct stack {
    int data;
    struct stack *next;
} STACK;

void push(STACK **head, int value) {
    STACK *node = (STACK*) malloc(sizeof(STACK));
    if (node == NULL) { fputs("Memoire insuffisante\n", stderr); abort(); }
    node->data = value;
    node->next = (*head == NULL) ? NULL : *head;
    *head      = node;
}

int pop(STACK **head) {
    if (*head == NULL) { fputs("Pile vide!\n", stderr); abort(); }
    STACK *top = *head;
    int value  = top->data;
    *head      = top->next;
    free(top);
    return value;
}

void AffichePile(STACK *P) {
    printf("[Sommet] ");
    while (P) { printf("%d ", P->data); P = P->next; }
    printf("[Fond]\n");
}

/* Separer pairs et impairs : pairs en bas, impairs en haut */
STACK* PairImpair(STACK *P1) {
    STACK *P2 = NULL, *P3 = NULL;
    int val;
    /* On vide P1 : pairs dans P2, impairs dans P3 */
    while (P1) {
        val = pop(&P1);
        if (val % 2 == 0) push(&P2, val);
        else               push(&P3, val);
    }
    /* On empile les impairs par-dessus les pairs dans P2 */
    while (P3) {
        val = pop(&P3);
        push(&P2, val);
    }
    return P2;
}

/* ===================================================
   EXERCICE 7 : FILES (PALINDROME)
   =================================================== */

struct queue_node { struct queue_node *next; char data; };
struct queue      { struct queue_node *first; struct queue_node *last; };

typedef struct stack SSTACK; /* reutiliser STACK avec char */

/* Pile de caracteres */
typedef struct cstack { char data; struct cstack *next; } CSTACK;

void cpush(CSTACK **head, char value) {
    CSTACK *node = (CSTACK*) malloc(sizeof(CSTACK));
    node->data = value; node->next = *head; *head = node;
}
char cpop(CSTACK **head) {
    CSTACK *top = *head; char val = top->data;
    *head = top->next; free(top); return val;
}

int enqueue(struct queue *q, char value) {
    struct queue_node *node = (struct queue_node*) malloc(sizeof(struct queue_node));
    if (!node) return 1;
    node->data = value; node->next = NULL;
    if (q->first == NULL) q->first = q->last = node;
    else { q->last->next = node; q->last = node; }
    return 0;
}

char dequeue(struct queue *q) {
    if (!q->first) return 0;
    char val = q->first->data;
    struct queue_node *tmp = q->first;
    if (q->first == q->last) q->first = q->last = NULL;
    else q->first = q->first->next;
    free(tmp);
    return val;
}

struct queue* EcrireMessage(char chaine[]) {
    int i, taille = strlen(chaine);
    struct queue *q = (struct queue*) malloc(sizeof(struct queue));
    q->first = q->last = NULL;
    for (i = 0; i < taille; i++) enqueue(q, chaine[i]);
    return q;
}

int EstPalindrome(char chaine[]) {
    int t1 = strlen(chaine) % 2;
    int t2 = strlen(chaine) / 2;
    int i;
    char c1, c2;
    CSTACK *p = NULL;
    struct queue *Q = EcrireMessage(chaine);

    /* Mettre la premiere moitie dans une pile */
    for (i = 0; i < t2; i++) cpush(&p, dequeue(Q));

    /* Si longueur impaire, sauter le caractere du milieu */
    if (t1 != 0) dequeue(Q);

    /* Comparer la deuxieme moitie avec la pile (inverse) */
    for (i = 0; i < t2; i++) {
        c1 = dequeue(Q);
        c2 = cpop(&p);
        if (c1 != c2) return 0;
    }
    return 1;
}

/* ===================================================
   PROGRAMME PRINCIPAL DE TEST
   =================================================== */

int main() {
    srand(time(NULL));

    /* --- Ex1 : Creation --- */
    printf("===== EXERCICE 1 : CREATION DE LISTE =====\n");
    LISTE *L = NULL;
    int i;
    for (i = 0; i < 10; i++) InsererElementEnTete(&L, rand() % 100);
    printf("Liste (100 elements, 10 affichees) : ");
    AfficheListe(L);

    /* --- Ex2 : Recherche --- */
    printf("\n===== EXERCICE 2 : RECHERCHE =====\n");
    int val = L->val; /* on cherche la tete (qui existe forcement) */
    printf("Chercher %d : %s\n", val, RechercherValeur(L, val) ? "TROUVE" : "ABSENT");
    printf("Chercher 999 : %s\n", RechercherValeur(L, 999) ? "TROUVE" : "ABSENT");

    /* --- Ex3 : Suppression min --- */
    printf("\n===== EXERCICE 3 : SUPPRESSION DU MIN =====\n");
    LISTE *L2 = NULL;
    InsererElementEnTete(&L2, 5); InsererElementEnTete(&L2, 2);
    InsererElementEnTete(&L2, 8); InsererElementEnTete(&L2, 1);
    InsererElementEnTete(&L2, 7);
    printf("Avant : "); AfficheListe(L2);
    SuppressionValeurMin(&L2);
    printf("Apres suppression du min : "); AfficheListe(L2);

    /* --- Ex4 : Fusion --- */
    printf("\n===== EXERCICE 4 : FUSION =====\n");
    LISTE *A = NULL, *B = NULL, *C = NULL;
    InsererElementEnFin(&A, 1); InsererElementEnFin(&A, 2); InsererElementEnFin(&A, 3);
    InsererElementEnFin(&B, 10); InsererElementEnFin(&B, 20); InsererElementEnFin(&B, 30); InsererElementEnFin(&B, 40);
    printf("A : "); AfficheListe(A);
    printf("B : "); AfficheListe(B);
    C = FusionDe2Listes(A, B);
    printf("C = fusion(A,B) : "); AfficheListe(C);

    /* --- Ex5 : Destruction --- */
    printf("\n===== EXERCICE 5 : DESTRUCTION =====\n");
    DestructionListe(&L);
    printf("Liste detruite. Pointeur : %s\n", L == NULL ? "NULL (OK)" : "non NULL (erreur)");

    /* --- Ex6 : Piles --- */
    printf("\n===== EXERCICE 6 : PILES PAIR/IMPAIR =====\n");
    STACK *P1 = NULL, *P2 = NULL;
    for (i = 1; i <= 9; i++) push(&P1, i);
    printf("P1 initiale : "); AffichePile(P1);
    P2 = PairImpair(P1);
    printf("P2 (pairs en bas, impairs en haut) : "); AffichePile(P2);

    /* --- Ex7 : Palindrome --- */
    printf("\n===== EXERCICE 7 : PALINDROME =====\n");
    char *tests[] = {"radar", "bonjour", "kayak", "hello", "racecar"};
    for (i = 0; i < 5; i++)
        printf("\"%s\" => %s\n", tests[i], EstPalindrome(tests[i]) ? "PALINDROME" : "PAS un palindrome");

    return 0;
}
