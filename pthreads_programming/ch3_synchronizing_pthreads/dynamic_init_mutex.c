#include <stdlib.h>
#include <pthread.h>

int main() {
    // Declare a pointer of type mutex
    pthread_mutex_t *dynamic_mutexp;

    // Allocate memory
    dynamic_mutexp = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));

    // Initialise mutex with default attributes
    pthread_mutex_init(dynamic_mutexp, NULL);

    return 0;
}


