#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "llist.h"

int val = 5;
void worker(llist_t *l);

int main() {
    llist_t *llistp;
    llistp = (llist_t *) malloc(sizeof(llist_t));
    llist_init(llistp);

    pthread_t t1;
    pthread_create(&t1, NULL, (void *) worker, (void *) llistp);
    pthread_join(t1, NULL);
    llist_node_t *node = llistp->first;
    printf("Value: %d\n", *((int *) node->datap));
    return 0;
}

void worker(llist_t *l) {
    llist_insert_data(0, (void *) &val, l);
}

int llist_init(llist_t *llistp) {
    llistp->first = NULL;
    pthread_mutex_init(&(llistp->mutex), NULL);
    return 0;
}

int llist_insert_data(int index, void *datap, llist_t *llistp) {
    llist_node_t *cur, *prev, *new;
    int found = false;

    pthread_mutex_lock(&(llistp->mutex));

    for(cur = prev = llistp->first; cur != NULL; prev = cur, cur=cur->nextp) {
        if (cur->index == index) {
            free(cur->datap);
            cur->datap = datap;
            found = true;
            break;
        } else if (cur->index > index) {
            break;
        }
    }

    if(!found) {
        new = (llist_node_t *) malloc(sizeof(llist_node_t));
        new->index = index;
        new->datap = datap;
        new->nextp = cur;
        if( cur == llistp->first) {
            llistp->first = new;
        } else {
            prev->nextp = new;
        }
    }

    pthread_mutex_unlock(&(llistp->mutex));

    return 0;
}

