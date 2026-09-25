// FUNCTION: GOLD 0x463050
// SIZE: 176

/* GOLD twin of vfs_CloseStream (vfs.c): GOLD's CRT keeps errno in a plain
 * global, where GOLDTL and the server call _errno(). */

#include <stdio.h>
#include <stdlib.h>

extern int g_6f2fa4; /* errno */

int __cdecl deflateEnd(void* strm);
int __cdecl inflateEnd(void* strm);

int __cdecl vfs_CloseStream(void* stream)
{
	int close_result;
	int result;

	result = 0;
	if (stream == 0) {
		return -2;
	}
	if (*(void**) ((int) stream + 0x50) != 0) {
		free(*(void**) ((int) stream + 0x50));
	}
	if (*(int*) ((int) stream + 0x1c) != 0) {
		if (*(char*) ((int) stream + 0x5c) == 'w') {
			result = deflateEnd((void*) stream);
		}
		else if (*(char*) ((int) stream + 0x5c) == 'r') {
			result = inflateEnd((void*) stream);
		}
	}
	if (*(FILE**) ((int) stream + 0x40) != 0) {
		close_result = fclose(*(FILE**) ((int) stream + 0x40));
		if (close_result != 0) {
			if (g_6f2fa4 != 0x1d) {
				result = -1;
			}
		}
	}
	if (*(int*) ((int) stream + 0x38) < 0) {
		result = *(int*) ((int) stream + 0x38);
	}
	if (*(void**) ((int) stream + 0x44) != 0) {
		free(*(void**) ((int) stream + 0x44));
	}
	if (*(void**) ((int) stream + 0x48) != 0) {
		free(*(void**) ((int) stream + 0x48));
	}
	if (*(void**) ((int) stream + 0x54) != 0) {
		free(*(void**) ((int) stream + 0x54));
	}
	free(stream);
	return result;
}
