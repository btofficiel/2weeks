#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void thread_func(void *arg);

int main() {
    pthread_t t;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    pthread_create(&t, NULL, (void*) thread_func, NULL);

    printf("SEND SIGUSR1: kill -SIGUSR1 %d\n", getpid());

    pthread_join(t, NULL);

    return 0;
}

void thread_func(void *arg) {
    int i=0;
    int caught_signum;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    for(;;i++) {
        sigwait(&set, &caught_signum);
        printf("SIGNAL %d caught inside thread_func()\n", caught_signum);
    }
}
