/*****************************************
 *  Struttura dati per le liste semplici
 *  di interi
 ******************************************/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listEl {
    int info;
    struct listEl* next;
};

typedef struct listEl* list;

list Cons(int x, list xs) {
    list newlist = malloc(sizeof(struct listEl));
    newlist->info = x;
    newlist->next = xs;
    return newlist;
}

void printlist(list l) {
    while (l != NULL) {
        printf("%d ", l->info);
        l = l->next;
    }
    printf("\n");
}

// ------------------ METODI AUSILIARI ------------------------------

list ArrayToList(int A[], int n) {
    list l = NULL;
    for (int i = n - 1; i >= 0; i--) {
        l = Cons(A[i], l);
    }
    return l;
}

list copylist(list l) {
    if (l == NULL) {
        return NULL;  // Caso base: lista vuota
    } else {
        return Cons(l->info, copylist(l->next));  // Crea il nuovo nodo e continua a copiare
    }
}

list reverse(list l) {
    list res = NULL;
    while (l != NULL) {
        res = Cons(l->info, res);
        l = l->next;
    }
    return res;
}

list concat(list a, list b) {
    list result = b;
    list a_reversed = reverse(a);
    while (a_reversed != NULL) {
        result = Cons(a_reversed->info, result);
        a_reversed = a_reversed->next;
    }
    return result;
}

// ------------------ ESERCIZI SU LISTE -------------------------

int sum_list(list l) {
    int sum = 0;
    while (l != NULL) {
        sum += l->info;
        l = l->next;
    }
    return sum;
}

int sum_list_rec(list l) {
    if (l == NULL)
        return 0;
    else {
        return l->info + sum_list_rec(l->next);
    }
}

/*
Lista ordinata
    pre: l lista di interi
    post: restituisce true se la lista è ordinata non decrescente, false altrimenti
*/
bool is_ordered(list l) {
    while (l->next != NULL) {
        if (l->info > l->next->info) return false;
        l = l->next;
    }
    return true;
}

/*
Cancellazione
    pre: x elemento/i da eliminare, l lista di interi
    post: lista modificata eliminando tutte le occorrenze di x dalla lista l
*/
list delete_all(int x, list l) {
    if (l == NULL) return l;

    if (l->info == x) {
        return delete_all(x, l->next);
    } else {
        l->next = delete_all(x, l->next);
        return l;
    }
}

/*
Unione di Liste
    pre: l, m liste ordinate crescenti di interi
    post: restituisce una nuova lista ordinata crescente unione delle liste passate come parametro
    note: l'algoritmo deve avere complessità O(n)
*/
list unione(list l, list m) {
    if (l == NULL) return m;
    if (m == NULL) return l;

    if (l->info <= m->info) {
        return Cons(l->info, unione(l->next, m));
    } else {
        return Cons(m->info, unione(l, m->next));
    }
}

/*
Unione senza duplicati
    pre: l, m liste ordinate crescenti di interi
    post: restituisce una nuova lista ordinata crescente unione delle liste passate come parametro,
    la lista non deve contenere elementi duplicati
*/
list unione_no_dup(list l, list m) {
    if (l == NULL) return m;
    if (m == NULL) return l;

    if (l->info < m->info) {
        return Cons(l->info, unione_no_dup(l->next, m));
    } else if (l->info > m->info) {
        return Cons(m->info, unione_no_dup(l, m->next));
    } else {
        return Cons(l->info, unione_no_dup(l->next, m->next));
    }
}

/*
Differenza tra Liste
    pre: l, m liste ordinate crescenti
    post: ritorna la lista crescente degli elementi in l che non sono in m
    note: usare copylist()
    esempio: l = {2 3 4 6} m = {1 2 5 7 8} risultato = {3 4 6}
*/
list diff(list l, list m) {
    list L = copylist(l);
    list M = copylist(m);
    if (L == NULL) return NULL;
    if (M == NULL) return L;

    if (L->info < M->info) {
        return Cons(L->info, diff(L->next, M));
    } else if (L->info == M->info) {
        return diff(L->next, M->next);
    } else {
        return diff(L, M->next);
    }
}

/*
Sottoinsiemi con liste
    pre: l, m liste ordinate crescenti
    post: true se tutti gli elementi di l sono inclusi in m
*/
bool subset(list l, list m) {
    if (l == NULL) return true;
    if (m == NULL) return false;

    if (l->info == m->info) {
        return subset(l->next, m->next);
    } else if (l->info > m->info) {
        return subset(l, m->next);
    } else {
        return false;
    }
}

/*
Intersezioni con liste
    pre: l, m liste ordinate crescenti
    post: la lista degli elementi in comune tra l e m in ordine crescente
*/
list intersect(list l, list m) {
    if (l == NULL || m == NULL) return NULL;  // intersezione vuota

    if (l->info == m->info) {
        return Cons(l->info, intersect(l->next, m->next));
    } else if (l->info < m->info) {
        return intersect(l->next, m);
    } else {
        return intersect(l, m->next);
    }
}

/*
Rango di una Lista
    pre:  l è una lista di interi, eventualmente vuota
    post: l è stata trasformata nella lista dei ranghi dei suoi
       elementi; il valore ritornato è il rango del primo elemento
       rispetto alla lista originaria (ovvero il valore del primo elemento
       della lista così come trasformata da rank()), se questa non è vuota,
       0 altrimenti
    esempio: [1, 2, 3] diventa [6, 5, 3]
*/
int rank(list l) {
    if (l == NULL)
        return 0;
    else {
        l->info = l->info + rank(l->next);
        return l->info;
    }
}

