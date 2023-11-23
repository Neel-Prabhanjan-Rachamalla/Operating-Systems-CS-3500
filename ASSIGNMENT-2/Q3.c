#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	//Two ends of a pipe.
	int pp[2];
	
	char str1[100000];
	
	pid_t process;
	
	//Piping.
	pipe(pp);
	
	scanf("%s",str1);
	
	//Creating a child process.
	process=fork();
	
	if(process<0)
	{
		printf("Fork Failed !\n");
		
		return 0;
	}
	//Child process.
	else if(process==0)
	{
		close(pp[0]);
		
		printf("Printing from child : %s\n",str1);
		//Writing from one end to other.
		write(pp[1],str1,strlen(str1)+1);
		
		close(pp[1]);
		
		exit(0);
	}
	//Parent process.
	else
	{
		wait(NULL);
		
		close(pp[1]);
		
		char str2[100000];
		
		//Reading string from one end to another.
		read(pp[0],str2,100000);
		
		printf("Printing from parent : %s\n",str2);
		
		close(pp[0]);
	}
	
	return 0;	
}
