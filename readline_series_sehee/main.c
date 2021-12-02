#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
extern int rl_catch_signals;

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)	
	//다른 rl관련 함수들에게 다음줄로 넘었갔다고 업데이트해주는 역할로, 마치 lseek()함수가 file의
	//offset을 이동시키는 개념과 비슷한 것 같음!단순 업데이트 용도라서 이 함수를 사용하기 전에 
	//개행을 따로 써준다! 
		exit(1);
	rl_replace_line("", 1);
	//현재 커서의 offset을 기준으로 입력받은 문자열은 rl_line_buffer라는 전역변수에 저장된다.
	//void rl_replace_line(const char *text, int clear_undo);
	//이 함수는 rl_line_buffer에 저장된 문자열을 문자열 text로 대체해주고 clear_undo라는 옵션으로
	//undo기능을 위한 undo_list를 초기화 여부를 결정한다!
	rl_redisplay();
	//rl_line_buffer에 저장된 문자열을 prompt와 함께 출력!
	//여기서는 위 rl_replace_line("", 1)을 통해, rl_line_buffer가 빈문자열로 바껴있음.
	//따라서 Ctrl-c를 누르면, 내가 어떤 값을 입력해도 prompt + 빈문자열만 나옴.
}

int		main(void)
{
	int				ret;
	char			*line;

	rl_catch_signals = 0;	
	signal(SIGINT, handler);
	while (true)
	{
		line = readline("input> ");
		if (line)
		{
			ret = strcmp(line, "bye");
			if (ret)
				printf("output> %s\nrl_line_buffer:%s\n", line, rl_line_buffer);
				// rl_line_buffer에는 현재 cursor기준으로 내가 입력한 값만 프린트된다!
			add_history(line);
			free(line);
			line = NULL;
			if (!ret)
				break ;
		}
		else
			return (1);
	}
	return (0);
}

//예제는 쉘같은 prompt 모습을 구현했음.
//근데 ctrl_c 누르면 찐 쉘은 표준입력에 아무것도 안보이는데 이 예제는 ^C가 찍힌다.
//이 부분, 고려해봐야할지도...? 기리님한테 물어봐야징... -> 앗 기리님의 도움으로(rl_catch_signal) 해결!!
