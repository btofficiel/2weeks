#include <stdlib.h>
#include <pthread.h> 


// Static initialisation of a mutex
// This is defined and setup at compile time
pthread_mutex_t static_mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
    return 0;
}
