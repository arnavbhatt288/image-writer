#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <linux/fs.h?
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/ioctl.h>   

#include "size.h"

unsigned long diskSize(const char* path)
{
	int fd = 0;
	int result = 0;
	unsigned long numblocks = 0;

	fd = open(path, O_RDONLY);

	if(fd == -1)
	{
		perror("diskSize failed!");
		return 0;
	}

	result = ioctl(fd, BLKGETSIZE, &numblocks);
	close(fd);

	if(result == -1 || fd == -1)
	{
		perror("diskSize failed!");
		return 0;
	}	

	return numblocks * 512;
}

off_t fileSize(const char* filename)
{
	struct stat st;
	int result = 0;

	result = stat(filename, &st);
	
	if (result != 0)
	{
		perror("fileSize failed!");
		return 0;
	}

	return st.st_size;
}
