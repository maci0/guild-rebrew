#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl _errno(void);
int __cdecl vfs_WriteBufferLocked(void*, int, int, int);
void __cdecl free(void*);
int __cdecl vfs_FreeGameSubobject(void*);
int __cdecl vfs_CleanupSubobject(void*);
int __cdecl vfs_CompressBlock(void*, int);
int __cdecl vfs_LockedFwrite(void*, int, int, void*);
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

int __cdecl vfs_ReadCompressed(int, int, unsigned int);

/* TL-side stream dispatcher. Shared name with the server twin
 * (SERVER vfs_GetByte), per-build body: null->-2 guard, callback slots,
 * 'w'/'r' mode dispatch, tag check, final notify; returns edi.
 * 82/177: head 0..41 byte-exact; residual is downstream branch fallout. */

// FUNCTION: GOLDTL 0x45f2c0
// SIZE: 192
// vfs_GetByte

void __cdecl fcn_0064dfda(void* p);
int __cdecl fcn_0045df20(int* stream);
int __cdecl fcn_00461560(int* stream);
int __cdecl fcn_0064e1fd(void* p);
int __cdecl fcn_0064d6f8(void);

int __cdecl vfs_GetByte(int* stream)
{
	int result;

	result = 0;
	if (stream == 0) {
		return -2;
	}
	if (stream[0x14] != 0) {
		fcn_0064dfda((void*) stream[0x14]);
	}
	if (stream[7] != 0) {
		if (*(unsigned char*) ((char*) stream + 0x5c) == 0x77) {
			fcn_0045df20(stream);
		}
		else if (*(unsigned char*) ((char*) stream + 0x5c) == 0x72) {
			result = fcn_00461560(stream);
		}
	}
	if (stream[0x10] != 0) {
		fcn_0064e1fd((void*) stream[0x10]);
		if (fcn_0064d6f8() != 0x1d) {
			result = -1;
		}
	}
	if (stream[0xe] != 0) {
		fcn_0064dfda((void*) stream[0xe]);
	}
	if (stream[0x12] != 0) {
		fcn_0064dfda((void*) stream[0x12]);
	}
	if (stream[0x15] != 0) {
		fcn_0064dfda((void*) stream[0x15]);
	}
	fcn_0064dfda(stream);
	return result;
}

/* Closes a VFS stream and releases associated resources.
 * Frees internal buffers and removes from open stream list. */

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
		close_result = fflush(*(FILE**) ((int) stream + 0x40));
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

