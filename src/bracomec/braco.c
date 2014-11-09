#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "braco.h"

int compare_block_stack(void *a, void *b)
{
  return ((Bloco *)a)->valor - ((Bloco *)b)->valor;
}

int validate_exec_a_b(int n, Pilha **esteira, Bloco *a, Bloco *b)
{
  if(a->valor == b->valor)
    {
      return 0;
    }
  int i, controle = 0;
  for(i = 0; i < n; i++)
    {
      controle = Pilha_has_equal(esteira[i], a, compare_block_stack);
      controle += Pilha_has_equal(esteira[i], b, compare_block_stack);
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

void move_block_from_to(Pilha **esteira, Bloco *bloco, int destino)
{
  if(bloco)
    {
      bloco->pos_atual = destino;
      Pilha_push(esteira[destino], bloco);
    }
}

void clear_blocks_from_top(Pilha **esteira, Bloco *bloco, int destino)
{
  Bloco *aux = Pilha_pop(esteira[bloco->pos_atual]);
  aux = aux != NULL ? aux : bloco;
  char f_nome[30];
  sprintf(f_nome, "debug_%d_%d.log", bloco->valor, aux->valor);
  FILE *f = fopen(f_nome, "w");
  fprintf(f, "---> b: %d\taux: %d | %d\n", bloco->valor, aux->valor, destino);
  fclose(f);
  while(aux->valor != bloco->valor)
    {
      clear_blocks_from_top(esteira, aux, aux->pos_original);
    }

  move_block_from_to(esteira, aux, destino);    
}

exec_status move_a_over_b(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
{
  if(!validate_exec_a_b(n_esteira, esteira, a, b))
    {
      return IGNORED;
    }
  int destino = b->pos_atual;
  clear_blocks_from_top(esteira, b, destino);
  clear_blocks_from_top(esteira, a, destino);

  return OK;
}
exec_status move_a_top_b(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
{
  if(!validate_exec_a_b(n_esteira, esteira, a, b))
    {
      return IGNORED;
    }
  int destino = b->pos_atual;
  clear_blocks_from_top(esteira, a, destino);

  return OK;
}

exec_status stack_a_over_b(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
{
  if(!validate_exec_a_b(n_esteira, esteira, a, b))
    {
      return IGNORED;
    }
  int destino = b->pos_atual;
  clear_blocks_from_top(esteira, b, destino);

  Bloco *bl;
  do
    {
      bl = Pilha_pop(esteira[a->pos_atual]);
      move_block_from_to(esteira, bl, destino);
    } while(bl->valor != a->valor);

  return OK;
}
exec_status stack_a_top_b(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
{
  if(!validate_exec_a_b(n_esteira, esteira, a, b))
    {
      return IGNORED;
    }
  int destino = b->pos_atual;
  Bloco *bl;
  do
    {
      bl = Pilha_pop(esteira[a->pos_atual]);
      move_block_from_to(esteira, bl, destino);
    } while(bl->valor != a->valor);

  return OK;
}
/* Argumentos apenas para uso de ponteiro */
exec_status find_greatest(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
{
  return EXIT;
}
/* Argumentos apenas para uso de ponteiro */
exec_status process_exit(int n_esteira, Pilha **esteira, Bloco *a, Bloco *b)
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
      Bloco *bl = Bloco_create(i);
      Pilha *pl = Pilha_create();
      br->blocos[i] = bl;
      Pilha_push(pl, bl);
      br->posicoes[i] = pl;
    }

  br->instrucoes = Fila_create();
  n_instr = Arquivo_count_line(arquivo) - 1;
  for(i = 0; i < n_instr; i++)
    {
      int aux_a = -1, aux_b = -1;
      funcao_exec _f;
      Bloco *_a = NULL, *_b = NULL;
      char _aux[10], *lin = Arquivo_get_line(arquivo, i + 1);
      switch(lin[0])
	{
	case 'm':
	  sscanf(lin, "%*s %d %s %d", &aux_a, _aux, &aux_b);
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
	      sscanf(lin, "%*s %d %s %d", &aux_a, _aux, &aux_b);
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

      _a = aux_a > -1 && aux_a < br->n ? br->blocos[aux_a] : NULL;
      _b = aux_b > -1 && aux_b < br->n ? br->blocos[aux_b] : NULL;

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
  char aux[MAX_ARQ_LIN_COL], aux2[MAX_ARQ_LIN_COL], *saida = "out.txt";
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
