#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    //Inititializing the current directory with length of maximum possible path.
    char pwd[PATH_MAX];
    
    //Getting the current directory.
    getcwd(pwd,sizeof(pwd));
    
    //Running commands.
    while(1)
    {
        printf("%s> ",pwd);

        char command[10];

        gets(command);
    
    	//CLEAR.
        if(!strcmp(command,"clear"))
        {
            system("cls");
            
            //Saving command.	
            FILE* fptr;
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);
        }
        //PWD.
        else if(!strcmp(command,"pwd"))
        {
            printf("Current Directory : %s\n",pwd);
            
            //Saving command.
            FILE* fptr;
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);
        }
        //MKDIR.
        else if(!strcmp(command,"mkdir"))
        {
            if (!mkdir("dir"))
            {
                printf("Directory created successfully.\n");
            }
            else
            {
                printf("Directory already exists !!\n");
            }
            
            //Saving command.
            FILE* fptr;
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);
        }
        //RMDIR.
        else if(!strcmp(command,"rmdir"))
        {
            if(!rmdir("dir"))
            {
                printf("Directory removed successfully.\n");
            }
            else
            {
                printf("Directory doesnt exist\n");
            }
            
            //Saving command.
            FILE* fptr;
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);
        }
        //LS or LS -l.
        else if(!strcmp(command,"ls") || !strcmp(command,"ls -l"))
        {
            struct stat file_stats;
            DIR *d;
            struct dirent *dir;
            d=opendir(".");
            if (d)
            {
                while ((dir = readdir(d))!=NULL)
                {
                    printf("File/Folder Name : %s\n",dir->d_name);
                    //Printing stats if -l is given.
                    if (!strcmp(command,"ls -l") && (stat(dir->d_name,&file_stats))!=-1)
                    {
                        printf("\tDevice                :    %lld\n",file_stats.st_dev);
                        printf("\tProtection            :    %o\n",file_stats.st_mode);
                        printf("\tUser ID               :    %d\n",file_stats.st_uid);
                        printf("\tGroup ID              :    %d\n",file_stats.st_gid);
                        printf("\tTotal Size            :    %ld bytes\n",file_stats.st_size);
                        printf("\tLast Access Time      :    %s",ctime(&file_stats.st_atime));
                        printf("\tLast Change Time      :    %s",ctime(&file_stats.st_ctime));
                    }
                    printf("\n");
                }

                closedir(d);
            }
            
            //Saving command.
            FILE* fptr;
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);
        }
        //HISTORY.
        else if(!strcmp(command,"history"))
        {
            //Outputting saved commands.
            FILE* fptr;
            fptr=fopen("commands.txt","r+");
            char c;
            while ((c=getc(fptr))!=EOF) printf("%c",c);
            fclose(fptr);
		
	     //Saving command.
            fptr=fopen("commands.txt","a+");
            fputs(command,fptr);
            fputc('\t',fptr);
            fclose(fptr);

            printf("\n");
        }
        //EXIT.
        else if(!strcmp(command,"exit"))
        {
            printf("Exiting Shell ...\n");
            //Delete saved commands and exit.
            remove("commands.txt");

            break;
        }
    }

    return 0;
}
