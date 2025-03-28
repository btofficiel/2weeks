#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_FOLLOWERS 3

void handler(int signum);
void follower(void *arg);
void leader(void *arg);

int main() {
    pthread_t followers[NUM_FOLLOWERS];
    pthread_t t_leader;

    printf("Main thread: %llu\n", (unsigned long long)pthread_self());

    for(int i=0;i<NUM_FOLLOWERS;i++){
        pthread_create(&followers[i], NULL, (void *) follower, NULL);
    }

    pthread_create(&t_leader, NULL, (void *) leader, NULL);

    printf("Send USR1: kill -USR1 %d\n", getpid());

    // Block SIGUSR1 in main thread after creating threads
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    for(int i=0;i<NUM_FOLLOWERS;i++) {
        pthread_join(followers[i], NULL);
    }

    pthread_join(t_leader, NULL);

    return 0;
}

void handler(int signum) {
    printf("Signal %d received from thread %llu\n", signum, (unsigned long long) pthread_self());
}

void follower(void *arg) {
    printf("Follower thread: %llu\n", (unsigned long long)pthread_self());
    while(1) sleep(1);
}

void leader(void *arg) {
    printf("Leader thread: %llu\n", (unsigned long long)pthread_self());
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    while(1) sleep(1);
}
