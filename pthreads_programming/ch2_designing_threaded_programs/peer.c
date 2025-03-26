/* Peers model for multithreading
 
   SAMPLE OUTPUT

Thread ID: 6135132160 performing Add operation: 5 + 5 = 10
Thread ID: 6135132160 performing Mul operation: 5 x 5 = 25
Thread ID: 6137999360 performing Div operation: 5 / 5 = 1
Thread ID: 6135132160 performing Div operation: 5 / 5 = 1
Thread ID: 6137999360 performing Add operation: 5 + 5 = 10
Thread ID: 6137999360 performing Mul operation: 5 x 5 = 25
Thread ID: 6136279040 performing Sub operation: 5 - 5 = 0
Thread ID: 6136279040 performing Add operation: 5 + 5 = 10
Thread ID: 6135705600 performing Mul operation: 5 x 5 = 25
Thread ID: 6135705600 performing Mul operation: 5 x 5 = 25
Thread ID: 6135705600 performing Div operation: 5 / 5 = 1
Thread ID: 6136852480 performing Div operation: 5 / 5 = 1
Thread ID: 6137999360 performing Div operation: 5 / 5 = 1
Thread ID: 6134558720 performing Div operation: 5 / 5 = 1
Thread ID: 6137425920 performing Mul operation: 5 x 5 = 25
Thread ID: 6136279040 performing Sub operation: 5 - 5 = 0
Thread ID: 6133985280 performing Mul operation: 5 x 5 = 25
Thread ID: 6135132160 performing Sub operation: 5 - 5 = 0

*/

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_PEERS 8

pthread_mutex_t tq_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t tq_not_empty=PTHREAD_COND_INITIALIZER;

typedef enum {
    ADD,
    SUB,
    MUL,
    DIV
} Action;


void add(int a, int b);
void sub(int a, int b);
void mul(int a, int b);
void dvd(int a, int b);

typedef struct _args {
    int arg1;
    int arg2;
} FnArgs;

typedef struct _task {
    Action action;
    void (*function)(int, int);
    FnArgs fn_args; 
   struct _task *next;
} Task;

typedef struct _queue {
    Task *front;
    Task *back;
} TaskQueue;

void initialise_task_queue(TaskQueue *tq);
void add_task(TaskQueue *tq, Task *t);
Task* pop_task(TaskQueue *tq);
bool empty(TaskQueue *tq);
Task *create_task(Action action, int arg1, int arg2);
void peer(TaskQueue *tq);
// Returns a function pointer
void (*get_fn(Action action))(int, int) {
    switch(action) {
        case ADD:
            return (void *) &add;
        case SUB:
            return (void *) &sub;
        case MUL:
            return (void *) &mul;
        case DIV: 
            return (void *) &dvd;
    }
}

int main() {
    pthread_t peers[NUM_PEERS];
    TaskQueue *tq = (TaskQueue *) malloc(sizeof(TaskQueue));
    initialise_task_queue(tq);


    // Creating a threadpool
    for(int i=0; i<NUM_PEERS;i++) {
        pthread_create(&peers[i], NULL, (void *) peer, (void *) tq);
    }

    while(1) {
        for(int i=0;i<1000;i++) {
            Task *addTask = create_task(ADD, 5, 5);
            Task *subTask = create_task(SUB, 5, 5);
            Task *mulTask = create_task(MUL, 5, 5);
            Task *divTask = create_task(DIV, 5, 5);
            //Add tasks to the task queue
            add_task(tq, addTask);
            pthread_cond_signal(&tq_not_empty);
            add_task(tq, subTask);
            add_task(tq, mulTask);
            add_task(tq, divTask);
        }
        sleep(1);
    }

    for(int i=0; i<NUM_PEERS;i++) {
        pthread_join(peers[i], NULL);
    }

    return 0;
}

void initialise_task_queue(TaskQueue *tq) {
    tq->front = NULL;
    tq->back = NULL;
}

void add_task(TaskQueue *tq, Task *t) {
    if(tq->front == NULL) {
        tq->front = t;
        tq->back = t;
    } else {
        tq->back->next = t;
        tq->back = t;
    }
}

Task *pop_task(TaskQueue *tq) {
    if(tq->front == NULL) {
        return NULL;
    }

    Task *t = tq->front;
    tq->front = tq->front->next;
    
    return t;
}

bool empty(TaskQueue *tq) {
    return (tq->front == NULL);
}

Task *create_task(Action action, int arg1, int arg2) {
    Task *t = (Task *) malloc(sizeof(Task));
    FnArgs args;
    args.arg1 = arg1;
    args.arg2 = arg2;

    t->action = action;
    t->function = get_fn(action);
    t->fn_args = args;
    t->next = NULL;

    return t;
}

void peer(TaskQueue *tq) {
    while(1) {
        // Take out a task from the task queue and run the action for it.
        pthread_mutex_lock(&tq_lock);

        while(empty(tq)) {
            pthread_cond_wait(&tq_not_empty, &tq_lock);
        }

        Task *t = pop_task(tq);

        pthread_mutex_unlock(&tq_lock);

        t->function(t->fn_args.arg1, t->fn_args.arg2);
        free(t);
        t = NULL;
    }
}

void add(int a, int b) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu performing Add operation: %d + %d = %d\n", (unsigned long)tid, a, b, (a+b));
}

void sub(int a, int b) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu performing Sub operation: %d - %d = %d\n", (unsigned long)tid, a, b, (a-b));
}

void mul(int a, int b) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu performing Mul operation: %d x %d = %d\n", (unsigned long)tid, a, b, (a*b));
}

void dvd(int a, int b) {
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu performing Div operation: %d / %d = %d\n", (unsigned long)tid, a, b, (a/b));
}
