#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key;
    int msgid;
    struct message msg;

    // Generate a key
    key = ftok("server.c", 65);
// Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    printf("Server started...\n");
    printf("Waiting for message from client...\n");

    // Receive message
    msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);

    printf("Server received: %s\n", msg.msg_text);

    // Send reply
    msg.msg_type = 2;
    strcpy(msg.msg_text, "Hello Client");
msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

    printf("Server sent: %s\n", msg.msg_text);

    // Delete message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
