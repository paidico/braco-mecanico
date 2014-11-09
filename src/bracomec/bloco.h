#ifndef _bloco_h
#define _bloco_h

typedef struct Bloco
{
  int pos_original;
  int pos_atual;
  int valor;
} Bloco;

Bloco *Bloco_create(int pos);
void Bloco_destroy(Bloco *bloco);

#endif
