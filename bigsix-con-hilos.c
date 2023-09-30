#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 2
#define CANTIDAD_INICIAL_HAMBURGUESAS 20

int cantidad_restante_hamburguesas = CANTIDAD_INICIAL_HAMBURGUESAS;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *comer_hamburguesa(void *tid) {
    while (1) {
        pthread_mutex_lock(&mutex);

        if (cantidad_restante_hamburguesas > 0) {
            printf("Hola! Soy el hilo(comensal) %ld, me voy a comer una hamburguesa! Quedan %d hamburguesas\n", (long)tid, cantidad_restante_hamburguesas);
            cantidad_restante_hamburguesas--;
        } else {
            printf("SE TERMINARON LAS HAMBURGUESAS :( \n");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&mutex);
        usleep(100000);
    }
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i, ret;

    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        status = pthread_create(&threads[i], NULL, comer_hamburguesa, (void *)(long)i);
        if (status != 0) {
            exit(-1);
        }
    }

    for (i = 0; i < NUMBER_OF_THREADS; i++) {
        void *retval;
        ret = pthread_join(threads[i], &retval);
        if (ret != 0) {
            exit(-1);
        }
    }

    pthread_exit(NULL);
}