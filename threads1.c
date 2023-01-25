

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define N 3

void* threadFunc(void* thread_data){
	//получаем структуру с данными
    int* x = (int*) thread_data;
    for ( int i = 0; i < 10000000; i++ )
    {
        *x = *x + 1; 
    }

    printf("%d \n", *x);
	return NULL;
}

int main()
{
    int x = 0; // *Здесь одна переменная

    //выделяем память под массив идентификаторов потоков
	pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));
	
    //сколько потоков - столько и переменных с потоковых данных
	//int* x = (int*) malloc(N * sizeof(int));  //*А нужно несколько по числу потоков

    for(int i = 0; i < N; i++)
    {
	   // x[i] = 0; //*здесь должно быть обнуление x[i]
		//запускаем поток
		pthread_create(&(threads[i]), NULL, threadFunc, &x);  //*здесь должно быть x[i]
	}

    	//ожидаем выполнение всех потоков
	for(int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);



	//освобождаем память
	free(threads);
	
    //free(x); //* нужно освободить память

    return 0;
}
