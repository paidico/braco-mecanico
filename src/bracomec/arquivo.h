#ifndef _arquivo_h
#define _arquivo_h

#define MAX_ARQ_LIN_COL 10000

#include "lista.h"

typedef struct Arquivo
{
  char *nome;
  Lista *linhas;
} Arquivo;

int Arquivo_count_line(Arquivo *arquivo);

/* Aloca Arquivo na memória e lê linhas se houver */
Arquivo *Arquivo_create(char *nome);

void Arquivo_destroy(Arquivo *arquivo);

void Arquivo_each_line(Arquivo *arquivo, funcao_each fe);

char *Arquivo_get_line(Arquivo *arquivo, int indice);

/* Escreve conteúdo das linhas do arquivo */
void Arquivo_write(Arquivo *arquivo)

#endif
