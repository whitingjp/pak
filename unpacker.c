#include "pak.h"

#include <stdio.h>
#include <stdlib.h>

void _err(const char* str)
{
	printf("err: %s\n", str);
	exit(1);
}

void main(int argc, char** argv)
{
	if(argc < 3)
		_err("Usage:\n  ./pak package file");

	pak_init(argv[1], _err);

	unsigned int filesize;
	void* handle;
	int ret = pak_file_open(argv[2], &filesize, &handle);
	if(ret == -1)
		_err("Could not find file in package");
	char* buffer = malloc(filesize);
	int bytes_read;
	pak_file_read(handle, buffer, filesize, &bytes_read);
	printf("%s", buffer);
	free(buffer);
	pak_file_close(handle);
	pak_shutdown();
}