#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("current working directory is %s.\n", cwd);
	printf("---------------------------------------\n");
	// if (chdir("hello") == -1)	//상대경로(실패)
	// if (chdir("dummy_folder")== -1)	//상대경로(성공)
	// if (chdir("..") == -1)	//상대경로(성공)
	if (chdir("/usr/local") == -1)	//절대경로(성공)
	{
		printf("failed to move\n");
		return (1);
	}
	printf("chdir() success.\n");
	cwd = NULL;
	free(cwd);
	cwd = getcwd(NULL, 0);
	printf("current working directory is %s.\n", cwd);
	cwd = NULL;
	free(cwd);
	return (0);
}
