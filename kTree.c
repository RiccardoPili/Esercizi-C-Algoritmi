/************************************
* Struttura dati degli alberi k-ari
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

// ------------- STRUTTURA DATI ALBERO K-ARIO ------------- 
struct kTreeVertex {
    int                  key;
    struct kTreeVertex*  child;
    struct kTreeVertex*  sibling;
};

typedef struct kTreeVertex* kTree;

// crea un nuovo nodo
kTree consTree(int k, kTree c, kTree s) {
    kTree t = malloc(sizeof(struct kTreeVertex));
    t->key = k;
    t->child = c;
    t->sibling = s;
    return t;
}

// il nodo foglia non può avere figli (child == NULL)
kTree leaf(int k, kTree s) {
    return consTree(k, NULL, s);
}

// il nodo radice non può avere fratelli (sibling == NULL)
kTree root(int k, kTree c) {
    return consTree(k, c, NULL);
}

// post: stampa indentata dell'albero t con margine
//       iniziale di n tab
void printTree(kTree t, int d) {
    if (t != NULL)
    for (int i = 0; i < d; ++i)
        printf("   ");
    printf("%d\n", t->key);
    kTree cl = t->child;
    while (cl != NULL) {
        printTree(cl, d + 1);
        cl = cl->sibling;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// ------------ STRUTTURA DATI AUSILIARIA QUEUE (CODE) ------------
struct queueEl {
    kTree            info;
    struct queueEl* next;
};

struct queueFrame {
    struct queueEl* front; // primo el. della coda
    struct queueEl* rear;  // ultimo el. della coda
};

typedef struct queueFrame* queue;

// post: alloca e ritorna una coda vuota
queue NewQueue() {
    queue q = malloc(sizeof(struct queueFrame));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// post: ritorna true se la coda è vuota, false altrimenti
bool isEmptyQueue(queue q) {
    return q->front == NULL;
}

// post: accoda t come ultimo elemento di q
void EnQueue (kTree t, queue q) {
    struct queueEl* newEl = malloc(sizeof(struct queueEl));
    newEl->info = t;
    newEl->next = NULL;
    if (q->front == NULL)
        q->front = q->rear = newEl;
    else // q->front != NULL implica q->rear != NULL
    {
        q->rear->next = newEl;
        q->rear = newEl;
    }
}

// pre:  q non è vuota
// post: ritorna il primo el. di q SENZA rimuoverlo da q
kTree First(queue q) {
    return q->front->info;
}

// pre:  q non è vuota
// post: ritorna il primo el. di q RIMUOVENDOLO da q
kTree DeQueue(queue q) {
    kTree t = q->front->info;
    struct queueEl* oldFirst = q->front;
    if (q->front == q->rear) // la coda ha un solo el.
        q->front = q->rear = NULL;
    else
        q->front = q->front->next;
    free(oldFirst);
    return t;
}



// ---------------- ESERCIZI SU ALBERI K-ARI -----------------

/*
    post: somma di tutti i nodi dell'albero k-ario
*/
int sum_ktree(kTree kt){
    if(kt == NULL) return 0;
    else{
        return kt->key + sum_ktree(kt->child) + sum_ktree(kt->sibling);
    }
}

/*
    post: Conta il numero di nodi interni (che hanno almeno una foglia)
*/
int count_internals(kTree kt) {
    if (kt == NULL || kt->child == NULL) {
        return 0;
    }
    int sum = 1;
    kTree c = kt->child;
    while (c != NULL) {
        sum += count_internals(c);  // ricorsione su ogni figlio
        c = c->sibling;  // passa al fratello successivo
    }
    return sum;
}

/*
    post: Altezza dell'albero k-ario (numero max di rami)
    note: usare funzione ausiliaria max
*/
int height(kTree kt){
    if(kt->child == NULL) {
        return 0;
    }
    else {
        int h = 0;
        kTree c = kt->child;
        while(c != NULL){
            h = max(h, height(c) + 1);
            c = c->sibling;
        }
        return h;
    }
}


