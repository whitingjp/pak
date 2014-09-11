#ifndef __PAK__
#define __PAK__

#define MAX_FILENAME (64)

void pak_init(const char* packname, void(*err)(const char* str));
void pak_shutdown();
int pak_file_open(const char *name, unsigned int *filesize, void **handle);
int pak_file_close(void *handle);
int pak_file_read(void *handle, void *buffer, unsigned int sizebytes, unsigned int *bytesread);
int pak_file_seek(void *handle, unsigned int pos);

#endif // __PAK__