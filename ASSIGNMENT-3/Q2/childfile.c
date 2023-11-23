#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define REQUEST 100
#define PIVOT 200
#define LARGE 300
#define SMALL 400
#define READY 500
#define KILL 600

int main(int argc,char *argv[])
{

    int id=atoi(argv[1]);
    printf("%d\n",id);

    int data[5];
    int sta[5];

    char writefifo[30]="Child0_W";
    char readfifo[30]="Child0_R";

    writefifo[5]=48+id;
    readfifo[5]=48+id;

    char fname[25]="data_1.txt";
    fname[5]=48+id;
    if (id>0)
    {
        FILE *fileptr;

        fileptr=fopen(fname,"r");

        for (int i=0 ; i<5 ; i++)
        {
            fscanf(fileptr,"%d",&data[i]);
            sta[i]=1;
        }

        fclose(fileptr);
    }

    int fdwrite=open(writefifo,O_WRONLY);
    char writebuf[80];
    sprintf(writebuf,"500");
    printf("In child process %d : %s\n",id,writebuf);
    write(fdwrite,writebuf,sizeof(writebuf));

    close(fdwrite);
    

    if (id==0)
    {
        return 0;
    }

    while(1)
    {
        int fdread=open(readfifo,O_RDONLY);
        char readbuf[80];
        int read_bytes=read(fdread, readbuf, 5);
        readbuf[read_bytes]='\0';
        printf("In child Process %d : %d, %s\n",id,read_bytes,readbuf);

        int op=atoi(readbuf),pivot;
        close(fdread);

        if(id==0) return 0;

        if(op==REQUEST)
        {
            printf("REQUEST\n");
            int key=0;

            srand(time(0));
            key=rand()%5;

            key=(sta[key]==1) ? data[key] : -1;

            char temp[10];
            sprintf(temp,"%d",key);

            int fdwrite=open(writefifo,O_WRONLY);
            char writebuf[80];
            sprintf(writebuf,"%d",key);
            printf("In child process %d : %s\n",id,writebuf);
            write(fdwrite,writebuf,sizeof(writebuf));

            close(fdwrite);
        }
        else if(op==PIVOT)
        {
            int fdwrite=open(writefifo,O_WRONLY);
            char writebuf[80];
            sprintf(writebuf,"1");
            printf("In child process %d : %s\n",id,writebuf);
            write(fdwrite,writebuf,sizeof(writebuf));

            close(fdwrite);

            int fdread=open(readfifo,O_RDONLY);
            char readbuf[80];
            int read_bytes=read(fdread,readbuf,5);
            readbuf[read_bytes]='\0';
            printf("In child Process %d : %d, %s\n",id,read_bytes,readbuf);

            pivot=atoi(readbuf);

            close(fdread);

            int count=0;

            for (int t=0 ; t<5 ; t++)
            {
                if (sta[t]==1)
                {
                    count+=(data[t]>pivot);
                }
            }

            fdwrite=open(writefifo,O_WRONLY);
            
            sprintf(writebuf,"%d",count);
            printf("In child process %d : %s\n", id, writebuf);
            write(fdwrite,writebuf,sizeof(writebuf));

            close(fdwrite);


        }
        else if(op==SMALL)
        {

            for(int i=0 ; i<5 ; i++)
            {
                if (sta[i] && data[i] < pivot)
                sta[i]=0;
            }

            fdwrite=open(writefifo,O_WRONLY);
            
            sprintf(writebuf,"1");
            printf("In child process %d : %s\n",id,writebuf);
            write(fdwrite,writebuf,sizeof(writebuf));

            close(fdwrite);
        }
        else if (op==LARGE)
        {
             for (int i=0 ; i<5 ; i++)
            {
                if (sta[i] && data[i] > pivot)
                sta[i] = 0;
            }

            fdwrite=open(writefifo,O_WRONLY);
            
            sprintf(writebuf,"1");
            printf("In child process %d : %s\n", id,writebuf);
            write(fdwrite,writebuf,sizeof(writebuf));

            close(fdwrite);
        }
        else if(op==KILL)
        {
            printf("CHILD %d has been killed.\n", id);
            break;
        }
    }

    printf("\n");
}