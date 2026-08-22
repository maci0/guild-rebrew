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

// FUNCTION: SERVER 0x10008C80
// vfs_CleanupObject

int __cdecl vfs_CleanupObject(char* obj)
{
	char* sub;
	int result;
	result = 0;
	if (!obj) {
		return -102;
	}
	sub = *(char**) (obj + 0x7c);
	if (!sub) {
		return -102;
	}
	if (!*(int*) (sub + 0x5c)) {
		if (*(int*) (sub + 0x50) != *(int*) (sub + 0x54)) {
			result = -105;
		}
	}
	if (*(int*) sub) {
		free(*(void**) sub);
	}
	*(int*) sub = 0;
	if (*(int*) (sub + 0x40)) {
		vfs_FreeSubobj(sub + 4);
	}
	*(int*) (sub + 0x40) = 0;
	free(sub);
	*(int*) (obj + 0x7c) = 0;
	return result;
}

/* Closes a VFS stream with full cleanup. Handles both
 * compressed and plain streams, flushing and deallocating
 * zlib state if needed. */

// FUNCTION: SERVER 0x10008d10
// CloseVfsStream

// DATA: SERVER 0x10034678

// DATA: SERVER 0x10034670

__declspec(naked) int __cdecl CloseVfsStream(void* stream)
{
	(void) stream;
	__asm {
		push ebp
		push esi
		mov esi, dword ptr [esp + 0xc]
		xor ebp, ebp
		test esi, esi
		je near L_pop2_ret
		mov al, byte ptr [esi + 0x13c]
		push edi
		test al, 0x20
		je near L_not20
		test al, 8
		je near L_skip_z
		test al, 1
		je L_deflate
		lea eax, [esi + 0x100]
		push eax
		call inflateEnd
		add esp, 4
		jmp L_skip_z
	L_deflate:
		lea edi, [esi + 0x100]
		push 4
		push edi
		call deflate
		push edi
		call deflateEnd
		mov eax, dword ptr [esi + 0x110]
		add esp, 0xc
		cmp eax, 8
		jb L_skip_z
		mov eax, dword ptr [esi + 0x10c]
		mov ecx, dword ptr [esi + 0x138]
		mov edx, 4
	L_byte_loop1:
		mov byte ptr [eax], cl
		shr ecx, 8
		inc eax
		dec edx
		jne L_byte_loop1
		mov ecx, dword ptr [esi + 0x108]
		mov edx, 4
	L_byte_loop2:
		mov byte ptr [eax], cl
		shr ecx, 8
		inc eax
		dec edx
		jne L_byte_loop2
		mov edx, dword ptr [esi + 0x114]
		mov ecx, dword ptr [esi + 0x10c]
		mov eax, dword ptr [esi + 0x110]
		add edx, 8
		add ecx, 8
		add eax, -8
		mov dword ptr [esi + 0x114], edx
		mov dword ptr [esi + 0x10c], ecx
		mov dword ptr [esi + 0x110], eax
	L_skip_z:
		test byte ptr [esi + 0x13c], 1
		jne L_after
		mov ebp, dword ptr [esi + 0x114]
		jmp L_after
	L_not20:
		mov ecx, dword ptr [esi + 0x100]
		test ecx, ecx
		je L_after
		test al, 1
		je L_else1
		test al, 0x10
		je L_else1
		push ecx
		call vfs_CleanupObject
		mov ecx, dword ptr [esi + 0x100]
		push ecx
		call vfs_DestroyEntity
		add esp, 8
		jmp L_after
	L_else1:
		test al, 8
		push ecx
		je L_fflush
		call vfs_FlushAndClose
		jmp L_after_call
	L_fflush:
		call fflush
	L_after_call:
		add esp, 4
	L_after:
		_emit 0x8b
		_emit 0x3d
		_emit 0x78
		_emit 0x46
		_emit 0x03
		_emit 0x10
		push esi
		dec edi
		push 0x10034670
		_emit 0x89
		_emit 0x3d
		_emit 0x78
		_emit 0x46
		_emit 0x03
		_emit 0x10
		call m_PoolFree
		add esp, 8
		mov eax, ebp
		pop edi
		pop esi
		pop ebp
		ret
	L_pop2_ret:
		mov eax, ebp
		pop esi
		pop ebp
		ret
	}
}

/* Reads raw data from a VFS stream. Low-level read that
 * handles buffering, refilling, and byte-by-byte reads
 * for variable-length data. */

char s_D__Develop_Units_vfs_vfs_c_10029458[] = "D:\\Develop\\Units\\vfs\\vfs.c";
char s_vfs__gz_compressed_file____s___i_10029474[] = "vfs: gz-compressed file (\"%s\") in zip found!";

