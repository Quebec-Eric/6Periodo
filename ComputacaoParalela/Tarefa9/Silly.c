
/*
--------------------------------------------------------
OBS Todos os testes foram realizados no servidor parcode|
---------------------------------------------------------




 Tempo paralelo com scadule(static)
 com paralelo nos for das linhas {156,172,181}

 Teste 1:
 real	0m2.633s
 user	0m4.884s 
 sys	0m0.000s

 Tste 2:
 real	0m3.890s
 user	0m6.143s
 sys	0m0.000s

 Teste 3:
 real	0m2.635s 
 user	0m4.891s
 sys	0m0.000s

 Teste 4:
 real	0m2.631s
 user	0m4.883s
 sys	0m0.000s

 Teste 5:

 real	0m2.636s
 user	0m4.889s
 sys	0m0.000s

 
 Tempo paralelo com scadule(static)
 sem  a parelizacao nos for das linhas {156,172,181}

 Teste 1:
 real	0m2.633s
 user	0m4.888s
 sys	0m0.000s
   
 Teste 2:
 real	0m3.928s
 user	0m6.184s
 sys	0m0.000s

 Teste 3: 
 real	0m2.640s
 user	0m4.905s
 sys	0m0.000s

 Teste 4:
 real	0m2.702s
 user	0m4.952s
 sys	0m0.104s
   
 Teste 5:
 real	0m2.687s
 user	0m5.122s
 sys	0m0.005s


Tempo paralelo com scadule(guided)
 com paralelo nos for das linhas {156,172,181}

 Teste 1:
 real	0m2.651s
 user	0m4.880s
 sys	0m0.004s

 Teste 2:
 real	0m2.631s
 user	0m4.882s
 sys	0m0.000s

 Teste 3:
 real	0m2.824s
 user	0m5.081s
 sys	0m0.004s

 Teste 4:
 real	0m2.645s
 user	0m4.908s
 sys	0m0.004s
 
 Teste 5:
 real	0m3.465s
 user	0m5.724s
 sys	0m0.000s


Tempo paralelo com scadule(guided)
 sem a  parelizacao nos for das linhas {156,172,181}

 Teste 1:
 real	0m4.361s
 user	0m4.358s 
 sys	0m0.000s

 Teste 2:
 real	0m4.369s
 user	0m4.358s
 sys	0m0.008s

 Teste 3:
 real	0m4.364s
 user	0m4.357s
 sys	0m0.004s

 Teste 4:
 real	0m4.365s
 user	0m4.363s
 sys	0m0.000s

 Teste 5:
 real	0m4.511s
 user	0m4.503s
 sys	0m0.004s



 Com todos os tempos analisados, pode-se verificar que com a utilizacao do  scadule(guided) foi possivel obter o melhor tempo , sendo 
 a melhor opcao para a parelizacao desse codigo em si 


 Alunos :
 Eric Azevedo 
 Felipe Nepomuceno
 Bruno Pena
 Diogo Rios

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(int argc, char **argv)
{
   omp_set_num_threads(2);

   int i, j, n = 30000;

   // Allocate input, output and position arrays
   int *in = (int*) calloc(n, sizeof(int));
   int *pos = (int*) calloc(n, sizeof(int));
   int *out = (int*) calloc(n, sizeof(int));
 
   //Initialize input array in the reserve order
   #pragma omp parallel for
   for(i=0; i < n; i++)
      in[i] = n-i;

   // Print input array
   //   for(i=0; i < n; i++)
   //      printf("%d ",in[i]);
   
   // Silly sort (you have to make this code parallel)
   #pragma omp parallel for collapse(2) schedule(guided)
   for(i=0; i < n; i++)
      for(j=0; j < n; j++)
	     if(in[i] > in[j])
            pos[i]++;
 
   //Move elements to final position
   #pragma omp parallel for
   for(i=0; i < n; i++)
      out[pos[i]] = in[i];

   // print output array
   //   for(i=0; i < n; i++)
   //      printf("%d ",out[i]);

   //check if answer is correct
   #pragma omp parallel for
   for(i=0; i < n; i++)
      if(i+1 != out[i])
      {
         printf("test failed\n");
         exit(0);
      }

   printf("test passed\n");
    return 0;
}
