#include <stdio.h>
#include <pthread.h>

int main() {
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
    printf("_POSIX_THREAD_ATTR_STACKSIZE supported: %ld\n", _POSIX_THREAD_ATTR_STACKSIZE);
#else
    printf("_POSIX_THREAD_ATTR_STACKSIZE not supported\n");
#endif

#ifdef _POSIX_THREAD_ATTR_STACKADDR
    printf("_POSIX_THREAD_ATTR_STACKADDR supported: %ld\n", _POSIX_THREAD_ATTR_STACKADDR);
#else
    printf("_POSIX_THREAD_ATTR_STACKADDR not supported\n");
#endif

#ifdef _POSIX_THREAD_PRIORITY_SCHEDULING
    printf("_POSIX_THREAD_PRIORITY_SCHEDULING supported: %ld\n", _POSIX_THREAD_PRIORITY_SCHEDULING);
#else
    printf("_POSIX_THREAD_PRIORITY_SCHEDULING not supported\n");
#endif

    return 0;
}
