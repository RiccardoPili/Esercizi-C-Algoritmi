# List
```c
struct listEl {
    int            info;
    struct listEl* next;
};
typedef struct listEl* list;
```
Le liste usano una funzione per l'**inserimento in testa** `Cons(int x, list l)`. Questa deve essere usata in tutti le funzioni che richiedono di restituire una nuova lista calcolata sulla base delle liste passate come parametro.

Quando non si deve operare direttamente sulle liste, perchè viene chiesto che la funzione sia **non distruttiva**, si può usare la funzione fornita `copylist(list l)`

In generale le soluzioni possono essere:
- **RICORSIVE**: usano passo base e poi richiamano la funzione riducendo le dimensioni della lista grazie al next, oppure chiamano `Cons` per costruire la nuova lista.
- **ITERATIVE**: usare un ciclo `while(l != NULL)` o `while(l->next != NULL)` e per iterare la lista con `l = l->next`. Alla fine del ciclo devono restituire la lista costruita o il valore calcolato.

### Esempio di soluzione ricorsiva
```c
list intersect(list l, list m){
    if(l == NULL || m == NULL) return NULL;
    if(l->info == m->info){
        return Cons(l->info, intersect(l->next, m->next));
    }
    else if(l->info < m->info){
        return intersect(l->next, m);
    }
    else {
        return intersect(l, m->next);
    }
}
```

### Esempio di soluzione iterativa
```c
bool palindrome_no_reverse(list l) {
    list rev = NULL;
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
```

### Funzioni ausiliarie utili
A volte sono fornite alcune funzioni ausiliarie, in altri problemi invece fanno parte della soluzione, quindi può essere utile ricordarle:
- [`copylist(list l)`](list.c#L44)
- [`reverse(list l)`](list.c#L52)
- [`concat(list a, list b)`](list.c#L61)


# B-Tree
```c
struct BtreeNd {
    int             key;
    struct BtreeNd* left;
    struct BtreeNd* right;
};
typedef struct BtreeNd* btree;
```
Gli alberi binari sono rappresentati con un nodo i cui campi sono un intero `key`, e due puntatori ai sottoalberi sinistro `left` e destro `right`. La maggior parte delle soluzioni sono **ricorsive** e si basano sul ricongiungersi al passo base secondo una condizione di `b` `b->left` e `b->right` e poi quando viene chiamato il passo ricorsivo viene chiamato sui figli sinistro e destro.

Può essere utile utilizzare la funzione [`ConsTree(int k, btree l, btree r)`](bTree.c#L33) usata solo per l'inserimento o aggiunta di qualche nodo all'albero, come avviene nella funzione  [`insert(int x, btree bt)`](bTree.c#L152)

### Alberi binari di ricerca
Un **albero binario di ricerca** è un albero binario "ordinato" secondo certe proprietà:
- il nodo left < parent
- il nodo right > parent
- i nodi sono univoci (non possono esserci duplicati)

(Ovviamente i sottoalberi sinistro e destro devono essere a loro volta alberi binari di ricerca)

### Esempio di soluzione tipica
```c
int sum_leaf(btree b) {
    if (b == NULL) {
        return 0;
    }
    if (b->left == NULL && b->right == NULL) {
        return b->key;
    }
    return sum_leaf(b->left) + sum_leaf(b->right);
}
```


# K-Tree
```c
struct kTreeVertex {
    int                  key;
    struct kTreeVertex*  child;
    struct kTreeVertex*  sibling;
};
typedef struct kTreeVertex* kTree;
```
Sono **alberi k-ari rappresentati come binari**, tramite i puntatori `child` e `sibling`. Le funzioni sono simili a quelli degli alberi binari, ma in alcuni casi bisogna fare **ricorsione per ogni figlio** quindi spesso serve ridefinire un albero child: `kTree c = t->child` e poi fare un ciclo `while(c != NULL)`. Le funzioni sono simili tra loro, quello che cambia sono i passi base, i valori restituiti e le operazioni all'interno del ciclo while. A volte possono usare le funzioni ausiliarie `min` e `max`.

### Esempio di soluzione
```c
int maxSumBranch(kTree t) {
    if (t->child == NULL) {
        return t->key;
    }
    int maxSum = 0;
    kTree c = t->child;
    while (c != NULL) {
        int sum = maxSumBranch(c);
        maxSum = max(maxSum, sum);
        c = c->sibling;
    }
    return t->key + maxSum;
}
```

# Array
Le soluzioni sono **iterative** e consistono nello scorrere l'array tramite indici e applicare una  o più condizioni.
A volte possono usare una funzione di supporto `swap(A, i , j)` per scambiare due elementi nell'array (di solito fornita).

In alcuni problemi è utile ricordarsi, o usare se fornita, la funzione ausiliaria swap:
- [`swap(int A[], int i, int j)`](array.c#L9) 


### Esempio di soluzione
```c
int maxDecSeq(int A[], int n){
    if(n == 0) return 0;

    int maxLen = 1;
    int currentLen = 1;

    for(int i = 1; i < n; i++){
        if(A[i-1] > A[i]){
            currentLen++;
        }
        else{
            if(currentLen > maxLen){
                maxLen = currentLen;
            }
            currentLen = 1;
        }
    }

    if(currentLen > maxLen){
        maxLen = currentLen;
    }

    return maxLen;
}
```

# Heap
Un heap è un albero binario rappresentato tramite un array H con le seguenti proprietà:
- H[0] = elemento fittizio (null)
- H[1] = radice dell'albero
- figlio Sx = parent * 2
- figlio Dx = parent * 2 + 1

### Inserimento
La funzione **Insert** inserisce un nuovo elemento in un min-heap rappresentato come array. L'inserimento avviene in fondo all'array e poi il nuovo elemento viene fatto "risalire" confrontandolo col genitore. Se è più piccolo, viene scambiato, mantenendo così la proprietà del min-heap. Il processo continua fino a che l'elemento trova la sua posizione corretta.
```c
void Insert(int h[], int* size, int x) {
    (*size)++;              // Incrementa la dimensione dell'heap (aggiunge un nodo)
    h[*size] = x;           // Inserisce il nuovo elemento x in fondo all'heap

    int i = *size;          // Salva l'indice dell'elemento appena inserito
    while (i > 1 && h[i/2] > h[i]) { // Finché il nodo ha un genitore e il genitore è maggiore
        swap(h, i, i/2);    // Scambia il nodo con il suo genitore
        i = i / 2;          // Aggiorna l'indice per risalire l'heap
    }
}
```

### Estrazione del minimo
La funzione **ExtractMin** rimuove il minimo da un min-heap, che si trova sempre nella radice (cioè h[1]). Per mantenere la struttura dell’albero completo, l’ultimo elemento viene spostato alla radice. Successivamente, si chiama MinHeapify per ripristinare la proprietà del min-heap a partire dalla radice. La funzione restituisce il valore minimo estratto.
```c
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
```

### Ricostruzione
La funzione **MinHeapify** ristabilisce la proprietà del min-heap a partire da un nodo interno dell'albero (rappresentato in un array). Considera l'elemento in posizione i e confronta il suo valore con quello dei suoi figli sinistro e destro. Se uno dei figli ha un valore più piccolo, scambia il nodo corrente con il figlio minore. Dopo lo scambio, può darsi che il sottoalbero modificato non rispetti più la proprietà di min-heap, quindi la funzione richiama sé stessa ricorsivamente sul figlio scambiato. Questo processo continua finché l'elemento trova la posizione corretta, garantendo che il sottoalbero radicato in i diventi un min-heap valido.
```c
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
```