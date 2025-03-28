#include <stdio.h>
#include <signal.h>

void sig_handler(int signum) {
    printf("Simple Handler: Signal %d received\n", signum);
}


int main() {
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger signal handler\n\n");  
    while(1){}

    return 0;
}


