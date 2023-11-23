#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
  
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
  
    while(1)
    {
        // msgrcv to receive message
        msgrcv(msgid, &message, sizeof(message), 1, 0);
  
        // display the message
        //printf("Data Received is : %s \n", 
                    //message.mesg_text);
        
        if(message.mesg_text[0]=='g' && message.mesg_text[1]=='e' && message.mesg_text[2]=='t' && message.mesg_text[3]=='c' && message.mesg_text[4]=='w' && message.mesg_text[5]=='d')
        {
            char pwd[500];
            getcwd(pwd,sizeof(pwd));

            snprintf(message.mesg_text, sizeof(message.mesg_text),"%s\n",pwd);
        }
        else if(message.mesg_text[0]=='g' && message.mesg_text[1]=='e' && message.mesg_text[2]=='t' && message.mesg_text[3]=='p' && message.mesg_text[4]=='i' && message.mesg_text[5]=='d')
        {
            snprintf(message.mesg_text, sizeof(message.mesg_text),"%d\n",getpid());
        }
        else if(message.mesg_text[0]=='t' && message.mesg_text[1]=='i' && message.mesg_text[2]=='m' && message.mesg_text[3]=='e')
        {
            time_t sec;
            sec=time(NULL);

            snprintf(message.mesg_text, sizeof(message.mesg_text),"%ld hours.\n",sec/3600);
        }
        if(message.mesg_text[0]=='m' && message.mesg_text[1]=='k' && message.mesg_text[2]=='d' && message.mesg_text[3]=='i' && message.mesg_text[4]=='r')
        {
            char c[1000];
            int i=6;
            while(message.mesg_text[i]!=')')
            {  
                c[i-6]=message.mesg_text[i];
                i++;
            }
            c[i-6]='\0';
            //printf("%s",c);

            if (!mkdir(c,S_IRWXU))
            {
                snprintf(message.mesg_text, sizeof(message.mesg_text),"Directory created successfully.\n");
            }
            else
            {
                snprintf(message.mesg_text, sizeof(message.mesg_text),"Directory already exists.\n");
            }
        }
        else if(message.mesg_text[0]=='r' && message.mesg_text[1]=='m' && message.mesg_text[2]=='d' && message.mesg_text[3]=='i' && message.mesg_text[4]=='r')
        {
            char c[1000];
            int i=6;
            while(message.mesg_text[i]!=')')
            {
                c[i-6]=message.mesg_text[i];
                i++;
            }
            c[i-6]='\0';

            if (!rmdir(c))
            {
                snprintf(message.mesg_text, sizeof(message.mesg_text),"Directory removed successfully.\n");
            }
            else
            {
                snprintf(message.mesg_text, sizeof(message.mesg_text),"Directory does not exist.\n");
            }
        }
        else if(message.mesg_text[0]=='E' && message.mesg_text[1]=='n' && message.mesg_text[2]=='d') break;
        
        //sprintf(message.mesg_text,"%s\n",system(message.mesg_text));
        msgsnd(msgid, &message, sizeof(message), 0);
    }
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}