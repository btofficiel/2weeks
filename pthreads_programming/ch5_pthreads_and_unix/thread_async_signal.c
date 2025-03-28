#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void handler(int signum);
void eligible_thread(void *arg);
void ineligible_thread(void *arg);

int main() {
    signal(SIGUSR1, handler);
    pthread_t t1, t2;

    pthread_create(&t1, NULL, (void *) eligible_thread, NULL);
    pthread_create(&t2, NULL, (void *) ineligible_thread, NULL);

    printf("Send USR1: kill -USR1 %d\n", getpid());

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

void handler(int signum) {
    printf("Signal %d received from thread %llu\n", signum, (unsigned long long) pthread_self());
}

void eligible_thread(void *arg) {
    while(1) sleep(1);
}

void ineligible_thread(void *arg) {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    while(1) sleep(1);
}
