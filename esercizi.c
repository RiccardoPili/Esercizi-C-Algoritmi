#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

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

list copylist(list l) {
    if (l == NULL)
        return NULL;
    else {
        return Cons(l->info, copylist(l->next));
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

struct BtreeNd {
    int key;
    struct BtreeNd* left;
    struct BtreeNd* right;
};
typedef struct BtreeNd* btree;

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

struct kTreeVertex {
    int key;
    struct kTreeVertex* child;
    struct kTreeVertex* sibling;
};
typedef struct kTreeVertex* kTree;

kTree ConsKTree(int k, kTree c, kTree s) {
    kTree t = malloc(sizeof(struct kTreeVertex));
    t->key = k;
    t->child = c;
    t->sibling = s;
    return t;
}

kTree leaf(int k, kTree s) {
    return ConsKTree(k, NULL, s);
}

kTree root(int k, kTree c) {
    return ConsKTree(k, c, NULL);
}

void printKTree(kTree t, int d) {
    if (t != NULL)
        for (int i = 0; i < d; ++i)
            printf("   ");
    printf("%d\n", t->key);
    kTree cl = t->child;
    while (cl != NULL) {
        printKTree(cl, d + 1);
        cl = cl->sibling;
    }
}

typedef struct {
    bool isOrdered;  // il sottoalbero è ordinato?
    int min;         // min nel sottoalbero
    int max;         // max nel sottoalbero
} Triple;

/**
 * -----------------------------------------------------------------------------------------------------------
 * ESERCIZI SU LISTE
 * -----------------------------------------------------------------------------------------------------------
 */

list delete_all(int x, list l) {
    list m = copylist(l);
    if (m == NULL)
        return m;
    if (m->info == x)
        return delete_all(x, m->next); // se il primo elemento è uguale a x, lo salto
    else {
        m->next = delete_all(x, m->next); // aggiorno il puntatore next
        return m;
    }
}

list unione(list l, list m) {
    if (l == NULL)
        return m;
    if (m == NULL)
        return l;

    if (l->info <= m->info) {
        return Cons(l->info, unione(l->next, m)); // usa Cons per costruire la nuova lista
    } else {
        return Cons(m->info, unione(l, m->next));
    }
}

list unione_no_dup(list l, list m) {
    if (l == NULL)
        return m;
    if (m == NULL)
        return l;

    if (l->info < m->info) {
        return Cons(l->info, unione_no_dup(l->next, m));
    } else if (l->info > m->info) {
        return Cons(m->info, unione_no_dup(l, m->next));
    } else {
        return Cons(l->info, unione_no_dup(l->next, m->next));
    }
}

list difference(list l, list m) {
    if (l == NULL)
        return NULL;
    if (m == NULL)
        return l;

    if (l->info < m->info) {
        return Cons(l->info, difference(l->next, m));
    } else if (l->info > m->info) {
        return difference(l, m->next);
    } else {
        return difference(l->next, m->next);
    }
}

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

list intersect(list l, list m) {
    if (l == NULL || m == NULL) return NULL;

    if (l->info == m->info) {
        return Cons(l->info, intersect(l->next, m->next));
    } else if (l->info > m->info) {
        return intersect(l, m->next);
    } else {
        return intersect(l->next, m);
    }
}

bool palindrome(list l) {
    list rev = reverse(l);
    while (l != NULL) {
        if (l->info != rev->info) return false;
        l = l->next;
        rev = rev->next;
    }
    return true;
}

bool palindrome_no_reverse(list l) {
    list rev;
    list temp = l;

    while (temp != NULL) {
        rev = Cons(temp->info, rev);
        temp = temp->next;
    }

    while (l != NULL) {
        if (l->info != rev->info) return false;
        l = l->next;
        rev = rev->next;
    }
    return true;
}

list oddEven(list l) {
    list dispari = NULL;
    list pari = NULL;

    while (l != NULL) {
        if (l->info % 2 == 0) {
            pari = Cons(l->info, pari);
        } else {
            dispari = Cons(l->info, dispari);
        }
        l = l->next;
    }

    return concat(reverse(dispari), reverse(pari));
}

/**
 * -----------------------------------------------------------------------------------------------------------
 * ESERCIZI SU ALBERI BINARI
 * -----------------------------------------------------------------------------------------------------------
 */

int sum_tree(btree bt) {
    if (bt == NULL)
        return 0;
    else
        return bt->key + sum_tree(bt->left) + sum_tree(bt->right);
}

int sum_internals(btree bt) {
    if (bt == NULL || (bt->left == NULL && bt->right == NULL))
        return 0;
    else
        return bt->key + sum_internals(bt->left) + sum_internals(bt->right);
}

int sum_leaf(btree bt) {
    if (bt == NULL)
        return 0;
    else if (bt->left == NULL && bt->right == NULL)
        return bt->key;
    else
        return sum_leaf(bt->left) + sum_leaf(bt->right);
}

btree insert(int x, btree b) {
    if (b == NULL)
        return ConsTree(x, NULL, NULL);

    if (x < b->key)
        b->left = insert(x, b->left);
    else if (x > b->key)
        b->right = insert(x, b->right);
    else {
        perror("Errore, impossibile inserire un nodo già presente");
        exit(EXIT_FAILURE);
    }
    return b;
}

btree antenatoComune(btree bt, int a, int b) {
    if (a <= bt->key && b >= bt->key)
        return bt;
    else if (a > bt->key)
        return antenatoComune(bt->right, a, b);
    else if (b < bt->key)
        return antenatoComune(bt->left, a, b);
    else {
        perror("Errore nei parametri dell'albero");
        exit(EXIT_FAILURE);
    }
}

list DescList_aux(btree bt, list l) {
    if (bt == NULL)
        return l;
    l = DescList_aux(bt->left, l);      // visita il sottoalbero sinistro
    l = Cons(bt->key, l);               // aggiunge il nodo corrente alla lista
    return DescList_aux(bt->right, l);  // visita il sottoalbero destro
}

list DescList(btree bt) {
    return DescList_aux(bt, NULL);
}

Triple isOrderedAux(btree bt) {
    // nodo foglia
    if (bt->left == NULL && bt->right == NULL) {
        Triple t = {true, bt->key, bt->key};
        return t;
    }
    // solo nodo sinistro
    else if (bt->left != NULL && bt->right == NULL) {
        Triple tLeft = isOrderedAux(bt->left);
        Triple t = {
            tLeft.isOrdered && bt->key > tLeft.max,
            tLeft.min,
            bt->key};
        return t;
    }
    // solo nodo destro
    else if (bt->right != NULL && bt->left == NULL) {
        Triple tRight = isOrderedAux(bt->right);
        Triple t = {
            tRight.isOrdered && bt->key < tRight.min,
            bt->key,
            tRight.max};
        return t;
    }
    // entrambi i figli
    else {
        Triple tLeft = isOrderedAux(bt->left);
        Triple tRight = isOrderedAux(bt->right);
        Triple t = {
            tLeft.isOrdered && tRight.isOrdered && bt->key > tLeft.max && bt->key < tRight.min,
            tLeft.min,
            tRight.max};
        return t;
    }
}
bool isOrdered(btree bt) {
    if (bt == NULL)
        return true;
    else {
        Triple t = isOrderedAux(bt);
        return t.isOrdered;
    }
}

/**
 * -----------------------------------------------------------------------------------------------------------
 * ESERCIZI SU ALBERI K-ARY
 * -----------------------------------------------------------------------------------------------------------
 */

int sum_internals_ktree(kTree t) {
    if (t == NULL || t->child == NULL)
        return 0;
    int sum = t->key;
    kTree c = t->child;
    while (c != NULL) {
        sum += sum_internals_ktree(c);
        c = c->sibling;
    }
    return sum;
}

int height(kTree t) {
    if (t->child == NULL)
        return 0;
    int h = 0;
    kTree c = t->child;
    while (c != NULL) {
        h = max(h, height(c) + 1);
        c = c->sibling;
    }
    return h;
}

int maxSumBranch(kTree t) {
    if (t == NULL)
        return 0;
    if (t->child == NULL)
        return t->key;
    int maxSum = 0;
    kTree c = t->child;
    while (c != NULL) {
        int currSum = maxSumBranch(c);
        maxSum = max(currSum, maxSum);
        c = c->sibling;
    }
    return maxSum + t->key;
}

int sumLeaf(kTree t) {
    if (t == NULL)
        return 0;
    if (t->child == NULL)
        return t->key;

    int sum = 0;
    kTree c = t->child;
    while (c != NULL) {
        sum += sumLeaf(c);
        c = c->sibling;
    }
    return sum;
}

int shortestBranch(kTree t) {
    if (t->child == NULL)
        return 1;  // nodo foglia

    int minL = INT_MAX;
    kTree c = t->child;
    while (c != NULL) {
        int currMin = shortestBranch(c);
        minL = min(minL, currMin);
        c = c->sibling;
    }
    return minL + 1;
}

int nodiProfondi(kTree t, int h) {
    if (t == NULL)
        return 0;
    if (h == 0)
        return 1;

    int count = 1;
    kTree c = t->child;
    while (c != NULL) {
        count += nodiProfondi(c, h - 1);
        c = c->sibling;
    }
    return count;
}

int main() {
    printf("\n======================== LISTE ========================\n\n");
    list L1 = Cons(1, Cons(2, Cons(3, Cons(5, Cons(7, Cons(8, Cons(10, NULL)))))));
    list L2 = Cons(2, Cons(3, Cons(4, Cons(8, Cons(9, Cons(10, NULL))))));

    printf("Lista L1: ");
    printlist(L1);
    printf("Lista L2: ");
    printlist(L2);

    // delete_all
    printf("\nCancella tutti i 3 da L1: ");
    printlist(delete_all(3, L1));

    // unione
    printf("\nUnione di L1 e L2: ");
    printlist(unione(L1, L2));

    // unione_no_dup
    printf("\nUnione senza duplicati di L1 e L2: ");
    printlist(unione_no_dup(L1, L2));

    // difference
    printf("\nDifferenza L1 - L2: ");
    printlist(difference(L1, L2));

    // subset
    printf("\nL2 è sottoinsieme di L1? %s\n", subset(L2, L1) ? "true" : "false");
    printf("L1 è sottoinsieme di unione(L1, L2)? %s\n", subset(L1, unione(L1, L2)) ? "true" : "false");

    // intersect
    printf("\nIntersezione tra L1 e L2: ");
    printlist(intersect(L1, L2));

    // palindrome
    list pal = Cons(1, Cons(2, Cons(3, Cons(2, Cons(1, NULL)))));
    printf("\nLa lista [1,2,3,2,1] è palindroma? %s\n", palindrome(pal) ? "true" : "false");
    printf("La lista [1,2,3,2,1] è palindroma (no reverse)? %s\n", palindrome_no_reverse(pal) ? "true" : "false");

    // oddEven
    printf("\nOddEven di L1: ");
    printlist(oddEven(L1));

    printf("\n======================== B-TREE =======================\n\n");
    // ALBERO BINARIO DI RICERCA
    //         5
    //        / \
    //       3   8
    //      / \   \
    //     1   4   10
    //          \
    //           6
    btree my_tree = ConsTree(
        5,
        ConsTree(
            3,
            ConsTree(1, NULL, NULL),
            ConsTree(4, NULL, ConsTree(6, NULL, NULL))),
        ConsTree(
            8,
            NULL,
            ConsTree(10, NULL, NULL)));
    printf("Binary Tree:\n");
    printtree(my_tree, 0);

    printf("\nSomma dei nodi dell'albero: %d\n", sum_tree(my_tree));

    printf("Somma dei nodi interni dell'albero: %d\n", sum_internals(my_tree));

    printf("Somma delle foglie dell'albero: %d\n", sum_leaf(my_tree));

    printf("\nInserisco il nodo 7 nell'albero...\n");
    my_tree = insert(7, my_tree);
    printtree(my_tree, 0);

    // Prova inserimento di un duplicato (dovrebbe dare errore)
    // printf("\nProvo a inserire il nodo 3 (già presente)...\n");
    // my_tree = insert(3, my_tree);
    // printtree(my_tree, 0);

    printf("\n======================== K-TREE =======================\n\n");
    // ALBERO K-ARIO
    //         12
    //        / | \
    //      22  2  32
    //      /      / \
    //     1      3   4

    kTree kt =
        root(12,
             ConsKTree(22,
                       leaf(1, NULL),
                       leaf(2,
                            root(32,
                                 leaf(3,
                                      leaf(4, NULL))))));

    printf("K-ary Tree:\n");
    printKTree(kt, 0);

    printf("\nAltezza dell'albero k-ario: %d\n", height(kt));

    printf("Somma dei nodi interni dell'albero k-ario: %d\n", sum_internals_ktree(kt));

    printf("Max somma delle etichette dei rami: %d\n", maxSumBranch(kt));

    printf("Somma delle foglie dell'albero k-ario: %d\n", sumLeaf(kt));

    printf("Lunghezza del ramo più corto dell'albero k-ario: %d\n", shortestBranch(kt));

    printf("Numero di nodi profondi (h=1) nell'albero k-ario: %d\n", nodiProfondi(kt, 1));
    printf("Numero di nodi profondi (h=2) nell'albero k-ario: %d\n", nodiProfondi(kt, 2));
}