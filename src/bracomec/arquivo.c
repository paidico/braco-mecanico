#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

int Arquivo_count_line(Arquivo *arquivo)
{
  return Lista_size(arquivo->linhas);
}

Arquivo *Arquivo_create(char *nome)
{
  FILE *f = fopen(nome, "a+");
  if(!f)
    {
      return NULL;
    }
  Arquivo *aq = calloc(1, sizeof(Arquivo));
  aq->nome = nome;
  aq->linhas = Lista_create();
  int cont = MAX_ARQ_LIN_COL;
  char lin[cont];
  while(fgets(lin, MAX_ARQ_LIN_COL, f) && cont--)
    {
      /* Removendo \n */
      char *_lin = malloc(strlen(lin ? lin : "\n"));
      strcpy(_lin, lin);
      _lin[strlen(_lin)-1] = '\0';

      Lista_push(aq->linhas, _lin);
    }
  fclose(f);

  return aq;
}

void Arquivo_destroy(Arquivo *arquivo)
{
  Lista_clear_destroy(arquivo->linhas);
  free(arquivo);
}

void Arquivo_each_line(Arquivo *arquivo, funcao_each fe)
{
  Lista_each(arquivo->linhas, fe);
}

char *Arquivo_get_line(Arquivo *arquivo, int indice)
{
  int i = 0;
  int n = Arquivo_count_line(arquivo);
  Elo *el = arquivo->linhas->primeiro;
  if(indice < 0 || indice >= n)
    {
      return NULL;
    }
  while(i <= indice && i++ < n)
    {
      el = el->proximo;
    }

  return el->valor;
}

void Arquivo_write(Arquivo *arquivo)
{
  /* A implementar  */
}