/*
    pre: t!=NULL
    post: il massimo delle somme delle etichette sui rami di t
    note: usare max(int a, int b), la soluzione è simile a DFS
*/
int maxSumBranch(kTree t){
    if(t->child == NULL){
        return t->key;
    }
    int maxSum = 0;
    kTree c = t->child;
    while(c != NULL){
        int sum = maxSumBranch(c);
        maxSum = max(maxSum, sum);
        c = c->sibling;
    }
    return t->key + maxSum;
}


/*
    post: Calcola la somma delle etichette di tutte le foglie dell'albero k-ario
*/
int sumLeaf (kTree t) {
    if(t == NULL) return 0;
    if(t->child == NULL) return t->key;
    
    kTree c = t->child;
    int sum = 0;
    while(c != NULL){
        sum += sumLeaf(c);
        c = c->sibling;
    }
    return sum;
}

/*
    Calcola il grado di un albero (eventualmente anche vuoto)
    Il grado è il massimo numero di nodi figli tra tutti i nodi dell'albero
    note: la soluzione è una BFS modificata, usare la struttura dati ausiliaria Queue
*/
int rank(kTree kt) {
    if(kt == NULL) return 0;

    int maxRank = 0;
    queue q = NewQueue();
    EnQueue(kt, q);

    while(!isEmptyQueue(q)){
        int childCount = 0; //figli del nodo corrente
        kTree n = DeQueue(q);
        kTree c = n->child;
        while (c != NULL) // scorre tutti i sibling
        {
            EnQueue(c, q); // Aggiungi il figlio alla coda
            childCount++;
            c = c->sibling;
        }
        if(childCount > maxRank) {
            maxRank = childCount;
        }
    }
    return maxRank;
}

/*
    Calcola la lunghezza del ramo più breve dell'albero
    Con lunghezza si intende il numero di nodi attraversati dalla radice alla foglia
    note: l'albero k-ario si può considerare non vuoto
    note: soluzione simile ad una DFS
*/
int shortestBranch(kTree kt) {
    if (kt->child == NULL) {
        return 1; // Caso base: nodo foglia
    }
    int res = INT_MAX;
    kTree c = kt->child;
    while (c != NULL) {
        res = min(res, shortestBranch(c));
        c = c->sibling;
    }
    return res + 1; // Aggiungi 1 per il nodo corrente
}

/*
    Calcola il numero di nodi "profondi", ovvero che si trovano ad un livello
    inferiore o uguale ad h
    note: con livello 0 si intende la radice, a scendere gli altri livelli

    esempio:
            12
           / | \
         22  2  5
        /   /|\
       1   8 4 6
          /
         3

    Per h = 1, i nodi profondi sono: 12, 22, 2, 5 (totale = 4)
    Per h = 2, i nodi profondi sono: 12, 22, 2, 5, 1, 8, 4, 6 (totale = 8)
*/
int nodiProfondi(kTree kt, int h) {
    if (kt == NULL) {
        return 0;
    }
    if (h == 0) {
        return 1;
    }
    int count = 1;
    kTree c = kt->child;
    while (c != NULL) {
        count += nodiProfondi(c, h - 1);
        c = c->sibling;
    }
    return count;
}


// ------------------------- MAIN ---------------------------
int main() {
    kTree kt =
       root(12, 
            consTree(22, 
                leaf(1,NULL), 
                leaf(2, 
                    root(32, 
                        leaf(3, 
                            leaf(4, NULL)
                        )
                    )
                )
            )
       );

    printf("Albero dato:\n");
    printTree(kt, 0);

    printf("\nSum: %d\n", sum_ktree(kt));

    printf("\nInternal Nodes: %d\n", count_internals(kt));

    printf("\nAltezza albero: %d\n", height(kt));

    printf("\nMax somma etichette ramo: %d\n", maxSumBranch(kt));

    printf("\nSomma delle foglie: %d\n", sumLeaf(kt));

    printf("\nRango dell'albero: %d\n", rank(kt));

    printf("\nLunghezza Cammino minimo: %d\n", shortestBranch(kt));

    printf("\nNodi Profondi (livello <= 1): %d", nodiProfondi(kt, 1));
    printf("\nNodi Profondi (livello <= 2): %d\n", nodiProfondi(kt, 2));
}
