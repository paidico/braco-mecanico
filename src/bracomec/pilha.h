#ifndef _pilha_h
#define _pilha_h

#include "lista.h"

typedef struct Pilha 
{
  Lista *base;
} Pilha;

int Pilha_size(Pilha *pilha);

Pilha *Pilha_create();

void Pilha_destroy(Pilha *pilha);

void Pilha_clear_destroy(Pilha *pilha);

/* Pega elemento do topo sem removê-lo da pilha */
void *Pilha_stacktop(Pilha *pilha);

/* Remove elemento do topo */
void *Pilha_pop(Pilha *pilha);

/* Insere elemento no topo */
void Pilha_push(Pilha *pilha, void *valor);

int Pilha_is_empty(Pilha *pilha);

void Pilha_each(Pilha *pilha, funcao_each fe);

int Pilha_has_lesser(Pilha *pilha, void *valor, funcao_compare fc);
int Pilha_has_greater(Pilha *pilha, void *valor, funcao_compare fc);
int Pilha_has_equal(Pilha *pilha, void *valor, funcao_compare fc);

#endif
