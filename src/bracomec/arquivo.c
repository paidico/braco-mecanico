#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

int Arquivo_count_line(Arquivo *arquivo)
{
  return Lista_size(arquivo->linhas);
}

Arquivo *Arquivo_create()
{
  Arquivo *aq = calloc(1, sizeof(Arquivo));
  aq->linhas = Lista_create();

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
  int i = 0, n = Arquivo_count_line(arquivo);
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

int Arquivo_write_to(Arquivo *arquivo, char *saida)
{
  FILE *f = fopen(saida, "w");
  if(!f)
    {
      return 0;
    }
  Elo *el = arquivo->linhas->primeiro;
  while((el = el->proximo))
    {
      fputs(el->valor, f);
      fputs("\n", f);
    }

  return fclose(f) + 1;
}

int Arquivo_read_from(Arquivo *arquivo, char *entrada)
{
  FILE *f = fopen(entrada, "r");
  if(!f)
    {
      return 0;
    }
  int cont = MAX_ARQ_LIN_COL;
  char lin[cont];
  while(fgets(lin, MAX_ARQ_LIN_COL, f) && cont--)
    {
      /* Removendo new line */
      char *_lin = malloc(strlen(lin) + 1);
      strcpy(_lin, lin);
      _lin[strlen(_lin) - 1] = '\0';

      Lista_push(arquivo->linhas, _lin);
    }

  return fclose(f) + 1;
}

void Arquivo_append_line(Arquivo *arquivo, char *linha)
{
  if(linha)
    {
      char *_lin = malloc(strlen(linha) + 1);
      strcpy(_lin, linha);

      Lista_push(arquivo->linhas, _lin);
    }
}
