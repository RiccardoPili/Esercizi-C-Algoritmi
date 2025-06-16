/************************************
 * Struttura dati degli alberi k-ari
 ************************************/

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

// ------------- STRUTTURA DATI ALBERO K-ARIO -------------
struct kTreeVertex {
    int key;
    struct kTreeVertex* child;
    struct kTreeVertex* sibling;
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

// ------------ STRUTTURA DATI AUSILIARIA QUEUE (CODE) ------------
struct queueEl {
    kTree info;
    struct queueEl* next;
};
typedef struct queueEl* queueEl;

struct queueFrame {
    struct queueEl* front;  // primo el. della coda
    struct queueEl* rear;   // ultimo el. della coda
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
void EnQueue(kTree t, queue q) {
    struct queueEl* newEl = malloc(sizeof(struct queueEl));
    newEl->info = t;
    newEl->next = NULL;
    if (q->front == NULL)
        q->front = q->rear = newEl;
    else  // q->front != NULL implica q->rear != NULL
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
    if (q->front == q->rear)  // la coda ha un solo el.
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
int sum_ktree(kTree kt) {
    if (kt == NULL)
        return 0;
    else {
        return kt->key + sum_ktree(kt->child) + sum_ktree(kt->sibling);
    }
}

/*
    post: Conta il numero di nodi interni dell'albero k-ario
*/
int count_internals(kTree kt) {
    // caso base: albero vuoto o senza figli
    if (kt == NULL || kt->child == NULL) {
        return 0;
    }

    int count = 1; // inizializza il conteggio a 1 per il nodo corrente
    kTree c = kt->child;
    while (c != NULL) {
        count += count_internals(c);  // ricorsione su ogni figlio
        c = c->sibling;             // passa al fratello successivo
    }
    return count;
}

/*
    post: somma le chiavi dei nodi interni dell'albero k-ario
*/
int sum_internals(kTree t) {
    // caso base: albero vuoto o senza figli
    if (t == NULL || t->child == NULL)
        return 0;

    int sum = t->key; // inizializza la somma con la chiave del nodo corrente
    kTree c = t->child;
    while (c != NULL) {
        sum += sum_internals(c);
        c = c->sibling;
    }
    return sum;
}

/*
    post: Altezza dell'albero k-ario (numero max di rami)
    note: usare funzione ausiliaria max
*/
int height(kTree kt) {
    // caso base: albero vuoto
    if (kt->child == NULL) {
        return 0;
    } else {
        int h = 0; // inizializza l'altezza a 0
        kTree c = kt->child;
        while (c != NULL) {
            h = max(h, height(c) + 1); // l'altezza è il max tra l'altezza corrente e quella dei figli + 1
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
int maxSumBranch(kTree t) {
    // caso base: albero senza figli (nodo foglia)
    if (t->child == NULL) {
        return t->key;
    }
    int maxSum = 0; // inizializza la somma massima a 0
    kTree c = t->child;
    while (c != NULL) {
        int sum = maxSumBranch(c); // calcola la somma del ramo corrente
        maxSum = max(maxSum, sum); // aggiorna la somma massima
        c = c->sibling;
    }
    return t->key + maxSum;
}

/*
    post: Calcola la somma delle etichette di tutte le foglie dell'albero k-ario
*/
int sumLeaf(kTree t) {
    // casi base: albero vuoto o nodo foglia
    if (t == NULL)
        return 0;
    if (t->child == NULL)
        return t->key;

    int sum = 0; // inizializza la somma a 0
    kTree c = t->child;
    while (c != NULL) {
        sum += sumLeaf(c);
        c = c->sibling;
    }
    return sum;
}

/*
    Calcola la lunghezza del ramo più breve dell'albero
    Con lunghezza si intende il numero di nodi attraversati dalla radice alla foglia
    note: l'albero k-ario si può considerare non vuoto
    note: soluzione simile ad una DFS
*/
int shortestBranch(kTree kt) {
    // caso base: albero senza figli (nodo foglia)
    if (kt->child == NULL) {
        return 1;
    }
    int res = INT_MAX; // inizializza il risultato a un valore molto grande (MAX_INT)
    kTree c = kt->child;
    while (c != NULL) {
        res = min(res, shortestBranch(c)); // la lunghezza del ramo più breve è il minimo tra i rami dei figli
        c = c->sibling;
    }
    return res + 1;  // aggiunge 1 per considerare il nodo corrente
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
    // casi base: albero vuoto o h <= 0
    if (kt == NULL)
        return 0;
    if (h == 0)
        return 1;

    int count = 1; // inizializza il conteggio a 1 per il nodo corrente
    kTree c = kt->child;
    while (c != NULL) {
        count += nodiProfondi(c, h - 1); // ricorsione sui figli, decrementando h
        c = c->sibling;
    }
    return count;
}

/*
    post: calcola il grado dell'albero k-ario, ovvero il numero massimo di figli
          che un nodo può avere (il grado massimo)
    note: usare funzione ausiliaria max
    esempio:
            12
           / | \
         22  2  5
        /   /|\
       1   8 4 6
          /
         3

    Il grado dell'albero è 3, perché il nodo con chiave 2 ha tre figli (8, 4, e 6)
*/
int degree(kTree t){
    // caso base: albero senza figli (nodo foglia)
	if(t->child == NULL)
		return 0;

	int curr = 0; // numero di figli del nodo corrente
	int max_deg = 0; // grado massimo trovato finora
	kTree c = t->child;
	while(c != NULL){
		curr++; // incremento il conteggio dei figli del nodo corrente
		max_deg = max(max_deg, degree(c)); // aggiorna il grado massimo 
		c = c->sibling;
	}
	return max(max_deg, curr); // restituisce il massimo tra il grado massimo trovato e il numero di figli del nodo corrente
}

/*
    post: restituisce la lista delle chiavi delle foglie dell'albero k-ario
    note: usare una funzione ausiliaria ricorsiva e una funzione di supporto
    per costruire la lista
    esempio:
            12
           / | \
         22  2  5
        /   /|\
       1   8 4 6
          /
         3
    La lista delle foglie sarà: [1, 3, 4, 6]
*/
list fringe_aux(kTree t, list l){
	// caso base: albero vuoto
    if (t == NULL)
		return l; // restituisce la lista

	l = fringe_aux(t->sibling, l);   // chiama sul sibling
	if (t->child == NULL)
		l = Cons(t->key, l);         // se il nodo è una foglia (non ha child), lo aggiunge alla lista
	else
		l = fringe_aux(t->child, l); // altrimenti chiama ricorsivamente sui figli

    return l; // restituisce la lista
}
list fringe(kTree t){
	return fringe_aux(t, NULL);      // funzione di supporto che chiama fringeaux con lista vuota
}


/*
    post: calcola il rango dell'albero k-ario, ovvero il numero massimo di figli
          che un nodo può avere (il grado massimo)
    note: usare una coda Queue per visitare l'albero in ampiezza (BFS)
*/
int rank(kTree kt) {
    if (kt == NULL) return 0;

    int maxRank = 0;
    queue q = NewQueue();
    EnQueue(kt, q);

    while (!isEmptyQueue(q)) {
        int childCount = 0;  // figli del nodo corrente
        kTree n = DeQueue(q);
        kTree c = n->child;
        while (c != NULL)  // scorre tutti i sibling
        {
            EnQueue(c, q);  // Aggiungi il figlio alla coda
            childCount++;
            c = c->sibling;
        }
        if (childCount > maxRank) {
            maxRank = childCount;
        }
    }
    return maxRank;
}

// ------------------------- MAIN ---------------------------
int main() {
    kTree kt =
        root(12,
             consTree(22,
                      leaf(1, NULL),
                      leaf(2,
                           root(32,
                                leaf(3,
                                     leaf(4, NULL))))));

    printf("Albero dato:\n");
    printTree(kt, 0);

    printf("\nSum all nodes: %d\n", sum_ktree(kt));

    printf("\nInternal Nodes: %d\n", count_internals(kt));

    printf("\nSum internal nodes: %d\n", sum_internals(kt));

    printf("\nAltezza albero: %d\n", height(kt));

    printf("\nSomma delle foglie: %d\n", sumLeaf(kt));

    printf("\nLunghezza Cammino minimo: %d\n", shortestBranch(kt));

    printf("\nMax somma etichette ramo: %d\n", maxSumBranch(kt));

    printf("\nNodi Profondi (livello <= 1): %d", nodiProfondi(kt, 1));
    printf("\nNodi Profondi (livello <= 2): %d\n", nodiProfondi(kt, 2));

    printf("\nRango dell'albero: %d\n", rank(kt));

    printf("\nGrado dell'albero: %d\n", degree(kt));

    printf("\nFringe (foglie) dell'albero: ");
    list leaves = fringe(kt);
    while (leaves != NULL) {
        printf("%d ", leaves->info);
        leaves = leaves->next;
    }
    printf("\n");
}
