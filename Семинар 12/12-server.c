#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char pathname[] = "12-server.c";

struct msg_buf_1 {
    long msg_type;
    struct {
        pid_t pid;
        double client_request;
    } request;
} request_buf;

struct msg_buf_2 {
    long msg_type;
    struct {
        double server_response;
    } response;
} response_buf;

int main() {
    int msqid;
    key_t key;
    int len, max_len;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can't get msqid\n");
        exit(-1);
    }

    while (1) {
        max_len = sizeof(request_buf.request);
        len = msgrcv(msqid, (struct msgbuf *) &request_buf, max_len, 1, 0) < 0;
        if (len) {
            printf("Can't receive message from queue\n");
            exit(-1);
        }

        response_buf.msg_type = request_buf.request.pid;
        response_buf.response.server_response = request_buf.request.client_request * request_buf.request.client_request;
        len = sizeof(response_buf.response);
        len = msgsnd(msqid, (struct msgbuf *) &response_buf, len, 0);
        if (len < 0) {
            printf("Can't send message\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
}
