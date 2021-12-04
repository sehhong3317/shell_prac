#include <unistd.h> 
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>

int	main(void)
{
	char	path[1024];

	if (getcwd(path, 1024) == NULL)
		printf("getcwd() has failed.\n%s\n", strerror(errno));
	printf("%s\n", path);
	return (0);
}

//char *getcwd(char *buf, size_f size);
//현재 디렉토리의 절대경로를 null-terminated 문자열로 반환함. size는 buf의 크기를 지칭함.
//만약 buf가 NULL일 경우, buf와 size와 관계없이 malloc()으로 메모리를 할당하므로 이후 free 필요!
//성공할 경우, path의 주소를 반환. 실패시, NULL 반환과 동시에 errno에 에러코드 저장.