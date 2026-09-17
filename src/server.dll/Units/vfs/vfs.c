#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl _errno(void);
void __cdecl free(void*);
unsigned int __cdecl vfs_GetByte(int*);
int __cdecl vfs_CloseStream(void*);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: SERVER 0x10003820
// vfs_GetByte

unsigned int __cdecl vfs_GetByte(int* stream)
{
	int* errno_ptr;
	int bytes_read;

	if (stream[0xf] != 0) {
		return (unsigned int) -1;
	}
	if (stream[1] == 0) {
		errno_ptr = _errno();
		*errno_ptr = 0;
		bytes_read = (int) fread((void*) stream[0x11], 1, 0x4000, (FILE*) stream[0x10]);
		stream[1] = bytes_read;
		if (bytes_read == 0) {
			stream[0xf] = 1;
			if ((*(unsigned char*) (stream[0x10] + 0xc) & 0x20) != 0) {
				stream[0xe] = -1;
			}
			return (unsigned int) -1;
		}
		stream[0] = stream[0x11];
	}
	/* The read cursor is post-incremented in place through a pointer alias
	 * of stream[0]. Copying it into a local first makes MSVC6 hold the
	 * cursor in ecx and zero-extend the byte into eax, which loses the
	 * target's reuse of eax for both the count temp and the cursor. */
	stream[1] = stream[1] - 1;
	return *(*(unsigned char**) &stream[0])++;
}

/* Closes a VFS stream and releases associated resources.
 * Frees internal buffers and removes from open stream list. */

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

