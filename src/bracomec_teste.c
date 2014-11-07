#include <stdio.h>
#include <string.h>

#include "lista.h"

void imprime(void *nome)
{
  printf("|| %s\n", (char *)nome);
}

int compara(void *a, void *b)
{
  return strcmp((char *)a, (char *)b);
}

int main(int argc, char *argv[])
{
  /* Teste de implementação */

  Lista *ls = Lista_create();
  Lista_push(ls, "Adriano");
  Lista_push(ls, "Pedro");
  Lista_push(ls, "dos");
  Lista_push(ls, "Santos");
  Lista_each(ls, imprime);
  printf("total: %d\n", ls->tamanho);
  imprime(Lista_primeiro(ls));
  imprime(Lista_ultimo(ls));
  printf("##########################\n");
  const char *wiped;
  int n = 0;
  while((wiped = Lista_pop(ls)))
    {
      printf("pop_%d:\t%s\n--------------------------\n", ++n, wiped);
      Lista_each(ls, imprime);
      printf("--------------------------\ntotal: %d\n", ls->tamanho);
    }
  Lista_push(ls, "Cícera");
  Lista_push(ls, "Pimenta");
  Lista_each(ls, imprime);
  printf("total: %d\n", ls->tamanho);
  n = 0;
  while((wiped = Lista_shift(ls)))
    {
      printf("shifted_%d:\t%s\n--------------------------\n", ++n, wiped);
      Lista_each(ls, imprime);
      printf("--------------------------\ntotal: %d\n", ls->tamanho);
    }
  n = argc;
  while(--n > 0)
    {
      Lista_unshift(ls, argv[n]);
    }
  Lista_each(ls, imprime);
  printf("total: %d\n", ls->tamanho);
  Lista_pop(ls);
  Lista_each(ls, imprime);
  printf("total: %d\n", ls->tamanho);

  imprime(Lista_remove(ls, "Pimenta", compara);
  printf("total: %d\n", ls->tamanho);
  Lista_destroy(ls);
  return 0;
}
