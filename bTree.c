/************************************
 *  Struttura per gli alberi binari
 *  (senza puntatore al padre)
 ************************************/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct BtreeNd {
    int key;
    struct BtreeNd* left;
    struct BtreeNd* right;
};
typedef struct BtreeNd* btree;

typedef struct {
    bool isOrdered;  // il sottoalbero è ordinato?
    int min;         // min nel sottoalbero
    int max;         // max nel sottoalbero
} Triple;

// ------------------ METODI AUSILIARI ------------------------------

btree ConsTree(int k, btree l, btree r) {
    btree rootnode = malloc(sizeof(struct BtreeNd));
    rootnode->key = k;
    rootnode->left = l;
    rootnode->right = r;
    return rootnode;
}

void printtree(btree bt, int n) {
    if (bt != NULL) {
        for (int i = 0; i < n; i++)
            printf("   ");
        printf("%d\n", bt->key);
        printtree(bt->left, n + 1);
        printtree(bt->right, n + 1);
    }
}

void printtree2(btree bt, int n) {
    for (int i = 0; i < n; i++)
        printf("   ");
    if (bt == NULL)
        printf("nil\n");
    else {
        printf("%d\n", bt->key);
        printtree2(bt->left, n + 1);
        printtree2(bt->right, n + 1);
    }
}

// --------------- ESERCIZI SU ALBERI BINARI -----------------------

/**
    post: somma di tutti i nodi dell'albero b
*/
int sum_tree(btree b) {
    if (b == NULL)
        return 0;
    else {
        return b->key + sum_tree(b->left) + sum_tree(b->right);
    }
}

/*
    post: somma di tutti i nodi che sono divisibili per 3
*/
int sum_mul3(btree b) {
    if (b == NULL) {
        return 0;
    }
    int sum = sum_mul3(b->left) + sum_mul3(b->right);
    if (b->key % 3 == 0) {
        sum += b->key;
    }
    return sum;
}

/*
    post: Conta il numero di nodi interni (che hanno almeno una foglia)
*/
int count_internals(btree b) {
    if (b == NULL || (b->left == NULL && b->right == NULL)) {
        return 0;
    } else {
        return 1 + count_internals(b->left) + count_internals(b->right);
    }
}

/*
    post: somma dei nodi interni (che hanno almeno una foglia)
*/
int sum_internals(btree b) {
    if (b == NULL || (b->left == NULL && b->right == NULL)) {
        return 0;
    } else {
        return b->key + sum_internals(b->left) + sum_internals(b->right);
    }
}

/*
    post: somma di tutte le foglie dell'albero
*/
int sum_leaf(btree b) {
    if (b == NULL) {
        return 0;
    }
    if (b->left == NULL && b->right == NULL) {
        return b->key;
    }
    return sum_leaf(b->left) + sum_leaf(b->right);
}

/*
list DescList(btree bt)
    pre: bt albero binario di ricerca
    post: lista delle chiavi di bt in ordine decrescente

list DescList_aux(btree bt, list l)
    post: ritorna la lista delle chiavi di bt in ordine descrescente davanti ad l
*/
list DescList_aux(btree bt, list l) {
    if (bt == NULL) {
        return l;
    }
    l = DescList_aux(bt->left, l);
    l = Cons(bt->key, l);
    return DescList_aux(bt->right, l);
}

list DescList(btree bt) {
    return DescList_aux(bt, NULL);
}

/*
    inserisce la chiave x nell'albero binario, mantenendo l'ordine
    restituisce l'albero binario stesso riordinato
    note: bt può essere vuoto
    note: se la chiave x è già presente non inserisce il nodo
*/
btree insert(int x, btree bt) {
    if (bt == NULL) {
        bt = ConsTree(x, NULL, NULL);
    }
    if (x < bt->key) {
        bt->left = insert(x, bt->left);
    } else if (x > bt->key) {
        bt->right = insert(x, bt->right);
    }
    return bt;
}

