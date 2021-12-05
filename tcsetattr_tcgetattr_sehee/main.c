#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios org_term;
struct termios new_term;

// org_term에 초기 터미널 세팅 저장
void save_input_mode(void)
{
	tcgetattr(0, &org_term); // STDIN으로부터 터미널 속성을 받아온다
}

// new_term에 원하는 터미널 속성 설정
void set_input_mode(void)
{
	tcgetattr(0, &new_term); // STDIN으로부터 터미널 속성을 받아온다
	new_term.c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
	new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
	new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
	tcsetattr(0, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

// 기존의 터미널 세팅으로 다시 변경
void reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

int main(void)
{
	int ch = 0;
	int idx = -1;

	save_input_mode();
	set_input_mode();
	while (read(0, &ch, 1) > 0)
	{
		if (ch == 4)
		{
			if (idx == -1)
				exit(0);
			else
				continue;
		}
		else if (ch == 127)
		{
			if (idx >= 0)
			{
				--idx;
				write(0, "\b \b", 3);
			}
		}
		else if (ch == '\n')
			break;
		else
		{
			++idx;
			write(0, &ch, sizeof(int));
		}
		ch = 0;
	}
	reset_input_mode();
	return (0);
}