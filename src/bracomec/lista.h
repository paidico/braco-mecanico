#ifndef _lista_h
#define _lista_h

typedef void (*funcao_each)(void *a);
typedef int (*funcao_compare)(void *a, void *b);

struct Elo;

/* Definição de nó da lista */
typedef struct Elo {
  /* Lista base para demais estruturas (singly linked) */
  struct Elo *proximo;
  
  /* Valor passível de cast para qualquer tipo */
  void *valor;
} Elo;

typedef struct Lista {
  int tamanho;
  Elo *primeiro; /* Elo iniciador stub */
} Lista;

/* Retorna valor do primeiro elemento da lista */
void *Lista_primeiro(Lista *lista);

/* Retorna valor do último elemento da lista */
void *Lista_ultimo(Lista *lista);

/* Aloca heap memory para uma nova lista */
Lista *Lista_create();

/* Remove lista da memória */
void Lista_destroy(Lista *lista);

/* Remove lista e valores da lista da memória evitando segfaults*/
void Lista_clear_destroy(Lista *lista);

/* Retira elemento do final e retorna valor */
void *Lista_pop(Lista *lista);

/* Inclui elemento no final */
void Lista_push(Lista *lista, void *valor);

/* Retira elemento do começo e retorna valor */
void *Lista_shift(Lista *lista);

/* Inclui elemento no começo */
void Lista_unshift(Lista *lista, void *valor);

/* Remove nó específico e retorna seu valor */
void *Lista_remove(Lista *lista, void *valor, funcao_compare fc);

/* Executa função para todos itens */
void Lista_each(Lista *lista, funcao_each fe);

#endif
