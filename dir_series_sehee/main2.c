#include <dirent.h>
#include <string.h>
#include <stdio.h>

int	main(void)
{
	struct dirent	*dp;
	DIR				*dirp;
	int				len;
	
	char	*name = "main3.c";
	dirp = opendir(".");
	if (dirp == NULL)
		return (1);
	len = strlen(name);
	while ((dp = readdir(dirp)) != NULL) 
	{
		if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) 
		{
				printf("yes");
				(void)closedir(dirp);
				return (0);
		}
}
closedir(dirp);
return (1);
}