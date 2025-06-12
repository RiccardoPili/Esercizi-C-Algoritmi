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
    int i = 0;
    int j = n - 1;
    while (i < j) {
        while (A[i] % 2 == 1) {
            i++;
        }
        while (A[j] % 2 == 0) {
            j--;
        }
        if (i < j) {
            swap(A, i, j);
        }
    }
}

/*
    pre: A array di interi, n dimensione dell'array
    post: maxDecSeq ritorna il massimo tra le lunghezze delle sequenze decrescenti
    esempio: A = {5 6 2 8 9 6 3 4 1} restituisce 3
*/
int maxDecSeq(int A[], int n) {
    int count = 1;
    int max = 1;

    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            count++;
        } else {
            if (count > max) {
                max = count;
            }
            count = 1;
        }
    }
    if (count > max) {
        max = count;
    }
    return max;
}

char *strtrim(char *s, int start, int end) {
    if (start > end || s == NULL || strlen(s) < start || strlen(s) < end) {
        return NULL;
    }
    int i;
    char *result = malloc(strlen(s) + 1);
    for (i = 0; i < start; i++) {
        result[i] = s[i];  // copia i caratteri fino a start
    }
    int j = i;
    for (; i <= end; i++);  // salta i caratteri compresi

    for (; s[i] != '\0'; i++) {  // copia i caratteri da end fino alla fine
        result[j] = s[i];
        j++;
    }
    result[j + 1] = '\0';  // aggiunge il fine stringa

    result = realloc(result, i - (end - start));
    return result;
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

    char *s = "Per me si va HELLO nella";
    char *res = strtrim(s, 13, 17);
    printf("%s\n", res);
}
