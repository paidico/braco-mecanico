#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "braco.h"

int compare_stack_int(void *a, void *b)
{
  return (int)a - (int)b;
}

int validate_exec_a_b(Braco *br, int a, int b)
{
  if(a == b)
    {
      return 0;
    }
  int i, controle = 0;
  for(i = 0; i < br->n; i++)
    {
      controle = Pilha_has_equal(br->posicoes[i], &a, compare_stack_int);
      controle += Pilha_has_equal(br->posicoes[i], &b, compare_stack_int);
      if(controle == 1) 
	{
	  return 1;
	}
      else if(controle == 2)
	{
	  return 0;
	}
    }
  /* Situação improvável de não existir nenhum dos valores na pilha de posições */
  return 0;
}

int get_block_position(Pilha **posicoes, int bloco)
{
  int cont = 0;
  while(!Pilha_has_equal(posicoes[cont], &bloco, compare_stack_int))
    {
      cont++;
    }
  return cont;
}

void clear_blocks_from_top(Pilha **posicoes, int bloco, int pilha_origem)
{
  int aux;
  while((aux = *(int *)Pilha_stacktop(posicoes[pilha_origem])) != bloco)
    {
      clear_blocks_from_top(posicoes, aux, pilha_origem);
    }
}

exec_status move_a_over_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, a, i_a);
  clear_blocks_from_top(br->posicoes, b, i_b);
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));

  return OK;
}
exec_status move_a_top_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, a, i_a);
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));

  return OK;
}
exec_status stack_a_over_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, b, i_b);
  while(*(int *)Pilha_stacktop(br->posicoes[i_a]) != a)
    {
      Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
    }
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
  return OK;
}
exec_status stack_a_top_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  while(*(int *)Pilha_stacktop(br->posicoes[i_a]) != a)
    {
      Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
    }
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
  return OK;
}
/* Argumentos apenas para uso de ponteiro */
exec_status find_greatest(Braco *br, int a, int b)
{
  return EXIT;
}
/* Argumentos apenas para uso de ponteiro */
exec_status process_exit(Braco *br, int a, int b)
{
  return EXIT;
}

Braco *Braco_create(Arquivo *arquivo)
{
  int i, n_instr, n_bloco = atoi(Arquivo_get_line(arquivo, 0));
  if(n_bloco <= 0 || n_bloco > MAX_BLOCO)
    {
      return NULL;
    }
  Braco *br = calloc(1, sizeof(Braco));
  br->auxiliar = Pilha_create();
  br->n = n_bloco;
  for(i = 0; i < n_bloco; i++)
    {
      Pilha *pl = Pilha_create();
      int j = i;
      Pilha_push(pl, &j);
      br->posicoes[i] = pl;
    }

  br->instrucoes = Fila_create();
  n_instr = Arquivo_count_line(arquivo) - 1;
  for(i = 0; i < n_instr; i++)
    {
      int aux_a = -1, aux_b =
      funcao_exec _f;
      Bloco *_a = NULL, *_b = NULL;
      char _aux[10], *lin = Arquivo_get_line(arquivo, i + 1);
      switch(lin[0])
	{
	case 'm':
	  sscanf(lin, "%*s %d %s %d", &_a, _aux, &_b);
	  if(_aux[0] == 'a')
	    {
	      _f = move_a_over_b;
	      break;
	    }
	  _f = move_a_top_b;
	  break;
	case 'e':
	  if(lin[1] == 'm')
	    {
	      sscanf(lin, "%*s %d %s %d", &_a, _aux, &_b);
	      if(_aux[0] == 'a')
		{
		  _f = stack_a_over_b;
		  break;
		}
	      _f = stack_a_top_b;	    
	      break;
	    }
	  _f = find_greatest;
	  break;
	default:
	  _f = process_exit;
	}
      Braco_add_instruction(br, Execucao_create(_a, _b, _f));
    }

  return br;
}
void Braco_process_start(Braco *braco)
{
  char *status_descr[] = { 
    "Instrução executada com sucesso.", 
    "Instrução ilegal ignorada.", 
    "Instrução de saída." 
  };
  exec_status es = OK;
  int i = 0;
  printf("Iniciando processamento:\n");
  while(es != EXIT && !Fila_is_empty(braco->instrucoes))
    {
      Execucao *ex = Fila_dequeue(braco->instrucoes);
      es = Execucao_process(ex, braco->n, braco->posicoes);
      printf("::: %2d ::: %s\n", ++i, status_descr[es]);
    }
  printf("Fim do processamento.\n");
}

int Braco_write(Braco *braco, Arquivo *arquivo)
{
  char aux[MAX_ARQ_LIN_COL], aux2[MAX_ARQ_LIN_COL], *saida = "arquivo_saida.txt";
  int i;
  for(i = 0; i < braco->n; i++)
    {
      sprintf(aux, "%d:", i);
      while(!Pilha_is_empty(braco->posicoes[i]))
	{
	  Pilha_push(braco->auxiliar, Pilha_pop(braco->posicoes[i]));
	}
      while(!Pilha_is_empty(braco->auxiliar))
	{
	  sprintf(aux2, " %d", *(int *)Pilha_pop(braco->auxiliar));
	  strcat(aux, aux2);
	}
      Arquivo_append_line(arquivo, aux);
    }

  return Arquivo_write_to(arquivo, saida);
}

void Braco_add_instruction(Braco *braco, Execucao *execucao)
{
  Fila_enqueue(braco->instrucoes, execucao);
}

void Braco_destroy(Braco *braco)
{
  int i;
  for(i = 0; i < braco->n; i++)
    {
      Pilha_destroy(braco->posicoes[i]);
    }
  Pilha_destroy(braco->auxiliar);
  Fila_clear_destroy(braco->instrucoes);

  free(braco);
}
