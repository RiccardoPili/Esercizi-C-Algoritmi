#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------- METODI AUSILIARI ------------------
void swap(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void printArray(int A[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("]\n");
}

// --------------------- ESERCIZI ARRAY -------------------

/*
    pre: A array di interi, n dimensione dell'array
    post: permuta gli elementi di A in modo che tutti i dispari precedano tutti i pari
            l'algoritmo deve avere complessità lineare
    note: usare la funzione ausiliaria swap
*/
void oddEven(int A[], int n) {
    // i scorre da sinistra verso destra, j da destra verso sinistra
    int i = 0;
    int j = n - 1;
    
    while (i < j) {
        while (A[i] % 2 == 1) { // scorre fino a trovare un pari
            i++;
        }
        while (A[j] % 2 == 0) { // scorre fino a trovare un dispari
            j--;
        }
        if (i < j) {
            swap(A, i, j); // scambia i due elementi
        }
    }
}

/*
    pre: A array di interi, n dimensione dell'array
    post: maxDecSeq ritorna il massimo tra le lunghezze delle sequenze decrescenti
    esempio: A = {5 6 2 8 9 6 3 4 1} restituisce 3
*/
int maxDecSeq(int A[], int n) {
    int max = 1;    // massima lunghezza trovata
    int curr = 1;   // lunghezza corrente della sottosequenza decrescente

    for (int i = 1; i < n; i++) {
        if (A[i-1] > A[i]) // finché la sequenza è decrescente incremento la lunghezza corrente
            curr++;
        else
            curr = 1; // resetto la lunghezza corrente

        if (curr > max)
            max = curr; // aggiorno la massima lunghezza trovata
    }
    return max;
}


int main() {
    int A[] = {3, 8, 5, 12, 7, 6, 9, 10, 15, 2};
    int n = sizeof(A) / sizeof(int);

    printf("Array prima di oddEven: ");
    printArray(A, n);
    printf("Massima lunghezza sottosequenza ordinata descrescente: %d\n\n", maxDecSeq(A, n));

    oddEven(A, n);

    printf("Array dopo oddEven: ");
    printArray(A, n);
    printf("Massima lunghezza sottosequenza ordinata descrescente: %d\n\n", maxDecSeq(A, n));
}
