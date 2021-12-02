#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*ret;
	
	ret= getenv("HOME");
	if (!ret)
	{
		printf("Can't find the env variable!\n");
		return (1);
	}
	printf("%s\n", getenv("HOME"));
	return (0);
}

//null-terminated 문자열 형태로 환경변수의 값을 리턴한다. 
//해당 환경변수값이 없을 경우, NULL 리턴.