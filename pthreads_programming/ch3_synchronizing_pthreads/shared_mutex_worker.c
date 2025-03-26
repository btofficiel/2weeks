#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "shared_mutex.h"

void increment_counter(SharedData* shared);

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if(shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    SharedData *shared = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(shared == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }


    //Fork two child processes
    pid_t pid1 = fork();
    if(pid1 == -1) {
        perror("pid1");
        exit(1);
    }

    if(pid1 == 0) {
        increment_counter(shared);
        printf("Child 1 done\n");
        exit(0);
    }

    pid_t pid2 = fork();
    if(pid2 == -1) {
        perror("pid2");
        exit(1);
    }

    if(pid2 == 0) {
        increment_counter(shared);
        printf("Child 2 done\n");
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    
    printf("Final counter: %d\n", shared->counter);

    pthread_mutex_destroy(&shared->mutex);
    munmap(shared, sizeof(SharedData));
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return 0;
}

void increment_counter(SharedData* shared) {
    for(int i=0; i < NUM_INCREMENTS;i++) {
        if(pthread_mutex_lock(&shared->mutex) != 0) {
            perror("pthread_mutex_lock");
            exit(1);
        }

        shared->counter++;

        if(pthread_mutex_unlock(&shared->mutex) != 0) {
            perror("pthread_mutex_unlock");
            exit(1);
        }
    }
}



