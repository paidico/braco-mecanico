#include <stdlib.h>

#include "execucao.h"

Execucao *Execucao_create(Bloco *a, Bloco *b, funcao_exec fx, char *tx)
{
  Execucao *ex = calloc(1, sizeof(Execucao));
  ex->a = a;
  ex->b = b;
  ex->fx = fx;
  ex->texto = tx;

  return ex;
}

exec_status Execucao_process(Execucao *execucao, int n, Pilha **esteira)
{
  return execucao->fx(n, esteira, execucao->a, execucao->b);
}

void Execucao_destroy(Execucao *execucao)
{
  Bloco_destroy(execucao->a);
  Bloco_destroy(execucao->b);

  free(execucao);
}
