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
  if(a)
    {
      Arquivo_destroy(a);
    }
  if(b)
    {
      Arquivo_destroy(b);
    }
  if(braco)
    {
      Braco_destroy(braco);
    }

  printf("Programa encerrado.\n");
  return retorno;
}
