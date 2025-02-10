#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//  provides access to the POSIX operating system API
#include <unistd.h>
// defines several data types used in system calls and other low-level operations
#include <sys/types.h>
// provides definitions for Inter-Process Communication (IPC) mechanisms such as message queues, semaphores, and shared memory.
#include <sys/ipc.h>
// provides facilities for creating and managing shared memory segments between processes.
#include <sys/shm.h>
// provides functions and macros for controlling and waiting for child processes.
#include <sys/wait.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap(int, int);

int shared_mem_id;
int *shared_mem_ptr;
int *r1p;
int *r2p;

int main(void) {
     struct timespec start, end;
    // Start the timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t child1_pid, child2_pid;
    int status;
    // Create a new shared memory segment with 0660 file permissions
    // Owner and the group can read or write from the memory segment
    // 0660 = rw-rw----
    shared_mem_id = shmget(IPC_PRIVATE, 2*sizeof(int), 0660);

    // Attaches shared memory segment to process's address space
    // (void *) 0 is equivalent to NULL here which tells the system to attach 
    // the shared memory segment automatically to a suitable address
    // 0 as the last argument means we aren't passing any specific shmflg.
    shared_mem_ptr = (int*) shmat(shared_mem_id, (void *) 0, 0);

    r1p = shared_mem_ptr;
    r2p = (shared_mem_ptr+1);

    *r1p = 0;
    *r2p = 0;

    if ((child1_pid = fork()) == 0) {
        // first child
        do_one_thing(r1p);
        exit(0);
    }

    if((child2_pid = fork()) == 0) {
        // second child
        do_another_thing(r2p);
        exit(0);
    }


    // parent 
   //  wait for a specific child process to change its state (e.g., terminate, stop, or resume) 
    waitpid(child1_pid, &status, 0);
    waitpid(child2_pid, &status, 0);

    do_wrap(*r1p, *r2p);


    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    // Calculate the elapsed time in seconds
    double elapsed_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_nsec - start.tv_nsec) * 1e-9;
    // Print the elapsed time
    printf("\nElapsed time: %f seconds\n", elapsed_time);

    return 0;
}

void do_one_thing(int *pnum_times) {
    int i,j,x;

    for(i = 0; i < 4; i++) {
        printf("doing one thing\n");
        for(j=0; j < 10000; j++) {
            x = x+i;
            (*pnum_times)++;
        }
    }
}

void do_another_thing(int *pnum_times) {
    int i,j,x;

    for(i = 0; i < 4; i++) {
        printf("doing another thing\n");
        for(j=0; j < 10000; j++) {
            x = x+i;
            (*pnum_times)++;
        }
    }
}

void do_wrap(int one_times, int another_times) {
    int total;

    total = one_times+another_times;
    printf("wrap up: one thing %d, another %d, total %d\n", one_times, another_times, total);
}
