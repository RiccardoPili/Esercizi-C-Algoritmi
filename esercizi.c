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

/**
 * -----------------------------------------------------------------------------------------------------------
 * ESERCIZI SU LISTE, ALBERI BINARI E ALBERI K-ARI
 * -----------------------------------------------------------------------------------------------------------
 */

list delete_all(int x, list l) {
    list m = copylist(l);
    if (m == NULL)
        return m;
    if (m->info == x)
        return delete_all(x, m->next);
    else {
        m->next = delete_all(x, m->next);
        return m;
    }
}

list unione(list l, list m) {
    if (l == NULL)
        return m;
    if (m == NULL)
        return l;

    if (l->info <= m->info) {
        return Cons(l->info, unione(l->next, m));
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
    btree my_tree = ConsTree(1, ConsTree(2, NULL, NULL), ConsTree(3, NULL, NULL));
    printf("Binary Tree:\n");
    printtree(my_tree, 0);

    printf("\n======================== K-TREE =======================\n\n");
    kTree my_k_tree = root(12, ConsKTree(22, leaf(1, NULL), leaf(2, NULL)));
    printf("K-ary Tree:\n");
    printKTree(my_k_tree, 0);

    return 0;
}