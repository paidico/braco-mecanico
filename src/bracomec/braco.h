#ifndef _braco_h
#define _braco_h

#define MAX_BLOCO 25

#include "execucao.h"
#include "pilha.h"
#include "fila.h"
#include "arquivo.h"


typedef struct Braco
{
  int n;
  Bloco *blocos[MAX_BLOCO];
  Pilha *posicoes[MAX_BLOCO];
  Pilha *auxiliar;
  Fila *instrucoes;
} Braco;

Braco *Braco_create(Arquivo *arquivo);
void Braco_add_instruction(Braco *braco, Execucao *execucao);
void Braco_process_start(Braco *braco);
int Braco_write(Braco *braco, Arquivo *arquivo);
void Braco_destroy(Braco *braco);

#endif
