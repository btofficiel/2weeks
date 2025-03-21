#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "shared_mutex.h"

int main() {
    //Create/Open a shared memory object
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);
    if(shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if(ftruncate(shm_fd, sizeof(SharedData)) == -1) {
        perror("ftruncate");
        exit(1);
    }
    
    //Map shared memory
    SharedData *shared = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(shared == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    pthread_mutexattr_t m_attr;
    if(pthread_mutexattr_init(&m_attr) != 0) {
        perror("pthread_mutexattr_init");
        exit(1);
    }

    // Set mutex attribute to PTHREAD_PROCESS_SHARED to make it available cross processes
    if(pthread_mutexattr_setpshared(&m_attr, PTHREAD_PROCESS_SHARED) != 0) {
        perror("pthread_attr_setpshared");
        exit(1);
    }

    if(pthread_mutex_init(&shared->mutex, &m_attr) != 0) {
        perror("pthread_mutex_init");
        exit(1);
    }


    pthread_mutexattr_destroy(&m_attr);

    //Intialise the counter with the value 0
    shared->counter = 0;

    //Unmap shared memory
    munmap(shared, sizeof(SharedData));
    close(shm_fd);

    return 0;
}


