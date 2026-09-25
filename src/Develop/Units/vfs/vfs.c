#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl _errno(void);
void __cdecl free(void*);
unsigned int __cdecl vfs_GetByte(int*);
int __cdecl vfs_CloseStream(void*);

// FUNCTION: GOLDTL 0x45f2c0
// SIZE: 192
// FUNCTION: SERVER 0x100038a0

// vfs_CloseStream

int __cdecl vfs_CloseStream(void* stream)
{
	int close_result;
	int* errno_ptr;
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
			errno_ptr = _errno();
			if (*errno_ptr != 0x1d) {
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

/* Flushes pending write data from a VFS stream buffer to
 * disk. Takes stream handle and flush mode parameters. */
