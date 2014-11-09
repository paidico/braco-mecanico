#ifndef _execucao_h
#define _execucao_h

#include "bloco.h"
#include "pilha.h"

typedef enum { OK, IGNORED, EXIT } exec_status;

typedef exec_status (*funcao_exec)(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b);

typedef struct Execucao
{
  Bloco *a;
  Bloco *b;
  funcao_exec fx;
} Execucao;

Execucao *Execucao_create(Bloco *a, Bloco *b, funcao_exec fx);
exec_status Execucao_process(Execucao *execucao, int n, Pilha **esteira);
void Execucao_destroy(Execucao *execucao);

#endif
