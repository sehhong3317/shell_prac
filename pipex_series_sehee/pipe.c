#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

//자식 프로세스가 보낸 메세지를 부모 프로세스가 읽는다!

int	main(void)
{
	pid_t	pid;
	int		pipe_fds[2];
	int		ret;
	char	msg[] = "Greeting from your child:)!";
	char	buffer[100];

	ret = pipe(pipe_fds);
	if (ret == -1)
		printf("calling pipe() has failed.\n");
	//fork로 연결하기 전에 pipe를 열어줘서 pipe_fds[0]에는 파이프의 read 부분연결.
	//pipe_fds[1]에는 파이프의 write 부분을 연결할 fd를 기록. 
	pid = fork();
	//자식프로세스는 부모 프로세스의 fd를 복사본을 가지므로, 위에서 부모 프로세스가 연 파이프를
	//자식 프로세스도 똑같이 참조한다. (man fork) 
	//따라서 이 파이프를 통해, 두 프로세스가 파이프를 매개로 서로 통신을 할 수 있게 된 것. 
	if (pid == -1)
		printf("failed to call fork().\n");
	else if (!pid)	//자식 프로세스
	{
		close(pipe_fds[0]);
		//파이프는 단일 방향 통신만 가능하다! 
		//여기서는 자식 프로세스가 write한 내용을 부모프로세스가 read하게 할 것임.
		//따라서, 자식 프로세스의 read fd는 닫아줘야 함.
		write(pipe_fds[1], msg, strlen(msg) + 1);
		//파이프에 전달할 문자열을 write한다.
		return (0);
	}
	else	//부모 프로세스
	{
		close(pipe_fds[1]);
		//부모 프로세스는 읽기만 역할!
		//(파이프는 단일 방향 통신만 가능하므로 양방향통신을 원할 경우, 파이프를 두개 열어야 한다!)
		//그러므로 부모 프로세스의 write fd는 닫아준다.
		wait(NULL);
		//자식 프로세스를 기다려준다. 이때 자식 프로세스의 exit status를 여기서는 쓰지 않아서 
		//int *status를 사용하지 않았음.
		read(pipe_fds[0], buffer, sizeof(buffer));
		printf("I got message from my child: %s\n", buffer);
	}
	return (0);
}