# List
```c
struct listEl {
    int            info;
    struct listEl* next;
};
typedef struct listEl* list;
```
Le liste usano una funzione per l'**inserimento in testa** `Cons(int x, list l)`. Questa deve essere usata in tutti i metodi che richiedono di restituire una nuova lista calcolata sulla base delle liste passate come parametro.

Quando non si deve operare direttamente sulle liste, perchè viene chiesto che la funzione sia **non distruttiva**, si può usare la funzione fornita `copylist(list l)`

In generale le soluzioni possono essere:
- **RICORSIVE**: usano passo base e poi richiamano il metodo riducendo le dimensioni della lista grazie al next, oppure chiamano `Cons` per costruire la nuova lista.
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
```

### Funzioni ausiliarie utili
A volte sono fornite alcune funzioni ausiliarie, in altri problemi invece fanno parte della soluzione, quindi può essere utile ricordarle:

- [`copylist(list l)`](list.c#L45)  
- [`reverse(list l)`](list.c#L53)  
- [`concat(list a, list b)`](list.c#L62)  


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

### Alberi binari di ricerca
Un **albero binario di ricerca** è 

### Esempio di soluzione tipica
```c
int count_internals(btree b) {
    if (b == NULL || (b->left == NULL && b->right == NULL)) {
        return 0;
    }
    else {
       return 1 + count_internals(b->left) + count_internals(b->right); 
    }
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
Sono alberi k-ari rappresentati come binari, tramite i puntatori child e sibling. I metodi sono simili a quelli degli alberi binari, ma in alcuni casi bisogna fare ricorsione per ogni figlio quindi spesso serve ridefinire un albero child: `kTree c = t->child` e poi fare un ciclo `while(c != NULL)`

Un esempio di soluzione:
```c
int count_internals(kTree kt) {
    if (kt == NULL || kt->child == NULL) {
        return 0;
    }
    int sum = 1;
    kTree c = kt->child;
    while (c != NULL) {
        sum += count_internals(c);
        c = c->sibling;
    }
    return sum;
}
```

# Array
Le soluzioni sono **iterative** e consistono nello scorrere l'array tramite indici e applicare una  o più condizioni.
A volte possono usare una funzione di supporto `swap(A, i , j)` per scambiare due elementi nell'array (di solito fornita).

### Funzione ausiliaria swap
```c
void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
```

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