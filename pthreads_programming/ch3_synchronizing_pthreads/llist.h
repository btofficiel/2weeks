/* llist.h */
#include <pthread.h>

typedef struct llist_node {
    int index;
    void *datap;
    struct llist_node *nextp;
} llist_node_t;

typedef struct llist {
    llist_node_t *first;
    pthread_mutex_t mutex;
} llist_t;


int llist_init(llist_t *llist_t);
int llist_insert_data(int index, void *datap, llist_t *llistp);
