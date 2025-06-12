#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// --------------------- METODI AUSILIARI ------------------
void swap(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void printHeapArray(int A[], int n) {
    printf("[ ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", A[i]);
    }
    printf("]\n");
}


// --------------------- ESERCIZI MIN-HEAP -------------------

/*
    Scrivere una funzione che esegua l'operazione di inserimento in un MinHeap.
    (inserimento sempre in ultima posizione e poi risalgo confrontando con parent e 
    se minore viene scambiato). Heap rappresentato come array.
*/
void Insert(int h[], int* size, int x) {
    (*size)++;              // Incrementa la dimensione dell'heap (aggiunge un nodo)
    h[*size] = x;           // Inserisce il nuovo elemento x in fondo all'heap

    int i = *size;          // Salva l'indice dell'elemento appena inserito
    while (i > 1 && h[i/2] > h[i]) { // Finché il nodo ha un genitore e il genitore è maggiore
        swap(h, i, i/2);    // Scambia il nodo con il suo genitore
        i = i / 2;          // Aggiorna l'indice per risalire l'heap
    }
}

/*
    Scrivere una funzione che implementi l'operazione di MinHeapify.
    Questa funzione ricorsiva ricostruisce la proprietà del MinHeap a partire da un nodo i.   
*/
void MinHeapify(int h[], int size, int i) {
    int smallest = i;         // Assume che il nodo corrente sia il più piccolo
    int left = 2 * i;         // Calcola l'indice del figlio sinistro
    int right = 2 * i + 1;    // Calcola l'indice del figlio destro

    // Se il figlio sinistro esiste ed è minore del nodo corrente
    if (left <= size && h[left] < h[smallest]) {
        smallest = left;      // Aggiorna il più piccolo con il figlio sinistro
    }

    // Se il figlio destro esiste ed è minore del più piccolo finora trovato
    if (right <= size && h[right] < h[smallest]) {
        smallest = right;     // Aggiorna il più piccolo con il figlio destro
    }

    // Se il più piccolo non è il nodo corrente
    if (smallest != i) {
        swap(h, i, smallest);                // Scambia il nodo corrente con il figlio minore
        MinHeapify(h, size, smallest);       // Continua ricorsivamente nel sottoalbero
    }
}

/*
    Scrivere una funzione che implementi l'estrazione del minimo da un MinHeap 'h'
    avente h.size > 0.
    (Tolgo elemento iniziale, al suo posto ci metto quello finale e chiamo heapify).
    (Per semplicita' gli elementi dello heap sono interi).
*/
int ExtractMin(int h[], int* size) {
    // Controlla se l'heap è vuoto
    if (*size <= 0) {
        printf("Heap vuoto\n");   // Stampa messaggio di errore
        return -1;                // Ritorna valore di errore
    }

    int min = h[1];               // Salva il minimo (radice del min-heap)

    h[1] = h[*size];              // Sostituisce la radice con l'ultimo elemento
    (*size)--;                    // Decrementa la dimensione dell'heap

    MinHeapify(h, *size, 1);      // Ripristina la proprietà di min-heap partendo dalla radice

    return min;                   // Ritorna il valore minimo estratto
}



int main() {
    printf("--> TEST Insert\n");
    int minHeap[100];
    int minHeapSize = 0;
    
    printf("Inserimento elementi: 10, 5, 8, 3, 2, 7\n");
    Insert(minHeap, &minHeapSize, 10);
    Insert(minHeap, &minHeapSize, 5);
    Insert(minHeap, &minHeapSize, 8);
    Insert(minHeap, &minHeapSize, 3);
    Insert(minHeap, &minHeapSize, 2);
    Insert(minHeap, &minHeapSize, 7);
    
    printf("MinHeap dopo gli inserimenti: ");
    printHeapArray(minHeap, minHeapSize);
    

    printf("\n--> TEST ExtractMin e MinHeapify\n");
    printf("Estrazione del minimo: %d\n", ExtractMin(minHeap, &minHeapSize));
    printf("MinHeap dopo estrazione: ");
    printHeapArray(minHeap, minHeapSize);
    
    printf("Estrazione del minimo: %d\n", ExtractMin(minHeap, &minHeapSize));
    printf("MinHeap dopo estrazione: ");
    printHeapArray(minHeap, minHeapSize);
    
    return 0;
}