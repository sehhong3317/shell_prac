#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("failed to call fork().\n");
	else if (!pid)	//자식 부모세스(새로 생성한 프로세스)
	{	
		printf("I'm a child process.\n");
		printf("my pid is %d.\n", getpid());
		printf("Pid of my parent is %d.\n", getppid());
		exit(5);
	}
	else			//부모 프로세스
	{	
		wait(&status);	//자식 프로세스가 먼저 진행되도록!	//waitpid(-1, &status, 0)과 같음.
		printf("----------------------------------\n");
		if (WIFEXITED(status))
		{
			printf("Exit of child success.\n");
			printf("Exit status of my child is %d.\n", WEXITSTATUS(status));
		}
		else
		{	
			printf("Exit of child failed.\n");			
			return (-1);
		}
		printf("I'm a parent process.\n");
		printf("my pid is %d.\n", getpid());
		printf("Pid of my child is %d.\n", pid);
		return (0);
	}
}