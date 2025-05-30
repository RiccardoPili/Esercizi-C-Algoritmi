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

void printArray(int A[], int n) {
    printf("[ ");
    for (int i = 1; i < n; i++) {
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
    // Incremento la dimensione e inserisco il nuovo elemento in fondo
    (*size)++;
    h[*size] = x;
    
    // Risalgo l'albero confrontando con i genitori
    int i = *size;
    while (i > 0 && h[i/2] > h[i]) {
        swap(h, i, i/2);
        i = i/2;
    }
}

/*:
    Scrivere una funzione che implementi l'estrazione del minimo da un MinHeap 'h'
    avente h.size > 0.
    (Tolgo elemento iniziale, al suo posto ci metto quello finale e chiamo heapify).
    (Per semplicita' gli elementi dello heap sono interi).
*/
void MinHeapify(int h[], int size, int i) {
    int smallest = i;        // Inizializzo il più piccolo come la radice
    int left = 2 * i;       // Indice figlio sinistro
    int right = 2 * i + 1;   // Indice figlio destro
    
    // Se il figlio sinistro è minore della radice
    if (left < size && h[left] < h[smallest]) {
        smallest = left;
    }
    
    // Se il figlio destro è minore del più piccolo finora
    if (right < size && h[right] < h[smallest]) {
        smallest = right;
    }
    
    // Se il più piccolo non è la radice
    if (smallest != i) {
        swap(h, i, smallest);
        // Continuo ricorsivamente con il sottoalbero
        MinHeapify(h, size, smallest);
    }
}

/*
    Scrivere una funzione che implementi l'estrazione del minimo da un MinHeap 'h'
    avente h.size > 0.
    (Tolgo elemento iniziale, al suo posto ci metto quello finale e chiamo heapify).
    (Per semplicita' gli elementi dello heap sono interi).
*/
int ExtractMin(int h[], int* size) {
    // Controllo se l'heap è vuoto
    if (*size <= 0) {
        printf("Heap vuoto\n");
        return -1;  // Valore di errore
    }
    
    // Salvo il minimo da restituire
    int min = h[1];
    
    // Sposto l'ultimo elemento alla radice e diminuisco la dimensione
    h[1] = h[*size];
    (*size)--;
    
    // Ripristino la proprietà dell'heap
    MinHeapify(h, *size, 1);
    
    return min;
}



int main() {
    printf("Un MinHeap è un albero binario rappresentato come un array H con le seguenti proprieta':");
    printf("\n - H[0] = elemento fittizio");
    printf("\n - H[1] = min (radice)");
    printf("\n - left = 2 * i");
    printf("\n - right = 2 * i + 1");

    printf("\n\n--> Test MinHeap e Insert\n");
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
    printArray(minHeap, minHeapSize);
    

    printf("\n--> Test ExtractMin\n");
    printf("Estrazione del minimo: %d\n", ExtractMin(minHeap, &minHeapSize));
    printf("MinHeap dopo estrazione: ");
    printArray(minHeap, minHeapSize);
    
    printf("Estrazione del minimo: %d\n", ExtractMin(minHeap, &minHeapSize));
    printf("MinHeap dopo estrazione: ");
    printArray(minHeap, minHeapSize);
    
    return 0;
}