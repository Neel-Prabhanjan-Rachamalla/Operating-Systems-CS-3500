#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define MAX 10000
  
// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[5000];
} message;
  
int main()
{
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
  
    while(1)
    {
        printf("Write Data : ");
        fgets(message.mesg_text,MAX,stdin);

       // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);
  
        // display the message
        printf("Data send is : %s \n", message.mesg_text);
  
        if(message.mesg_text[0]=='E' && message.mesg_text[1]=='n' && message.mesg_text[2]=='d') break;

        msgrcv(msgid, &message, sizeof(message), 1, 0);
  
        // display the message
        printf("Data Received is : %s \n", 
                    message.mesg_text);
    }
    return 0;
}