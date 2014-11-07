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

void Pilha_each(Pilha *pilha, funcao_each fe);

#endif
