#include <stdio.h>
#include <time.h>

void do_one_thing(int *);
void do_another_thing(int *);
void do_wrap(int, int);

int r1 =0;
int r2=0;

int main(void) {
     struct timespec start, end;
    // Start the timer
    clock_gettime(CLOCK_MONOTONIC, &start);

    do_one_thing(&r1);
    do_another_thing(&r2);
    do_wrap(r1, r2);


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
