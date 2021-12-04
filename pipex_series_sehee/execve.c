#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(void)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		infile_fd;
	int		ret;
	char	*cmd_arg[] = {"/usr/bin/grep", "mini", 0};

	pid = fork();
	if (pid == -1)
		printf("failed to call fork().\n");
	else if (!pid)	//자식 프로세스
	{
		infile_fd = open("infile.txt", O_RDONLY);
		if (infile_fd == -1)
		{
			printf("open() has failed.\n");
			exit (-1);
		}
		ret = dup2(infile_fd, 0);
		if (ret == -1)
		{	
			printf("dup2() has failed.\n");
			exit(-1);
		}
		close(infile_fd);
		//이제  fd 0은 사용자의 입력값이 아닌, infile.txt의 내용이 input이 된다.
		execve("/usr/bin/grep", cmd_arg, 0);
		printf("If you see this, your execve() has failed.\n");
	}
	else	//부모 프로세스
	{
		wait(NULL);
	}
	return (0);
}