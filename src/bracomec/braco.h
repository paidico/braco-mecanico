#ifndef _braco_h
#define _braco_h

#define MAX_BLOCO 25

#include "pilha.h"
#include "fila.h"
#include "arquivo.h"

typedef enum { OK, IGNORED, EXIT } exec_status;

typedef exec_status (*funcao_exec)(int a, int b);

typedef struct Execucao
{
  int a;
  int b;
  funcao_exec fx;
} Execucao;

typedef struct Braco
{
  int n;
  Pilha *posicoes[MAX_BLOCO];
  Pilha *auxiliar;
  Fila *instrucoes;
} Braco;

Braco *Braco_create(Arquivo *arquivo);
void Braco_process_start(Braco *braco);
int Braco_write(Braco *braco, Arquivo *arquivo);
void Braco_destroy(Braco *braco);

#endif