/*
    restituisce true se l'albero binario di ricerca è ordinato
    esempio:
            10                10
           /  \              /  \
          5    20          5    20
         / \   / \        / \   / \
        1   6 12  22     1   12 6  22
    La funzione ritorna true per il primo albero e false per il secondo.
    note: usare la struct Triple fornita e una funzione ausiliaria
*/
Triple isOrderedAux(btree bt) {
    // nodo foglia
    if (bt->left == NULL && bt->right == NULL) {
        Triple t = {true, bt->key, bt->key};
        return t;
    }
    // solo figlio sx
    else if (bt->right == NULL) {
        Triple tleft = isOrderedAux(bt->left);
        Triple t = {
            tleft.isOrdered && bt->key > tleft.max,
            tleft.min,
            bt->key};
        return t;
    }
    // solo figlio dx
    else if (bt->left == NULL) {
        Triple tright = isOrderedAux(bt->right);
        Triple t = {
            tright.isOrdered && bt->key < tright.min,
            bt->key,
            tright.max};
        return t;
    }
    // entrambi i figli
    else {
        Triple tleft = isOrderedAux(bt->left);
        Triple tright = isOrderedAux(bt->right);
        Triple t = {
            tleft.isOrdered && tright.isOrdered && bt->key > tleft.max && bt->key < tright.min,
            tleft.min,
            tright.max};
        return t;
    }
}

bool isOrdered(btree bt) {
    // passo base: albero vuoto
    if (bt == NULL) return true;
    // passi ricorsivi: funzione ausiliaria
    else {
        Triple t = isOrderedAux(bt);
        return t.isOrdered;
    }
}

/*
    Scrivere una funzione che ritorni l'antenato comune ad 'a' e 'b' più prossimo.
    'a' e 'b' sono chiavi intere, con a < b.
    esempio:
            10
           /  \
          5    20
         / \   / \
        1   6 12  22

    Se a = 1 e b = 6, l'antenato comune più prossimo è 5.
    Se a = 1 e b = 12, l'antenato comune più prossimo è 10.
    note: bt è un albero binario di ricerca ed è diverso da NULL
*/
btree antenatoComune(btree bt, int a, int b) {
    if (a <= bt->key && b >= bt->key) {
        return bt;
    } else if (bt->key < a) {
        return antenatoComune(bt->right, a, b);
    } else if (bt->key > b) {
        return antenatoComune(bt->left, a, b);
    } else {
        printf("Errore: albero o parametri non validi.\n");
        exit(EXIT_FAILURE);
    }
}

// ------------------------- MAIN ---------------------------
int main() {
    btree bt =
        ConsTree(21,
                 ConsTree(35,
                          ConsTree(9, NULL, NULL),
                          ConsTree(1, NULL, NULL)),
                 ConsTree(5, NULL, ConsTree(3, NULL, NULL)));

    printf("Albero binario BT:\n");
    printtree(bt, 0);

    printf("\nSum: %d\n", sum_tree(bt));
    printf("Sum only multiples of 3: %d\n", sum_mul3(bt));

    printf("\nCount internal nodes: %d\n", count_internals(bt));

    printf("\nSum internal nodes values: %d\n", sum_internals(bt));

    printf("\nSum Leaf values: %d\n", sum_leaf(bt));

    btree bst =
        ConsTree(10,
                 ConsTree(5,
                          ConsTree(1, NULL, NULL),
                          ConsTree(6, NULL, NULL)),
                 ConsTree(20,
                          ConsTree(12, NULL, NULL),
                          ConsTree(22, NULL, NULL)));
    printf("\nAlbero binario di ricerca BST: \n");
    printtree(bst, 0);
    printf("\nChiavi ordinate descrescenti: ");
    printlist(DescList(bst));

    printf("\nIsOrdered (BST)? %d", isOrdered(bst));
    printf("\nIsOrdered (BT)? %d\n", isOrdered(bt));

    printf("\nAntenato Comune");
    printf("\n\ttra 1 e 6: %d", antenatoComune(bst, 1, 6)->key);
    printf("\n\ttra 1 e 20: %d", antenatoComune(bst, 1, 20)->key);
    printf("\n\ttra 12 e 22: %d\n", antenatoComune(bst, 12, 22)->key);
}