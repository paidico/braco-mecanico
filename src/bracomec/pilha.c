#include <stdlib.h>

#include "pilha.h"

int Pilha_size(Pilha *pilha)
{
  return Lista_size(pilha->base);
}

Pilha *Pilha_create()
{
  Pilha *pl = calloc(1, sizeof(Pilha));
  pl->base = Lista_create();

  return pl;
}

void Pilha_destroy(Pilha *pilha)
{
  Lista_destroy(pilha->base);
  free(pilha);
}

void Pilha_clear_destroy(Pilha *pilha)
{
  Lista_clear_destroy(pilha->base);
  free(pilha);
}

void *Pilha_stacktop(Pilha *pilha)
{
  return Lista_first(pilha->base);
}

void *Pilha_pop(Pilha *pilha)
{
  return Lista_shift(pilha->base);
}

void Pilha_push(Pilha *pilha, void *valor)
{
  Lista_unshift(pilha->base, valor);
}

void Pilha_each(Pilha *pilha, funcao_each fe)
{
  Lista_each(pilha->base, fe);
}
