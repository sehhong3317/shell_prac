#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

void check_resource_usage(struct rusage *ru)
{
	struct timeval	*tv;

    printf("=== pid rusage info ===\n");
    tv = &(ru->ru_utime);
    printf("user CPU time used [%ld]sec [%d]usec\n", tv->tv_sec, tv->tv_usec );
    tv = &(ru->ru_stime);
    printf("system CPU time used [%ld]sec [%d]usec\n", tv->tv_sec, tv->tv_usec );
}

int main(void)
{
    pid_t			pid;
	pid_t			reaped_pid;
	int				i;
	int				status;
	struct rusage	r_usage;
	
	pid = fork();
    if(pid < 0)
    {
        perror("fork() has failed.\n");
        return (-1);
    }
	if (!pid)
	{
		printf("[child] pid: %d\n", getpid());
		i = 0;
		while (i++ < 10000)
			write(2, ".", 1);
	}
	else
	{
		printf("[parent] pid of my child: %d\n", pid);
		reaped_pid = wait3(&status, 0, &r_usage);
		if (reaped_pid == pid)
			check_resource_usage(&r_usage);
		else
			printf("wait3() has failed to wait its child.\n");
	}
	return (0);
}