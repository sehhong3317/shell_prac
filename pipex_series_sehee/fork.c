#include <unistd.h>

//fork, pipe, dup, dup2, wait, waitpid, exit, execve, unlink

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		
	}
	else if (!pid)
	{
		printf("hello. I'm a child process.\n");
		return (0);
	}

}