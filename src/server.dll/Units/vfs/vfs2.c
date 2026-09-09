#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int __cdecl vfs_WriteBufferLocked(void*, int, int, int);
void __cdecl free(void*);
int __cdecl vfs_FreeGameSubobject(void*);
int __cdecl vfs_CleanupSubobject(void*);
int __cdecl deflate(void*, int);  /* zlib deflate — the original calls it directly */
int __cdecl _crt_locked_call4a(void*, int, int, void*);
int __cdecl crt_locked_putc(int, void*);
unsigned int __cdecl vfs_GetByte(int*);
unsigned int __cdecl vfs_FlushStream(int, int);
void __cdecl vfs_WriteUint32LE(int, unsigned int);
int __cdecl vfs_CloseStream(void*);
void __cdecl vfs_EntityCleanup(char*);

void __cdecl vfs_StreamClose(int);
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
void __cdecl vfs_FreeSubobj(void*);
int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_ReadUint32BE(int);
int __cdecl vfs_FlushAndClose(int);

int __cdecl ReadVfsCompressed(int, int, unsigned int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: SERVER 0x10003b90
// vfs_FlushStream

unsigned int __cdecl vfs_FlushStream(int stream, int dest)
{
	int done;
	int write_result;
	int remaining;

	done = 0;
	if (stream == 0 || *(char*) (stream + 0x5c) != 'w') {
		return 0xFFFFFFFE;
	}
	*(int*) (stream + 4) = 0;
	do {
		remaining = 0x4000 - *(int*) (stream + 0x10);
		if (remaining != 0) {
			write_result = _crt_locked_call4a(*(void**) (stream + 0x48), 1, remaining, *(void**) (stream + 0x40));
			if (write_result != remaining) {
				*(int*) (stream + 0x38) = -1;
				return (unsigned int) -1;
			}
			*(int*) (stream + 0x10) = 0x4000;
			*(int*) (stream + 0x0c) = *(int*) (stream + 0x48);
		}
		if (done) {
			break;
		}
		write_result = deflate((void*) stream, (int) dest);
		*(int*) (stream + 0x38) = write_result;
		if (remaining == 0 && write_result == -5) {
			*(int*) (stream + 0x38) = 0;
		}
		if (*(int*) (stream + 0x10) == 0 && *(int*) (stream + 0x38) != 1) {
			done = 0;
		}
		else {
			done = 1;
		}
	} while (*(int*) (stream + 0x38) == 0 || *(int*) (stream + 0x38) == 1);
	if (*(unsigned int*) (stream + 0x38) != 1) {
		return *(unsigned int*) (stream + 0x38);
	}
	return 0;
}

/* Reads a 32-bit big-endian integer from the VFS stream and
 * converts to host byte order. */

// FUNCTION: SERVER 0x10003C50
// vfs_ReadUint32BE

int __cdecl vfs_ReadUint32BE(int stream)
{
	int result;
	int last;

	result = vfs_GetByte((int*) stream);
	result = result + (vfs_GetByte((int*) stream) << 8);
	result = result + (vfs_GetByte((int*) stream) << 16);
	last = vfs_GetByte((int*) stream);
	if (last == -1) {
		*(unsigned int*) (stream + 0x38) = 0xfffffffd;
	}
	return (last << 24) + result;
}

/* Flushes a VFS stream and closes it. Combines vfs_FlushStream
 * and vfs_CloseStream into a single operation. */

// FUNCTION: SERVER 0x10003CA0
// vfs_FlushAndClose

int __cdecl vfs_FlushAndClose(int stream)
{
	int flush_result;

	if (stream == 0) {
		return -2;
	}
	if (*(char*) (stream + 0x5c) == 'w') {
		flush_result = vfs_FlushStream(stream, 4);
		if (flush_result == 0) {
			vfs_WriteUint32LE(*(int*) (stream + 0x40), *(unsigned int*) (stream + 0x4c));
			vfs_WriteUint32LE(*(int*) (stream + 0x40), *(unsigned int*) (stream + 8));
		}
	}
	return vfs_CloseStream((void*) stream);
}

/* Writes a 32-bit little-endian integer to the VFS stream. */

// FUNCTION: SERVER 0x10003CF0
// vfs_WriteUint32LE

void __cdecl vfs_WriteUint32LE(int stream, unsigned int value)
{
	int i;

	i = 4;
	do {
		crt_locked_putc(value & 0xff, (void*) stream);
		value = value >> 8;
		i = i - 1;
	} while (i != 0);
	return;
}

/* Destroys a VFS entity (file/directory node). Frees the
 * entity's name string and the entity struct itself. */

