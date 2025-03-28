#include <stdio.h>
#include <signal.h>

void sig_handler_extd(int signum, siginfo_t *info, void *context) {
    printf("Extended Handler: Signal %d received from PID %d\n", signum, info->si_pid);
}

int main() {
    struct sigaction sa;
    sa.sa_sigaction = sig_handler_extd;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger extended signal handler\n\n");  
    while(1){}

    return 0;
}


