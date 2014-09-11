#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int magic;
	int files;
} pak_meta;

typedef struct
{
	char name[64];
	int offset;
	int size;
} file_header;

void _err(const char* str)
{
	printf("err: %s\n", str);
	exit(1);
}

typedef struct
{
	FILE *fptr;
	pak_meta meta;
	file_header *headers;
} pak_file;
pak_file pak_file_zero = {NULL, {0,0}, NULL};
pak_file pak;

typedef struct
{
	unsigned int start;
	unsigned int size;
	unsigned int offset;
} pak_handle;

void pak_init()
{
	pak = pak_file_zero;
	pak.fptr = fopen("audio.pak", "rb");
	if(!pak.fptr)
		_err("Could not open file");
	int readsize;
	readsize = fread(&pak.meta, sizeof(pak_meta), 1, pak.fptr);
	if(readsize != 1)
		_err("Failed to read meta");
	if(pak.meta.magic != 0xd1ed)
		_err("Magic number wrong");
	pak.headers = calloc(pak.meta.files, sizeof(file_header));
	readsize = fread(pak.headers, sizeof(file_header), pak.meta.files, pak.fptr);
	if(readsize != pak.meta.files)
		_err("Failed to read headers");

}
void pak_shutdown()
{
	fclose(pak.fptr);
	free(pak.headers);
	pak = pak_file_zero;
}

int pak_file_open(const char *name, int unicode, unsigned int *filesize, void **handle, void **userdata)
{
	int i;
	for(i=0; i<pak.meta.files; i++)
	{
		if(strncmp(name, pak.headers[i].name, sizeof(pak.headers[i].name)) != 0)
			continue;
		*filesize = pak.headers[i].size;
		pak_handle* h = malloc(sizeof(pak_handle));
		h->start = pak.headers[i].offset;
		h->size = pak.headers[i].size;
		h->offset = 0;
		*handle = (void*)h;
		return 0;
	}
	return -1;
}
int pak_file_close(void *handle, void *userdata)
{
	free(handle);
}
int pak_file_read(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread, void *userdata)
{
	pak_handle* h = (pak_handle*)handle;
	fseek(pak.fptr, h->start+h->offset, SEEK_SET);
	int to_read = sizebytes;
	if(h->size - h->offset < to_read)
		to_read = h->size - h->offset;
	*bytesread = fread(buffer, 1, to_read, pak.fptr);
}
int pak_file_seek(void *handle, unsigned int pos, void *userdata)
{
	pak_handle* h = (pak_handle*)handle;
	h->offset = pos;
}

void main()
{
	pak_init();

	unsigned int filesize;
	void* handle;
	pak_file_open("pak.py", 0, &filesize, &handle, NULL);
	char* buffer = malloc(filesize);
	int bytes_read;
	pak_file_read(handle, buffer, filesize, &bytes_read, NULL);
	printf("%s", buffer);
	free(buffer);
	pak_shutdown();
}
