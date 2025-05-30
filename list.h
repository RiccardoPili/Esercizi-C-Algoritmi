#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

struct listEl {
    int            info;
    struct listEl* next;
};

typedef struct listEl* list;

list Cons(int x, list xs) {
    list newlist = malloc(sizeof(struct listEl));
    newlist->info = x;
    newlist->next = xs;
    return newlist;
}

void printlist (list l) {
    while (l != NULL) {
        printf("%d ", l->info);
        l = l->next;
    }
    printf("\n");
}


// ------------------ METODI AUSILIARI ------------------------------

list ArrayToList(int A[], int n){
    list l = NULL;
    for(int i=n-1; i>=0; i--){
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