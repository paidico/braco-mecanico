#include <stdio.h>

#include "arquivo.h"
#include "braco.h"

int main(int argc, char *argv[])
{
  int retorno = -1;

  char *in;
  Arquivo *a = NULL, *b = NULL;
  Braco *braco = NULL;
  if(argc != 2)
    {
      printf("O programa espera um arquivo de entrada.\n");
      goto error;
    }
  in = argv[1];
  if(!(a = Arquivo_create()) || !Arquivo_read_from(a, in))
    {
      printf("Falha ao criar arquivo \"%s\".\n", in);
      goto error;
    }
  if(!(b = Arquivo_create()))
    {
      goto error;
    }

  braco = Braco_create(a);
  Braco_process_start(braco);
  Braco_write(braco, b);

  retorno = 0;

 error: /* fallthrough proposital */
  Arquivo_destroy(a);
  Arquivo_destroy(b);
  Braco_destroy(braco);

  printf("Programa encerrado.\n");
  return retorno;
}

/* #include <stdio.h> */
/* #include <string.h> */

/* #include "lista.h" */
/* #include "pilha.h" */
/* #include "fila.h" */

/* void imprime(void *nome) */
/* { */
/*   printf("|| %s\n", (char *)nome); */
/* } */

/* int compara(void *a, void *b) */
/* { */
/*   return strcmp((char *)a, (char *)b); */
/* } */

/* int main(int argc, char *argv[]) */
/* { */
/*   /\* Teste de implementação *\/ */

/*   Lista *ls = Lista_create(); */
/*   Lista_push(ls, "Adriano"); */
/*   Lista_push(ls, "Pedro"); */
/*   Lista_push(ls, "dos"); */
/*   Lista_push(ls, "Santos"); */
/*   Lista_each(ls, imprime); */
/*   printf("total: %d\n", Lista_size(ls)); */
/*   imprime(Lista_first(ls)); */
/*   imprime(Lista_last(ls)); */
/*   printf("##########################\n"); */
/*   const char *wiped; */
/*   int n = 0; */
/*   while((wiped = Lista_pop(ls))) */
/*     { */
/*       printf("pop_%d:\t%s\n--------------------------\n", ++n, wiped); */
/*       Lista_each(ls, imprime); */
/*       printf("--------------------------\ntotal: %d\n", Lista_size(ls)); */
/*     } */
/*   Lista_push(ls, "Dó"); */
/*   Lista_push(ls, "Ré"); */
/*   Lista_each(ls, imprime); */
/*   printf("total: %d\n", Lista_size(ls)); */
/*   n = 0; */
/*   while((wiped = Lista_shift(ls))) */
/*     { */
/*       printf("shifted_%d:\t%s\n--------------------------\n", ++n, wiped); */
/*       Lista_each(ls, imprime); */
/*       printf("--------------------------\ntotal: %d\n", Lista_size(ls)); */
/*     } */
/*   n = argc; */
/*   while(--n > 0) */
/*     { */
/*       Lista_unshift(ls, argv[n]); */
/*     } */
/*   Lista_each(ls, imprime); */
/*   printf("total: %d\n", Lista_size(ls)); */
/*   Lista_pop(ls); */
/*   Lista_each(ls, imprime); */
/*   printf("total: %d\n", Lista_size(ls)); */

/*   imprime(Lista_remove(ls, "Dó", compara)); */
/*   imprime(Lista_remove(ls, "Ré", compara)); */
/*   imprime(Lista_remove(ls, "Mi", compara)); */
/*   imprime(Lista_remove(ls, "Fá", compara)); */
/*   printf("total: %d\n", Lista_size(ls)); */
/*   printf("\nvisão final:\n--------------------------\n"); */
/*   Lista_each(ls, imprime); */
/*   printf("--------------------------\ntotal: %d\n", Lista_size(ls)); */
/*   Lista_destroy(ls); */
/*   printf("\n--------------------------\n"); */
/*   printf("-------- pilha -----------\n"); */
/*   printf("--------------------------\n"); */
/*   Pilha *pl = Pilha_create(); */
/*   Pilha_push(pl, "Mônica"); */
/*   Pilha_push(pl, "Cebolinha"); */
/*   Pilha_push(pl, "Cascão"); */
/*   Pilha_each(pl, imprime); */
/*   printf("--------------------------\n"); */
/*   Pilha_pop(pl); */
/*   Pilha_each(pl, imprime); */
/*   printf("--------------------------\n"); */
/*   imprime(Pilha_stacktop(pl)); */
/*   printf("--------------------------\n"); */
/*   Pilha_destroy(pl); */
/*   printf("\n--------------------------\n"); */
/*   printf("-------- fila ------------\n"); */
/*   printf("--------------------------\n"); */
/*   Fila *fl = Fila_create(); */
/*   Fila_enqueue(fl, "Mônica"); */
/*   Fila_enqueue(fl, "Chico Bento"); */
/*   Fila_enqueue(fl, "Cebolinha"); */
/*   Fila_enqueue(fl, "Cascão"); */
/*   Fila_each(fl, imprime); */
/*   printf("--------------------------\n"); */
/*   Fila_dequeue(fl); */
/*   imprime(Fila_peek(fl)); */
/*   printf("--------------------------\n"); */
/*   Fila_dequeue(fl); */
/*   Fila_each(fl, imprime); */
/*   Fila_destroy(fl); */

/*   return 0; */
/* } */
