#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int	main(void)
{
	struct stat	stat_ptr;
	int			fd;

	fd = open("txt_link", O_RDONLY);
	if (fd == -1)
	{
		printf("open() has failed.\n");
		return (-1);
	}
	if (fstat(fd, &stat_ptr) == -1)
	{
		printf("calling stat() failed.\n");
		return (-1);
	}
	close(fd);
	printf("File type: "); 
	switch (stat_ptr.st_mode & S_IFMT) 
	{
		case S_IFBLK: printf("block device\n"); break; 
		case S_IFCHR: printf("character device\n"); break; 
		case S_IFDIR: printf("directory\n"); break; 
		case S_IFIFO: printf("FIFO/pipe\n"); break; 
		case S_IFLNK: printf("symlink\n"); break; 
		case S_IFREG: printf("regular file\n"); break; 
		case S_IFSOCK: printf("socket\n"); break; 
		default: printf("unknown?\n"); break; 
	} 
	printf("I-node number: %ld\n", (long) stat_ptr.st_ino); 
	printf("Mode: %lo (octal)\n", (unsigned long) stat_ptr.st_mode); 
	printf("Link count: %ld\n", (long) stat_ptr.st_nlink); 
	printf("Ownership: UID=%ld GID=%ld\n", (long) stat_ptr.st_uid, (long) stat_ptr.st_gid); 
	printf("Preferred I/O block size: %ld bytes\n", (long) stat_ptr.st_blksize); 
	printf("File size: %lld bytes\n", (long long) stat_ptr.st_size); 
	printf("Blocks allocated: %lld\n", (long long) stat_ptr.st_blocks);
	printf("Last status change: %s", ctime(&stat_ptr.st_ctime)); 
	printf("Last file access: %s", ctime(&stat_ptr.st_atime)); 
	printf("Last file modification: %s", ctime(&stat_ptr.st_mtime));
	return (0);
}

//int	fstat(int fildes, struct stat *buf);