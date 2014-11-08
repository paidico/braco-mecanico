#include <stdlib.h>
#include <stdio.h>

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
  for(i = 0; i < br.n; i++)
    {
      controle = Pilha_has_equal(br->posicoes[i], a, compare_stack_int);
      controle += Pilha_has_equal(br->posicoes[i], b, compare_stack_int);
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
  while(!Pilha_has_equal(br->posicoes[cont], bloco, compare_stack_int))
    {
      cont++;
    }
  return cont;
}

void clear_blocks_from_top(Pilha **posicoes, int bloco, int pilha_origem)
{
  int aux;
  while((aux = Pilha_stacktop(posicoes[pilha_origem])) != bloco)
    {
      clear_blocks_from_top(posicoes[pilha_origem], aux, pilha_origem);
    }
}

exec_status move_a_over_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return exec_status.IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, a, i_a);
  clear_blocks_from_top(br->posicoes, b, i_b);
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
}
exec_status move_a_top_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return exec_status.IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, a, i_a);
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
}
exec_status stack_a_over_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return exec_status.IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  clear_blocks_from_top(br->posicoes, b, i_b);
  while(Pilha_stacktop(br->posicoes[i_a]) != a)
    {
      Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
    }
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
}
exec_status stack_a_top_b(Braco *br, int a, int b)
{
  if(!validate_exec_a_b(br, a, b))
    {
      return exec_status.IGNORED;
    }
  int i_a = get_block_position(br->posicoes,  a);
  int i_b = get_block_position(br->posicoes,  b);
  while(Pilha_stacktop(br->posicoes[i_a]) != a)
    {
      Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
    }
  Pilha_push(br->posicoes[i_b], Pilha_pop(br->posicoes[i_a]));
}
/* Argumentos apenas para uso de ponteiro */
exec_status find_greatest(Braco *br, int a, int b)
{

}
/* Argumentos apenas para uso de ponteiro */
exec_status process_exit(Braco *br, int a, int b)
{
  return exec_status.EXIT;
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
  br.n = n_bloco;
  for(i = 0; i < n_bloco; i++)
    {
      Pilha *pl = Pilha_create();
      Pilha_push(pl, i);
      br->posicoes[i] = pl;
    }

  br->instrucoes = Fila_create();
  n_instr = Arquivo_count_line(arquivo) - 1;
  for(i = 0; i < n_instr; i++)
    {
      funcao_exec _f;
      int _a = -1, _b = -1;
      char _aux[10], *lin = Arquivo_get_line(arquivo, i + 1);
      swtich(lin[0])
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
      Execucao ex = {
	.a = _a;
	.b = _b;
	.fx = _f;
      };
      Fila_enqueue(br->instrucoes, ex);
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
  exec_status es = exec_status.OK;
  int i = 0;
  printf("Iniciando processamento:\n");
  while(es != exec_status.EXIT && !Fila_is_empty(braco->instrucoes))
    {
      Execucao ex = Fila_dequeue(braco->instrucoes);
      es = ex.fx(braco, ex.a, ex.b);
      printf("::: %d ) ::: %s :::\n", ++i, status_descr[es]);
    }
  printf("Fim do processamento.\n");
}

int Braco_write(Braco *braco, Arquivo *arquivo)
{
  char aux[MAX_ARQ_LIN_COL], *saida = "arquivo_saida.txt";
  int i;
  for(i = 0; i < braco.n; i++)
    {
      sprintf(aux, "%d:", i);
      while(!Pilha_is_empty(braco->posicoes[i]))
	{
	  Pilha_enqueue(braco->auxiliar, Pilha_dequeue(braco->posicoes[i]));
	}
      while(!Pilha_is_empty(braco->auxiliar))
	{
	  strcat(aux, sprintf(aux, " %d", Pilha_dequeue(braco->auxiliar)));
	}
      Arquivo_append_line(arquivo, aux);
    }

  return Arquivo_write_to(arquivo, saida);
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
