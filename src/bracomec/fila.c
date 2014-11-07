#include <stdlib.h>

#include "fila.h"

int Fila_size(Fila *fila)
{
  return Lista_size(fila->base);
}

Fila *Fila_create()
{
  Fila *fl = calloc(1, sizeof(Fila));
  fl->base = Lista_create();

  return fl;
}

void Fila_destroy(Fila *fila)
{
  Lista_destroy(fila->base);
  free(fila);
}

void Fila_clear_destroy(Fila *fila)
{
  Lista_clear_destroy(fila->base);
  free(fila);
}

void *Fila_peek(Fila *fila)
{
  /* Próximo da fila */
  return Lista_first(fila->base);
}

void *Fila_dequeue(Fila *fila)
{
  return Lista_shift(fila->base);
}

void Fila_enqueue(Fila *fila, void *valor)
{
  Lista_push(fila->base, valor);
}

void Fila_each(Fila *fila, funcao_each fe)
{
  Lista_each(fila->base, fe);
}
