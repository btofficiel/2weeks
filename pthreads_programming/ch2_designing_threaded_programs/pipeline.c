/* Pipeline model for multithreading
 * Pipeline stages: Add -> Sub -> Mul -Div
 
   SAMPLE OUTPUT

Thread ID: 6097891328 performing Div operation: 140 / 2 = 70
Thread ID: 6097891328 performing Div operation: 105 / 2 = 52
Thread ID: 6097891328 performing Div operation: 95 / 2 = 47
Thread ID: 6096744448 performing Mul operation: 23 x 5 = 115
Thread ID: 6098464768 performing Div operation: 125 / 2 = 62
Thread ID: 6097317888 performing Mul operation: 22 x 5 = 110
Thread ID: 6097891328 performing Div operation: 125 / 2 = 62
Thread ID: 6096744448 performing Mul operation: 29 x 5 = 145
Thread ID: 6098464768 performing Div operation: 145 / 2 = 72
Thread ID: 6097317888 performing Mul operation: 25 x 5 = 125
Thread ID: 6097891328 performing Div operation: 110 / 2 = 55
Thread ID: 6096744448 performing Mul operation: 20 x 5 = 100
Thread ID: 6098464768 performing Div operation: 145 / 2 = 72
Thread ID: 6097317888 performing Mul operation: 23 x 5 = 115
Thread ID: 6097891328 performing Div operation: 105 / 2 = 52
Thread ID: 6098464768 performing Div operation: 95 / 2 = 47
Thread ID: 6098464768 performing Div operation: 95 / 2 = 47
Thread ID: 6098464768 performing Div operation: 145 / 2 = 72
Thread ID: 6098464768 performing Div operation: 145 / 2 = 72
Thread ID: 6097891328 performing Div operation: 120 / 2 = 60
Thread ID: 6097891328 performing Div operation: 145 / 2 = 72
Thread ID: 6097891328 performing Div operation: 115 / 2 = 57
Thread ID: 6097891328 performing Div operation: 110 / 2 = 55
Thread ID: 6098464768 performing Div operation: 130 / 2 = 65
Thread ID: 6098464768 performing Div operation: 125 / 2 = 62
Thread ID: 6098464768 performing Div operation: 100 / 2 = 50
Thread ID: 6098464768 performing Div operation: 115 / 2 = 57
Thread ID: 6097891328 performing Div operation: 145 / 2 = 72

*/

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS_PER_STAGE 2

pthread_mutex_t aq_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t aq_not_empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t sq_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sq_not_empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mq_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mq_not_empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t dq_lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t dq_not_empty=PTHREAD_COND_INITIALIZER;

int add(int num);
int sub(int num);
int mul(int num);
void dvd(int num);

typedef struct _task {
    int value;
    struct _task *next;
} Task;

typedef struct _queue {
    Task *front;
    Task *back;
} TaskQueue;

typedef struct _prodcon {
    TaskQueue *prod;
    TaskQueue *con;
} ProducerConsumer;

void initialise_task_queue(TaskQueue *tq);
void initialise_prodcon(ProducerConsumer *pc, TaskQueue *prod, TaskQueue *con);
void add_task(TaskQueue *tq, Task *t);
Task* pop_task(TaskQueue *tq);
bool empty(TaskQueue *tq);
Task *create_task(int arg);
void add_worker(ProducerConsumer *pc);
void sub_worker(ProducerConsumer *pc);
void mul_worker(ProducerConsumer *pc);
void div_worker(TaskQueue *tq);

int main() {
    srand(time(0));
    pthread_t add_workers[NUM_THREADS_PER_STAGE];
    pthread_t sub_workers[NUM_THREADS_PER_STAGE];
    pthread_t mul_workers[NUM_THREADS_PER_STAGE];
    pthread_t div_workers[NUM_THREADS_PER_STAGE];

    TaskQueue *stage1 = (TaskQueue *) malloc(sizeof(TaskQueue));
    TaskQueue *stage2 = (TaskQueue *) malloc(sizeof(TaskQueue));
    TaskQueue *stage3 = (TaskQueue *) malloc(sizeof(TaskQueue));
    TaskQueue *stage4 = (TaskQueue *) malloc(sizeof(TaskQueue));
    initialise_task_queue(stage1);
    initialise_task_queue(stage2);
    initialise_task_queue(stage3);
    initialise_task_queue(stage4);

    ProducerConsumer *aq_pc = (ProducerConsumer *) malloc(sizeof(ProducerConsumer));
    ProducerConsumer *sq_pc = (ProducerConsumer *) malloc(sizeof(ProducerConsumer));
    ProducerConsumer *mq_pc = (ProducerConsumer *) malloc(sizeof(ProducerConsumer));
    initialise_prodcon(aq_pc, stage2, stage1);
    initialise_prodcon(sq_pc, stage3, stage2);
    initialise_prodcon(mq_pc, stage4, stage3);


    // Creating a threadpool
    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_create(&add_workers[i], NULL, (void *) add_worker, (void *) aq_pc);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_create(&sub_workers[i], NULL, (void *) sub_worker, (void *) sq_pc);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_create(&mul_workers[i], NULL, (void *) mul_worker, (void *) mq_pc);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_create(&div_workers[i], NULL, (void *) div_worker, (void *) stage4);
    }

    while(1) {
        for(int i=0;i<1000;i++) {
            // Generate a random number between 10 and 20
            int random_number = rand() % 11 + 10;
            Task *t = create_task(random_number);
            //Add tasks to the task queue
            if(t) {
                add_task(stage1, t);
            }
            pthread_cond_signal(&aq_not_empty);
        }
        sleep(1);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_join(add_workers[i], NULL);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_join(sub_workers[i], NULL);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_join(mul_workers[i], NULL);
    }

    for(int i=0; i<NUM_THREADS_PER_STAGE;i++) {
        pthread_join(div_workers[i], NULL);
    }

    return 0;
}