/*
MergeSort con Liste
    scrivere la funzione di fusione dell'algoritmo merge sort visto a lezione,
    ma utilizzando come struttura dati le liste invece che gli array
*/
list merge(list l, list m) {
    if (l == NULL) return m;
    if (m == NULL)
        return l;

    else {
        if (l->info <= m->info) {
            l->next = merge(l->next, m);
            return l;
        } else {
            m->next = merge(m->next, l);
            return m;
        }
    }
}

/*
Lista palindroma
    scrivere una funzione che restituisce true se la lista passata come parametro è palindroma.
    esempio:    [1, 2, 25, 36, 25, 2, 1] -> true
                [1, 2, 25, 40, 36, 2, 1] -> false
*/
bool palindrome(list l) {
    list rev = reverse(l);
    while (l != NULL) {
        if (l->info != rev->info) {
            return false;
        }
        l = l->next;
        rev = rev->next;
    }
    return true;
}

/*
Lista palindroma (senza usare reverse)
    scrivere una funzione che restituisce true se la lista passata come parametro è palindroma.
    esempio:    [1, 2, 25, 36, 25, 2, 1] -> true
                [1, 2, 25, 40, 36, 2, 1] -> false
*/
bool palindrome_no_reverse(list l) {
    list rev = NULL;
    list temp = l;

    while (temp != NULL) {
        rev = Cons(temp->info, rev);
        temp = temp->next;
    }
    while (l != NULL) {
        if (l->info != rev->info) {
            return false;
        }
        l = l->next;
        rev = rev->next;
    }
    return true;
}

/*
OddEven
    scrivere una funzione che riordini la lista passata come parametro in modo che tutti
    i dispari precedono i pari
    esempio: [1, 4, 5, 6, 7, 2] diventa [1, 5, 7, 4, 6, 2]
    note: usare funzioni ausiliarie concat e reverse
*/
list oddEven(list l) {
    list dispari = NULL;
    list pari = NULL;

    while (l != NULL) {
        if (l->info % 2 != 0) {
            dispari = Cons(l->info, dispari);
        } else {
            pari = Cons(l->info, pari);
        }
        l = l->next;
    }

    return concat(reverse(dispari), reverse(pari));
}

// ------------------------- MAIN ---------------------------
int main() {
    int arr[] = {10, 5, 8, 2, 16, 12};
    list my_list = ArrayToList(arr, sizeof(arr) / sizeof(int));
    printlist(my_list);
    printf("Somma: %d\n", sum_list(my_list));
    printf("Somma ricorsiva: %d\n", sum_list_rec(my_list));

    printf("\nUnione di liste\n");
    int a1[] = {1, 2, 3, 4, 6, 10};
    list l1 = ArrayToList(a1, sizeof(a1) / sizeof(int));
    printlist(l1);
    int a2[] = {2, 4, 5, 10};
    list l2 = ArrayToList(a2, sizeof(a2) / sizeof(int));
    printlist(l2);
    printlist(unione(l1, l2));
    printlist(unione_no_dup(l1, l2));

    printf("\nInversione di una lista\n");
    int a3[] = {1, 2, 3, 4, 6, 10};
    list l3 = ArrayToList(a3, sizeof(a3) / sizeof(int));
    printlist(l3);
    printlist(reverse(l3));

    int a4[] = {1, 2, 3, 4, 7, 10};
    list l4 = ArrayToList(a4, sizeof(a4) / sizeof(int));
    printf("\nIs ordered? %d\n", is_ordered(l4));

    printf("\nRimozione di tutti i 2 dalla lista\n");
    int a5[] = {1, 2, 3, 4, 2, 6, 2, 10};
    list l5 = ArrayToList(a5, sizeof(a5) / sizeof(int));
    printlist(l5);
    printlist(delete_all(2, l5));

    printf("\nOperazioni su Liste:\n");
    int arrA[] = {1, 2, 3, 4, 6, 10};
    int arrB[] = {2, 4, 5, 10};
    list A = ArrayToList(arrA, sizeof(arrA) / sizeof(int));
    list B = ArrayToList(arrB, sizeof(arrB) / sizeof(int));

    printf("Lista A: ");
    printlist(A);
    printf("Lista B: ");
    printlist(B);

    printf("\nDifferenza tra Liste (A - B):\n");
    printlist(diff(A, B));

    printf("\nA è sottoinsieme di B?\n");
    printf("%d\n", subset(A, B));

    printf("\nIntersezione tra Liste:\n");
    printlist(intersect(A, B));

    printf("\nLista Palindroma\n");
    int pal[] = {1, 5, 3, 4, 3, 5, 1};
    int not_pal[] = {10, 5, 8, 2, 8, 10};
    list list_pal = ArrayToList(pal, sizeof(pal) / sizeof(int));
    list list_not_pal = ArrayToList(not_pal, sizeof(not_pal) / sizeof(int));
    printlist(list_pal);
    printlist(list_not_pal);
    printf("palindrome -> pal: %d, not_pal: %d\n", palindrome(list_pal), palindrome(list_not_pal));
    printf("palindrome_no_reverse -> pal: %d, not_pal: %d\n", palindrome_no_reverse(list_pal), palindrome_no_reverse(list_not_pal));

    printf("\nOddEven\n");
    printlist(A);
    printlist(oddEven(A));
}