# List
```
struct listEl {
    int            info;
    struct listEl* next;
};
```
Le liste usano una funzione per l'inserimento in testa `Cons(int x, list l)`. Questa deve essere usata in tutti i metodi che richiedono di restituire una nuova lista calcolata sulla base delle liste passate come parametro.

Quando non si deve operare direttamente sulle liste si può usare la funzione fornita `copylist(list l)`

Le soluzioni possono essere:
- RICORSIVE: usano passo base e poi richiamano il metodo riducendo le dimensioni della lista, oppure chiamano `Cons` per costruire la nuova lista
- ITERATIVE: usare un ciclo `while(l != NULL)` o `while(l->next != NULL)` e per iterare ad esempio con `l = l->next`

Un esempio di soluzione tipica:
```
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

# B-Tree
```
struct BtreeNd {
    int             key;
    struct BtreeNd* left;
    struct BtreeNd* right;
};
```
La maggior parte delle soluzioni sono ricorsive e si basano sull'applicare il passo base secondo una condizione di `b` `b->left` e `b->right` e poi quando viene chiamato il passo ricorsivo viene chiamato sui figli sinistro e destro.

Un esempio di soluzione tipica:
```
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
```
struct kTreeVertex {
    int                  key;
    struct kTreeVertex*  child;
    struct kTreeVertex*  sibling;
};
```
Sono alberi k-ari rappresentati come binari, tramite i puntatori child e sibling. I metodi sono simili a quelli degli alberi binari, ma in alcuni casi bisogna fare ricorsione per ogni figlio quindi spesso serve ridefinire un albero child: `kTree c = t->child` e poi fare un ciclo `while(c != NULL)`

Un esempio di soluzione:
```
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
Le soluzioni sono iterative e consistono nello scorrere l'array tramite indici e applicare una condizione.
A volte possono usare una funzione di supporto `swap(A, i , j)` per scambiare due elementi nell'array.

Un esempio di soluzione:
```
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