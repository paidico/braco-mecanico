#include <stdlib.h>

#include "pilha.h"

int generic_comparer(Pilha *pl, void *vl, funcao_compare fc, char acao)
{
  if(Pilha_is_empty(pl))
    {
      return 0;
    }
  Elo *el = pl->base->primeiro;
  while((el = el->proximo))
    {
      switch(acao)
	{
	case 'L':
	  if(fc(el->valor, vl) < 0)
	    {
	      return 1;
	    }
	  break;
	case 'G':
	  if(fc(el->valor, vl) > 0)
	    {
	      return 1;
	    }
	  break;
	case 'E':
	  if(fc(el->valor, vl) == 0)
	    {
	      return 1;
	    }
	  break;
	default:
	  return 0;
	}
    }

  return 0;
}

int Pilha_size(Pilha *pilha)
{
  return Lista_size(pilha->base);
}

Pilha *Pilha_create()
{
  Pilha *pl = calloc(1, sizeof(Pilha));
  pl->base = Lista_create();

  return pl;
}

void Pilha_destroy(Pilha *pilha)
{
  Lista_destroy(pilha->base);
  free(pilha);
}

void Pilha_clear_destroy(Pilha *pilha)
{
  Lista_clear_destroy(pilha->base);
  free(pilha);
}

void *Pilha_stacktop(Pilha *pilha)
{
  return Lista_first(pilha->base);
}

void *Pilha_pop(Pilha *pilha)
{
  return Lista_shift(pilha->base);
}

void Pilha_push(Pilha *pilha, void *valor)
{
  Lista_unshift(pilha->base, valor);
}

void *Pilha_pop_to(Pilha *pilha_origem, Pilha *pilha_destino)
{
  void *el = Pilha_pop(pilha_origem);
  Pilha_push(pilha_destino, el);
  return el;
}

int Pilha_is_empty(Pilha *pilha)
{
  return Lista_size(pilha->base) == 0;
}

void Pilha_each(Pilha *pilha, funcao_each fe)
{
  Lista_each(pilha->base, fe);
}

int Pilha_has_lesser(Pilha *pilha, void *valor, funcao_compare fc)
{
  return generic_comparer(pilha, valor, fc, 'L');
}
int Pilha_has_greater(Pilha *pilha, void *valor, funcao_compare fc)
{
  return generic_comparer(pilha, valor, fc, 'G');
}
int Pilha_has_equal(Pilha *pilha, void *valor, funcao_compare fc)
{
  return generic_comparer(pilha, valor, fc, 'E');
}

