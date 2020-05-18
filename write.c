#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

int writeImage(const char* source, const char* dest)
{
	int input = 0;
	int output = 0;
	off_t bytesCopied = 0;
	int result = 0;
	struct stat fileinfo = { 0 };

	input = open(source, O_RDONLY);
	output = creat(dest, 0660);

	if(input == -1 || output == -1)
	{
		perror("writeImage Failed!");
		return -1;
	}

	fstat(input, &fileinfo);

	result = sendfile(output, input, &bytesCopied, fileinfo.st_size);

	close(input);
	close(output);

	if(result == -1)
	{
		perror("writeImage Failed!");
		return -1;
	}

	return 0;
}
