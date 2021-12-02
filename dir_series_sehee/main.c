#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <sys/types.h> 
#include <dirent.h> 

int main(void) 
{
	DIR *dir_ptr = NULL;
	struct dirent *file = NULL;
	char home[1024];

	strncpy(home, getenv("HOME"), sizeof(home)); 
	/* 목록을 읽을 디렉토리명으로 DIR *를 return 받습니다. */ 
	printf("%s\n", home);
	if((dir_ptr = opendir(home)) == NULL)
	{ 
		fprintf(stderr, "%s directory 정보를 읽을 수 없습니다.\n", home); 
		return -1; 
	} /* 디렉토리의 처음부터 파일 또는 디렉토리명을 순서대로 한개씩 읽습니다. */ 
	while((file = readdir(dir_ptr)) != NULL) 
	{ 
		/* * struct dirent *의 구조체에서 d_name 이외에는 * 시스템마다 항목이 없을 수 있으므로 무시하고 이름만 사용합니다. */ 
		printf("%s\n", file->d_name); 
	} 
	/* open된 directory 정보를 close 합니다. */ 
	closedir(dir_ptr); 
	return 0; 
}

//DIR *opendir(const char *filename);
//리턴된 DIR를 이요해, filename의 하위에 있는 파일명 또는 디렉토리명 등의 목록을 얻을 수 있다.
//filename: 절대경로 또는 현재 디렉토리의 상대 경로
//성공시, NULL이 아닌 값 리턴. 실패시, NULL 발생 그리고 errno 셋팅됨.

//struct dirent *readdir(DIR *dirp);
//디렉토리의 하위에 있는 파일 및 디렉토리 정보를 한 건 읽음. 
//readdir(3)에 대해서 1회 호출에 1건의 정보를 반환함.
//읽는 순서는 시간 순서, 파일명 순서, 파일 크기 등 어떤 기준이 없으므로 기본적으로 sorting이 되어 있지 않음.
//더 이상 읽을 정보가 없거나 에러 발생시, NULL 반환. 상세한 오류는 errno에 저장.
//readdir()이 NULL을 리턴했는데 디렉토리 끝인지 에러인지를 구분하고 싶다면, 호출전에 errno를 0으로 지우고 호출하면 
//디렉토리 끝으로 NULL을 리턴한 경우에는 errno값이 0으로 유지되므로 에러를 구분할 수 있습니다.

//int closedir(DIR *dirp);
//정상이면 0, 실패면 -1을 리턴하고 errno 셋팅함.
