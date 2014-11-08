#ifndef _arquivo_h
#define _arquivo_h

#define MAX_ARQ_LIN_COL 999

#include "lista.h"

/* Tipo para armazenar linhas de arquivo de texto */
typedef struct Arquivo
{
  Lista *linhas;
} Arquivo;

int Arquivo_count_line(Arquivo *arquivo);

/* Aloca Arquivo na memória e lê linhas se houver */
Arquivo *Arquivo_create();

void Arquivo_destroy(Arquivo *arquivo);

void Arquivo_each_line(Arquivo *arquivo, funcao_each fe);

/* Retorna valor linha com índice informado (zero based) */
char *Arquivo_get_line(Arquivo *arquivo, int indice);

/* Escreve linhas de Arquivo e retorna status da operação */
int Arquivo_write_to(Arquivo *arquivo, char *saida);

/* Lê linhas para Arquivo e retorna status da operação */
int Arquivo_read_from(Arquivo *arquivo, char *entrada);

/* Adiciona nova linha ao arquivo */
void Arquivo_append_line(Arquivo *arquivo, char *linha);

#endif
