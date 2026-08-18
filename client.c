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

    // Generate the same key
    key = ftok("server.c", 65);
    // Access message queue
    msgid = msgget(key, 0666);

    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // Send message
    msg.msg_type = 1;
    strcpy(msg.msg_text, "Hello Server");

    msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);

    printf("Client sent: %s\n", msg.msg_text);

    // Receive reply
    msgrcv(msgid, &msg, sizeof(msg.msg_text), 2, 0);
   printf("Client received: %s\n", msg.msg_text);

    return 0;
}