void initialise_task_queue(TaskQueue *tq) {
    tq->front = NULL;
    tq->back = NULL;
}

void initialise_prodcon(ProducerConsumer *pc, TaskQueue *prod, TaskQueue *con) {
    pc->prod = prod;
    pc->con = con;
}

void add_task(TaskQueue *tq, Task *t) {
    t->next = NULL; // Prevent accidental use of stale pointers
    if (tq->front == NULL) {
        tq->front = t;
        tq->back = t;
    } else {
        tq->back->next = t;
        tq->back = t;
    }
}

Task *pop_task(TaskQueue *tq) {
    if (tq->front == NULL) {
        return NULL;
    }

    Task *t = tq->front;  // Store the front task
    tq->front = tq->front->next; // Move the front pointer to the next task

    if (tq->front == NULL) {
        tq->back = NULL;  // If the queue is empty, reset back pointer
    }

    t->next = NULL;  // Prevent stale pointer usage
    return t;
}


bool empty(TaskQueue *tq) {
    return (tq->front == NULL);
}

Task *create_task(int arg) {
    Task *t = (Task *) malloc(sizeof(Task));
    t->value = arg;
    t->next = NULL;

    return t;
}

void add_worker(ProducerConsumer *pc) {
    while(1) {
        // Take out a task from the task queue and run the action for it.
        pthread_mutex_lock(&aq_lock);

        while(empty(pc->con)) {
            pthread_cond_wait(&aq_not_empty, &aq_lock);
        }

        Task *t = pop_task(pc->con);

        pthread_mutex_unlock(&aq_lock);

        if(t) {
            t->value = add(t->value);
            pthread_mutex_lock(&sq_lock);
            add_task(pc->prod, t);
            pthread_cond_signal(&sq_not_empty);
            pthread_mutex_unlock(&sq_lock);
        }
    }
}

void sub_worker(ProducerConsumer *pc) {
    while(1) {
        // Take out a task from the task queue and run the action for it.
        pthread_mutex_lock(&sq_lock);

        while(empty(pc->con)) {
            pthread_cond_wait(&sq_not_empty, &sq_lock);
        }

        Task *t = pop_task(pc->con);

        pthread_mutex_unlock(&sq_lock);
        
        if(t) {
            t->value = sub(t->value);
            pthread_mutex_lock(&mq_lock);
            add_task(pc->prod, t);
            pthread_cond_signal(&mq_not_empty);
            pthread_mutex_unlock(&mq_lock);
        }
    }
}

void mul_worker(ProducerConsumer *pc) {
    while(1) {
        // Take out a task from the task queue and run the action for it.
        pthread_mutex_lock(&mq_lock);

        while(empty(pc->con)) {
            pthread_cond_wait(&mq_not_empty, &mq_lock);
        }

        Task *t = pop_task(pc->con);

        pthread_mutex_unlock(&mq_lock);

        if(t) {
            t->value = mul(t->value);
            pthread_mutex_lock(&dq_lock);
            add_task(pc->prod, t);
            pthread_cond_signal(&dq_not_empty);
            pthread_mutex_unlock(&dq_lock);
        }
    }
}

void div_worker(TaskQueue *tq) {
    while(1) {
        // Take out a task from the task queue and run the action for it.
        pthread_mutex_lock(&dq_lock);

        while(empty(tq)) {
            pthread_cond_wait(&dq_not_empty, &dq_lock);
        }

        Task *t = pop_task(tq);

        pthread_mutex_unlock(&dq_lock);

        if(t) {
            dvd(t->value);
    
            free(t);
            t = NULL;
        }
    }
}

int add(int num) {
    pthread_t tid = pthread_self();
    int result = num+10;
    printf("Thread ID: %lu performing Add operation: %d + 10 = %d\n", (unsigned long)tid, num, result);
    return result;
}

int sub(int num) {
    pthread_t tid = pthread_self();
    int result = num-1;
    printf("Thread ID: %lu performing Sub operation: %d - 1 = %d\n", (unsigned long)tid, num, result);
    return result;
}

int mul(int num) {
    pthread_t tid = pthread_self();
    int result = num*5;
    printf("Thread ID: %lu performing Mul operation: %d x 5 = %d\n", (unsigned long)tid, num, result);
    return result;
}

void dvd(int num) {
    pthread_t tid = pthread_self();
    int result = num/2;
    printf("Thread ID: %lu performing Div operation: %d / 2 = %d\n", (unsigned long)tid, num, result);
}
