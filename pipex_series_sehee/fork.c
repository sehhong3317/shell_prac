#include <unistd.h>
#include <stdio.h>
//fork, pipe, dup, dup2, wait, waitpid, exit, execve, unlink

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("failed to call fork().\n");
	else if (!pid)	//자식 부모세스(새로 생성한 프로세스)
	{	
		printf("hello. I'm a child process.\n");
	}
	else			//부모 프로세스
	{	
		sleep(5);
		printf("I'm a parent process.\n");
	}
	return (0);
}