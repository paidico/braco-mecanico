#include "bloco.h"

Bloco *Bloco_create(int pos)
{
  Bloco *bl = calloc(1, sizeof(Bloco));
  bl->pos_original = pos;
  bl->pos_atual = pos;
  bl->valor = pos;

  return bl;
}

void Bloco_destroy(Bloco *bloco)
{
  free(bloco);
}
