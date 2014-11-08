#ifndef _fila_h
#define _fila_h

#include "lista.h"

typedef struct Fila 
{
  Lista *base;
} Fila;

/* Obtém tamanho da fila */
int Fila_size(Fila *fila);

Fila *Fila_create();

void Fila_destroy(Fila *fila);

void Fila_clear_destroy(Fila *fila);

/* "Espia" próximo elemento a sair da fila */
void *Fila_peek(Fila *fila);

/* Retira próximo elemento da fila (primeiro que entrou) */
void *Fila_dequeue(Fila *fila);

/* Enfileira valor */
void Fila_enqueue(Fila *fila, void *valor);

/* Determina se tamanho da fila é maior que zero */
int Fila_is_empty(Fila *fila);

void Fila_each(Fila *fila, funcao_each fe);

#endif
