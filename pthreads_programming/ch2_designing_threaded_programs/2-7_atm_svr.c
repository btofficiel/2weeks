#include <stdio.h>
#include <pthread.h>

typedef struct workorder {
    int conn;
    char req_buf[COMM_BUF_SIZE];
} workorder_t;

int main(int argc, char **argv) {
    workorder_t *workorderp;
    pthread_t *worker_threadp;
    int conn;
    int trans_id;

    atm_server_init(argc, argv);

    for(;;) {
        // Wait for the request
        
        workorderp = (workorder_t *) malloc(sizeof(workorderp));
        server_comm_get_request(&workorderp->conn, workorderp->req_buf);

        sscanf(workorderp->req_buf, "%d", &trans_id);
        if(trans_id == SHUTDOWN) {
            break;
        }

        worker_threadp=(pthread_t *) malloc(sizeof(pthread_t));
        pthread_create(worker_threadp, NULL, processs_request, (void *) workorderp);

        pthread_detach(*worker_threadp);
        free(workorderp);
    }

    server_comm_shutdown();
    return 0;
}

void process_request(workorder_t *workorderp) {
    char resp_buf[COMM_BUF_SIZE];
    sscanf(workorderp->req_buf,m "%d", &trans_id);
    switch(trans_id) {
        case CREATE_ACCT_TRANS:
            create_account(resp_buf);
            break;
        case DEPOSIT_TRANS:
            deposit(workorderp->req_buf, resp_buf);
            break;
        case WITHDRAW_TRANS:
            withdraw(workorderp->req_buf, resp_buf);
            break;
        case BALANCE_TRANS:
            balance(workorderp->req_buf, resp_buf);
        default:
            handle_bad_trans_id(workorderp->req_buf, resp_buf);
            break;
    }

    server_comm_send_response(workorderp->conn, resp_buf);
    
    free(workorderp);
}
