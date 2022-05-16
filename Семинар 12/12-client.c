#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    key_t key;
    int len, maxlen, msqid;
    double input;
    
    scanf("%lf", &input);

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        printf("Can't get msqid\n");
        exit(-1);
    }

    request_buf.msg_type = 1;
    request_buf.request.pid = getpid();
    request_buf.request.client_request = input;
    len = msgsnd(msqid, (struct msgbuf *) &request_buf, sizeof(request_buf.request), 0);

    if (len < 0) {
        printf("Can't send message\n");
        exit(-1);
    }

    maxlen = sizeof(response_buf.response);
    len = msgrcv(msqid, (struct msgbuf *) &response_buf, maxlen, getpid(), 0) < 0;
    if (len) {
        printf("Can't receive message\n");
        exit(-1);
    }

    printf("Message type = %d, request = %lf, response = %lf\n", request_buf.request.pid, request_buf.request.client_request, response_buf.response.server_response);

    return 0;
}
