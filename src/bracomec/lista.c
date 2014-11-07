#include <stdlib.h>

#include "lista.h"

void *Lista_primeiro(Lista *lista)
{
  return lista->primeiro->proximo == NULL ? NULL : lista->primeiro->proximo->valor;
}

void *Lista_ultimo(Lista *lista)
{
  Elo *el = lista->primeiro->proximo;
  Elo *_atual = NULL;
  do
    {
      _atual = el;
    } while((el = (el == NULL ? NULL : el->proximo)) != NULL);

  return _atual == NULL ? NULL : _atual->valor;
}

Lista *Lista_create()
{
  Lista *ls = calloc(1, sizeof(Lista));
  ls->primeiro = calloc(1, sizeof(Elo));
  return ls;
}

void Lista_destroy(Lista *lista)
{
  Elo *el = lista->primeiro;
  while(el)
    {
      Elo *_proximo = el->proximo;
      free(el);
      el = _proximo;
    }
  free(lista);
}

void Lista_clear_destroy(Lista *lista)
{
  Elo *el = lista->primeiro->proximo;
  while(el)
    {
      Elo *_proximo = el->proximo;
      free(el->valor);
      free(el);
      el = _proximo;
    }
  free(lista->primeiro);
  free(lista);
}

void Lista_each(Lista *lista, funcao_each fe)
{
  Elo *el = lista->primeiro->proximo;
  while(el != NULL)
    {
      fe(el->valor);
      el = el->proximo;
    }
}

void Lista_push(Lista *lista, void *valor)
{
  Elo *el = calloc(1, sizeof(Elo));
  el->valor = valor;

  Elo *aux_elo = lista->primeiro;
  while(aux_elo->proximo)
    {
      aux_elo = aux_elo->proximo;
    }
  aux_elo->proximo = el;

  lista->tamanho++;
}

void *Lista_pop(Lista *lista)
{
  void *aux_valor;
  Elo *aux_ant;
  Elo *aux_elo = lista->primeiro;
  if(aux_elo->proximo == NULL)
    {
      return NULL;
    }
  do
    {
      aux_ant = aux_elo;
      aux_elo = aux_elo->proximo;
    } while(aux_elo->proximo);
  aux_valor = aux_elo->valor;
  free(aux_elo);
  aux_ant->proximo = NULL;

  lista->tamanho--;
  return aux_valor;
}

void *Lista_shift(Lista *lista)
{
  if(lista->primeiro->proximo == NULL)
    {
      return NULL;
    }
  Elo *aux_prox = lista->primeiro->proximo->proximo;
  void *aux_valor = lista->primeiro->proximo->valor;
  free(lista->primeiro->proximo);
  lista->primeiro->proximo = aux_prox;

  lista->tamanho--;
  return aux_valor;
}

void Lista_unshift(Lista *lista, void *valor)
{
  Elo *el = calloc(1, sizeof(Elo));
  el->valor = valor;
  el->proximo = lista->primeiro->proximo;

  lista->primeiro->proximo = el;

  lista->tamanho++;
}

void *Lista_remove(Lista *lista, void *valor, funcao_compare fc)
{
  int comp;
  void *aux_valor;
  Elo *aux_ant;
  Elo *aux_elo = lista->primeiro;
  if(aux_elo->proximo != NULL)
    {
      do
	{
	  aux_ant = aux_elo;
	  aux_elo = aux_elo->proximo;
	  comp = fc(aux_elo->valor, valor);
	} while(aux_elo->proximo && comp != 0);

      if(comp == 0)
	{
	  aux_ant->proximo = aux_elo->proximo;
	  aux_valor = aux_elo->valor;
	  free(aux_elo);
	  lista->tamanho--;

	  return aux_valor;
	}
    }
  return NULL;
}
