#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 100

// FUNCAO QUE IMPRIME VALOR PRIMO
void * isPrimo (void *arg) {
    int *valor;
    valor = (int *)(arg); // O ARGUMENTO RECEBIDO É CONVERTIDO EM INTEIRO (RECEBE 100 VETORES DE TAMANHO 1000)
	int i, j;
	int cont = 0; // SINALIZADOR QUE VERIFICA SE O VALOR É PRIMO OU NÃO

	for(i = (*valor - 1000); i <= *valor; i++){ 
                for(j = 2; j < (i/2); j++){   // PERCORRE OS VALORES NO INTERVALO DE 2 À METADE DO VALOR QUE ESTÁ SENDO VERIFICADO
                        if(i % j == 0){  // VERIFICA SE O VALOR É PRIMO OU NÃO
                                cont += 1;  // SE O VALOR ENTRAR NO CONDIÇÃO, OU SEJA, FOR PRIMO A FUNÇÃO SOMA UM 
                                break;      // E PARA A EXECUÇÃO DAQUELE VALOR PARA QUE OUTRO SEJA EXECUTADO
                        }
                }
                if(cont == 0){
                        printf("Thread %ld, valor: %i \n",*valor/1000, i);  
                }
                cont = 0;
	}
}

int main () {
	pthread_t t[NUM_THREADS];
	int i;
	int a[NUM_THREADS]; // GUARDA OS ARGUMENTOS DAS THREADS

	for(i = 0; i < NUM_THREADS; i++){ // DEFINE OS ARGUMENTOS DAS THREADS, QUE SERÃO MULTIPLICADOS POR 1000
                a[i] = (i + 1) * 1000;
	}

	for(i = 0; i < NUM_THREADS; i++){ // CRIA AS THREADS
                pthread_create(&t[i], NULL, isPrimo, (void *)(&a[i])); 
	}

	for(i = 0; i < NUM_THREADS; i++){ // FINALIZA AS THREADS
        pthread_join(t[i], NULL);
	}

	exit(0);
}
