#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int* __cdecl vfs_GetErrnoPtr(void);
int __cdecl vfs_WriteBufferLocked(void*, int, int, int);
void __cdecl m_FreeHeapLocked(void*);
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

int __cdecl ReadVfsCompressed(int, int, unsigned int);

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

// FUNCTION: SERVER 0x10003820
// vfs_GetByte

__declspec(naked) unsigned int __cdecl vfs_GetByte(int* stream)
{
	(void) stream;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		mov eax, dword ptr [esi + 0x3c]
		test eax, eax
		je L_have_buf
		or eax, 0xffffffff
		pop esi
		ret
	L_have_buf:
		mov eax, dword ptr [esi + 4]
		test eax, eax
		jne L_read
		call vfs_GetErrnoPtr
		mov dword ptr [eax], 0
		mov eax, dword ptr [esi + 0x40]
		mov ecx, dword ptr [esi + 0x44]
		push eax
		push 0x4000
		push 1
		push ecx
		call vfs_WriteBufferLocked
		add esp, 0x10
		mov dword ptr [esi + 4], eax
		test eax, eax
		jne L_refilled
		mov edx, dword ptr [esi + 0x40]
		mov dword ptr [esi + 0x3c], 1
		or eax, 0xffffffff
		test byte ptr [edx + 0xc], 0x20
		je L_done
		mov dword ptr [esi + 0x38], eax
		pop esi
		ret
	L_refilled:
		mov eax, dword ptr [esi + 0x44]
		mov dword ptr [esi], eax
	L_read:
		mov eax, dword ptr [esi + 4]
		xor ecx, ecx
		dec eax
		mov dword ptr [esi + 4], eax
		mov eax, dword ptr [esi]
		mov cl, byte ptr [eax]
		inc eax
		mov dword ptr [esi], eax
		mov eax, ecx
	L_done:
		pop esi
		ret
	}
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
		m_FreeHeapLocked(*(void**) ((int) stream + 0x50));
	}
	if (*(int*) ((int) stream + 0x1c) != 0) {
		if (*(char*) ((int) stream + 0x5c) == 'w') {
			result = vfs_FreeGameSubobject(stream);
		}
		else if (*(char*) ((int) stream + 0x5c) == 'r') {
			result = vfs_CleanupSubobject(stream);
		}
	}
	if (*(FILE**) ((int) stream + 0x40) != 0) {
		close_result = fclose(*(FILE**) ((int) stream + 0x40));
		if (close_result != 0) {
			errno_ptr = vfs_GetErrnoPtr();
			if (*errno_ptr != 0x1d) {
				result = -1;
			}
		}
	}
	if (*(int*) ((int) stream + 0x38) < 0) {
		result = *(int*) ((int) stream + 0x38);
	}
	if (*(void**) ((int) stream + 0x44) != 0) {
		m_FreeHeapLocked(*(void**) ((int) stream + 0x44));
	}
	if (*(void**) ((int) stream + 0x48) != 0) {
		m_FreeHeapLocked(*(void**) ((int) stream + 0x48));
	}
	if (*(void**) ((int) stream + 0x54) != 0) {
		m_FreeHeapLocked(*(void**) ((int) stream + 0x54));
	}
	m_FreeHeapLocked(stream);
	return result;
}

/* Flushes pending write data from a VFS stream buffer to
 * disk. Takes stream handle and flush mode parameters. */

