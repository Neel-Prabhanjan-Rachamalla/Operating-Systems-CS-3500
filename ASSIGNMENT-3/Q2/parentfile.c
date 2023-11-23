#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define REQUEST 100
#define PIVOT 200
#define LARGE 300
#define SMALL 400
#define READY 500
#define KILL 600

int main()
{
    int fdwrite[6];
    int fdread[6];

    char writefifo[30] = "Child0_W";
    char readfifo[30] = "Child0_R";

    for (int i=0 ; i<=5 ; i++)
    {
        writefifo[5]=48+i;
        readfifo[5]=48+i;

        mkfifo(writefifo, 0666);
        mkfifo(readfifo, 0666);
    }

    char id[5];

    for (int i=0 ; i<=5 ; i++)
    {
        sprintf(id,"%d",i);

        char *ch_args[]={id, NULL};
        if (fork()==0)
        {
            execv("./childfile",ch_args);
        }
    }

    for (int i=0 ; i<=5 ; i++)
    {
        writefifo[5]=48+i;
        readfifo[5]=48+i;

        fdread[i]=open(writefifo, O_RDONLY);
        char readbuf[80]="\0";
        int read_bytes=read(fdread[i], readbuf, 4);

        printf("Child %d ready from parent process : \n", i);

        close(fdread[i]);
    }

    printf("Child processes are ready.\n");
    int k = 25/2,val;
    while (1)
    {
        val = -1;
        do
        {
            srand(time(0));

            int i=(rand()%5+1);
            writefifo[5]=48+i;
            readfifo[5]=48+i;
            fdwrite[i]=open(readfifo, O_CREAT | O_WRONLY);
            char writebuf[80]="\0";

            sprintf(writebuf, "100");
            printf("REQUEST to Child %d: \n", i);
            write(fdwrite[i],writebuf,sizeof(writebuf));

            close(fdwrite[i]);

            fdread[i] = open(writefifo, O_RDONLY);
            char readbuf[80] = "\0";
            int read_bytes = read(fdread[i], readbuf, 4);

            close(fdread[i]);
            val = atoi(readbuf);
            printf("Value requestd is %d\n", val);
            
        } while (val == -1);

        int cnt = 0;
        for (int i = 1; i <= 5; i++)
        {
            printf("%d %d\n", i, getpid());
            writefifo[5]=48 + i;
            readfifo[5]=48+i;

            fdwrite[i] = open(readfifo, O_CREAT | O_WRONLY);
            char writebuf[80] = "\0";

            sprintf(writebuf, "200");
            printf("PIVOT to Child %d: \n", i);
            write(fdwrite[i], writebuf, sizeof(writebuf));

            close(fdwrite[i]);

            fdread[i] = open(writefifo, O_RDONLY);
            char readbuf[80] = "\0";
            int read_bytes = read(fdread[i], readbuf, 4);

            close(fdread[i]);

            fdwrite[i] = open(readfifo, O_CREAT | O_WRONLY);

            sprintf(writebuf, "%d", val);
            printf("Sending pivot value %d to child %d : \n",val, i);
            write(fdwrite[i], writebuf, sizeof(writebuf));

            close(fdwrite[i]);

            fdread[i] = open(writefifo, O_RDONLY);

            read_bytes = read(fdread[i], readbuf, 4);

            printf("Response from child %d for pivot : %s\n", i,  readbuf);

            close(fdread[i]);
            cnt += atoi(readbuf);
        }

        if (cnt == k)
        {

            printf("MEDIAN is %d.\n",val);
             for (int i = 1; i <= 5; i++)
            {

                writefifo[5] = 48 + i;
                readfifo[5]=48+i;
                fdwrite[i]=open(readfifo, O_CREAT | O_WRONLY);
                char writebuf[80] = "\0";

                sprintf(writebuf, "600");

                write(fdwrite[i], writebuf, sizeof(writebuf));

                close(fdwrite[i]);

                
            }
            break;
        }

        else if (cnt < k)
        {
            for (int i = 1; i <= 5; i++)
            {
                writefifo[5] = 48 + i;
                readfifo[5]=48+i;
                fdwrite[i]=open(readfifo, O_CREAT | O_WRONLY);
                char writebuf[80] = "\0";

                sprintf(writebuf, "300");
                printf("LARGE to Child%d:\n", i);
                write(fdwrite[i], writebuf, sizeof(writebuf));

                close(fdwrite[i]);

                fdread[i] = open(writefifo, O_RDONLY);
                char readbuf[80] = "\0";
                int read_bytes = read(fdread[i], readbuf, 4);

                close(fdread[i]);
            }

            k=k-cnt;
        }
        else
        {
            for (int i = 1; i <= 5; i++)
            {
                writefifo[5]=48+i;
                readfifo[5]=48+i;
                fdwrite[i]=open(readfifo, O_CREAT | O_WRONLY);
                char writebuf[80] = "\0";

                sprintf(writebuf, "400");
                printf("SMALL to Child %d: \n", i);
                write(fdwrite[i], writebuf, sizeof(writebuf));

                close(fdwrite[i]);

                fdread[i] = open(writefifo, O_RDONLY);
                char readbuf[80] = "\0";
                int read_bytes = read(fdread[i], readbuf, 4);

                close(fdread[i]);
            }
        }
    }

    char a;
    printf("Press ENTER to EXIT.\n");
    scanf("%c",&a);
    return 0;
}
