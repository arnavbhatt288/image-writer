#include <stdio.h>  
#include <unistd.h>
#include <stdbool.h>

#include "size.h"
#include "write.h"

int main(int argc, char *argv[])
{
	int opt;
	char* drive = NULL;
	char* img_dir = NULL;
	unsigned long long drive_size = 0;
	off_t img_size = 0;

	if(argc == 1)
	{
		printf("No arguments provided\n");
		printf("Give arg \"-h\" for help\n");
		return 0;
	}

	while((opt = getopt(argc, argv, "d:i:h::")) != -1)
	{
		switch(opt)
		{
			case 'd':
				drive = optarg;
				break;

			case 'i':
				img_dir = optarg;
				break;
			case 'h':
				printf("Usage -\n");
				printf("./program-name -d \"/dev/sdX\" -i \"path/to/img/file\"\n");
				return 0;

			case '?':
				printf("Give arg \"-h\" for help\n");
				return 0;
		}
	}

	
	drive_size = diskSize(drive);

	if(drive_size == 0)
	{
		printf("Exiting program...\n");
		return -1;
	}


	img_size = fileSize(img_dir);

	if(img_size == 0)
	{
		printf("Exiting program...\n");
		return -1;
	}

	if(img_size > drive_size)
	{
		printf("Your drive is too small to write!\nExiting program...\n");
		return 0;
	}

	printf("WARNING: The entire content of your drive will be OVERWRITTEN!\n");
	printf("Press Enter to continue or press Ctrl + C to cancel\n");
	fflush(stdin);
	getchar();

	int result = writeImage(img_dir, drive);

	if(result == -1)
	{
		printf("Exiting program...\n");
		return -1;
	}

	printf("Done.\n");

	return 0;
}
