#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "zlib.h"

#include <ctype.h>
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
int __cdecl vfs_Crc32Update(int checksum, int buffer, unsigned int size);
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
			write_result = vfs_LockedFwrite(*(void**) (stream + 0x48), 1, remaining, *(void**) (stream + 0x40));
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
		write_result = vfs_CompressBlock((void*) stream, (int) dest);
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
		putc(value & 0xff, (FILE*) stream);
		value = value >> 8;
		i = i - 1;
	} while (i != 0);
	return;
}

/* Destroys a VFS entity (file/directory node). Frees the
 * entity's name string and the entity struct itself. */

// FUNCTION: SERVER 0x10008A50
// vfs_DestroyEntity

int __cdecl vfs_DestroyEntity(char* entity)
{
	if (!entity) {
		return -102;
	}
	if (*(int*) (entity + 0x7c)) {
		vfs_EntityCleanup(entity);
	}
	vfs_StreamClose(*(int*) entity);
	free(entity);
	return 0;
}

/* Reads compressed (zlib) data from a VFS stream. Decompresses
 * into the output buffer up to the requested byte count. */

// FUNCTION: SERVER 0x10008a90
// ReadVfsCompressed

__declspec(naked) int __cdecl ReadVfsCompressed(int stream, int dest, unsigned int size)
{
	(void) stream;
	(void) dest;
	(void) size;
	__asm {
		sub esp, 8
		mov eax, dword ptr [esp + 0xc]
		push ebx
		push ebp
		push esi
		test eax, eax
		push edi
		mov dword ptr [esp + 0x14], 0
		mov dword ptr [esp + 0x10], 0
		jne L_have_param1
		pop edi
		pop esi
		pop ebp
		mov eax, 0xffffff9a
		pop ebx
		add esp, 8
		ret
	L_have_param1:
		mov esi, dword ptr [eax + 0x7c]
		test esi, esi
		jne L_have_ctx
		pop edi
		pop esi
		pop ebp
		mov eax, 0xffffff9a
		pop ebx
		add esp, 8
		ret
	L_have_ctx:
		cmp dword ptr [esi], 0
		jne L_chk_param3
		pop edi
		pop esi
		pop ebp
		mov eax, 0xffffff9c
		pop ebx
		add esp, 8
		ret
	L_chk_param3:
		mov ecx, dword ptr [esp + 0x24]
		test ecx, ecx
		jne L_proceed
	L_ret_bytes_read:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 8
		ret
	L_proceed:
		mov eax, dword ptr [esp + 0x20]
		mov dword ptr [esi + 0x14], ecx
		mov dword ptr [esi + 0x10], eax
		mov eax, dword ptr [esi + 0x5c]
		cmp ecx, eax
		jbe L_skip_clamp
		mov dword ptr [esi + 0x14], eax
	L_skip_clamp:
		mov eax, dword ptr [esi + 0x14]
		test eax, eax
		jbe near L_finalize_ret
	L_loop:
		mov eax, dword ptr [esi + 8]
		test eax, eax
		jne L_after_read
		mov eax, dword ptr [esi + 0x58]
		test eax, eax
		jbe L_after_read
		mov edi, 0x4000
		cmp eax, edi
		jae L_chunk_ok
		mov edi, eax
		test edi, edi
		je near L_ret_bytes_read
	L_chunk_ok:
		mov ecx, dword ptr [esi + 0x68]
		mov eax, dword ptr [esi + 0x3c]
		mov edx, dword ptr [esi + 0x60]
		add ecx, eax
		push 0
		push ecx
		push edx
		call fseek
		add esp, 0xc
		test eax, eax
		jne near L_neg1
		mov eax, dword ptr [esi + 0x60]
		mov ecx, dword ptr [esi]
		push eax
		push 1
		push edi
		push ecx
		call fread
		add esp, 0x10
		cmp eax, 1
		jne near L_neg1
		mov ecx, dword ptr [esi + 0x3c]
		mov eax, dword ptr [esi + 0x58]
		mov edx, dword ptr [esi]
		add ecx, edi
		sub eax, edi
		mov dword ptr [esi + 0x3c], ecx
		mov dword ptr [esi + 0x58], eax
		mov dword ptr [esi + 4], edx
		mov dword ptr [esi + 8], edi
	L_after_read:
		mov eax, dword ptr [esi + 0x64]
		test eax, eax
		jne L_inflate_path
		mov eax, dword ptr [esi + 0x14]
		mov edi, dword ptr [esi + 8]
		cmp eax, edi
		jae L_use_edi
		mov edi, eax
	L_use_edi:
		xor eax, eax
		test edi, edi
		jbe L_after_copy
	L_copy_loop:
		mov ecx, dword ptr [esi + 4]
		mov edx, dword ptr [esi + 0x10]
		mov cl, byte ptr [ecx + eax]
		mov byte ptr [edx + eax], cl
		inc eax
		cmp eax, edi
		jb L_copy_loop
	L_after_copy:
		mov edx, dword ptr [esi + 0x10]
		mov eax, dword ptr [esi + 0x50]
		push edi
		push edx
		push eax
		call vfs_Crc32Update
		mov ecx, dword ptr [esi + 0x5c]
		mov ebp, dword ptr [esi + 0x14]
		mov ebx, dword ptr [esi + 0x10]
		mov edx, dword ptr [esi + 4]
		mov dword ptr [esi + 0x50], eax
		mov eax, dword ptr [esi + 8]
		sub ecx, edi
		sub eax, edi
		mov dword ptr [esi + 0x5c], ecx
		mov ecx, dword ptr [esi + 0x18]
		mov dword ptr [esi + 8], eax
		mov eax, dword ptr [esp + 0x1c]
		add esp, 0xc
		sub ebp, edi
		add ebx, edi
		add edx, edi
		add ecx, edi
		add eax, edi
		mov dword ptr [esi + 0x14], ebp
		mov dword ptr [esi + 0x10], ebx
		mov dword ptr [esi + 4], edx
		mov dword ptr [esi + 0x18], ecx
		mov dword ptr [esp + 0x10], eax
		jmp L_loop_test
	L_inflate_path:
		mov ebx, dword ptr [esi + 0x18]
		mov ebp, dword ptr [esi + 0x10]
		lea ecx, [esi + 4]
		push 2
		push ecx
		call inflate
		mov edi, dword ptr [esi + 0x18]
		mov edx, dword ptr [esi + 0x50]
		sub edi, ebx
		mov dword ptr [esp + 0x1c], eax
		push edi
		push ebp
		push edx
		call vfs_Crc32Update
		mov ebx, dword ptr [esi + 0x5c]
		mov edx, dword ptr [esp + 0x24]
		mov dword ptr [esi + 0x50], eax
		mov eax, dword ptr [esp + 0x28]
		add esp, 0x14
		sub ebx, edi
		add edx, edi
		cmp eax, 1
		mov dword ptr [esi + 0x5c], ebx
		mov dword ptr [esp + 0x10], edx
		je near L_finalize_ret
		test eax, eax
		jne near L_ret_param_status
	L_loop_test:
		mov eax, dword ptr [esi + 0x14]
		test eax, eax
		ja near L_loop
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		jne L_ret_param_status
	L_finalize_ret:
		mov eax, dword ptr [esp + 0x10]
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 8
		ret
	L_neg1:
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		add esp, 8
		ret
	L_ret_param_status:
		mov eax, dword ptr [esp + 0x14]
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 8
		ret
	}
}

int __cdecl ReadVfsCompressed_unused(int stream, int dest, unsigned int size)
{
	int* ctx;
	int bytes_read;
	int decomp_status;
	unsigned int chunk_size;
	unsigned int copy_count;
	unsigned int j;
	int old_processed;
	int old_dest;
	int produced;

	bytes_read = 0;
	decomp_status = 0;

	if (stream == 0) {
		return -0x66;
	}

	ctx = *(int**) (stream + 0x7c);
	if (ctx == 0) {
		return -0x66;
	}
	if (*ctx == 0) {
		return -100;
	}

	if (size == 0) {
		return 0;
	}

	ctx[5] = size;
	ctx[4] = dest;
	if ((unsigned int) ctx[0x17] < size) {
		ctx[5] = ctx[0x17];
	}

	if ((unsigned int) ctx[5] == 0) {
		return bytes_read;
	}

	do {
		if (ctx[2] == 0 && (unsigned int) ctx[0x16] > 0) {
			chunk_size = 0x4000;
			if ((unsigned int) ctx[0x16] < 0x4000) {
				chunk_size = (unsigned int) ctx[0x16];
				if (chunk_size == 0) {
					return 0;
				}
			}
			if (fseek((FILE*) ctx[0x18], ctx[0x1a] + ctx[0xf], 0) != 0) {
				return -1;
			}
			if (fread((void*) *ctx, chunk_size, 1, (FILE*) ctx[0x18]) != 1) {
				return -1;
			}
			ctx[0xf] += chunk_size;
			ctx[0x16] -= chunk_size;
			ctx[1] = *ctx;
			ctx[2] = chunk_size;
		}

		if (ctx[0x19] == 0) {
			copy_count = (unsigned int) ctx[2];
			if ((unsigned int) ctx[5] < (unsigned int) ctx[2]) {
				copy_count = (unsigned int) ctx[5];
			}
			j = 0;
			if (copy_count > 0) {
				do {
					*((char*) ctx[4] + j) = *((char*) ctx[1] + j);
					j++;
				} while (j < copy_count);
			}
			ctx[0x14] = vfs_Crc32Update(ctx[0x14], ctx[4], copy_count);
			ctx[0x17] -= copy_count;
			ctx[2] -= copy_count;
			ctx[5] -= copy_count;
			ctx[4] += copy_count;
			ctx[1] += copy_count;
			ctx[6] += copy_count;
			bytes_read += copy_count;
		}
		else {
			old_processed = ctx[6];
			old_dest = ctx[4];
			decomp_status = inflate((z_stream*) (ctx + 1), 2);
			produced = ctx[6] - old_processed;
			ctx[0x14] = vfs_Crc32Update(ctx[0x14], old_dest, produced);
			ctx[0x17] -= produced;
			bytes_read += produced;
			if (decomp_status == 1) {
				return bytes_read;
			}
			if (decomp_status != 0) {
				return decomp_status;
			}
		}
	} while ((unsigned int) ctx[5] > 0);

	if (decomp_status != 0) {
		return decomp_status;
	}

	return bytes_read;
}

/* Cleans up a VFS object by closing its underlying handle,
 * freeing path strings, and releasing the object struct. */

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

extern char s_D__Develop_Units_vfs_vfs_c_10029458[];
extern char s_vfs__gz_compressed_file____s___i_10029474[];

// FUNCTION: SERVER 0x10008e40
// ReadVfsData

__declspec(naked) unsigned int ReadVfsData(unsigned int* arg_8h, int arg_ch, int arg_10h, int arg_14h)
{
	(void) arg_8h;
	(void) arg_ch;
	(void) arg_10h;
	(void) arg_14h;
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 0x10c
		push ebx
		push esi
		push edi
		mov edi, dword ptr [ebp + 0x14]
		test edi, edi
		mov dword ptr [ebp - 4], 0xffffffff
		je near L_finalize
		mov cl, byte ptr [edi + 0x13c]
		test cl, 1
		je near L_finalize
		lea eax, [edi + 0x100]
		mov dword ptr [ebp - 0xc], eax
		mov eax, dword ptr [eax]
		test eax, eax
		jne L_have_src
		test cl, 0x20
		je near L_finalize
	L_have_src:
		mov esi, dword ptr [ebp + 0xc]
		mov dl, cl
		imul esi, dword ptr [ebp + 0x10]
		and dl, 0x20
		mov dword ptr [ebp - 8], esi
		je L_after_clamp
		test cl, 8
		jne L_after_clamp
		mov ebx, dword ptr [edi + 0x104]
		cmp ebx, esi
		jae L_after_clamp
		mov dword ptr [ebp - 8], ebx
		mov esi, ebx
	L_after_clamp:
		test esi, esi
		jne L_have_size
		mov dword ptr [ebp - 4], esi
		mov eax, esi
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	L_have_size:
		mov ebx, dword ptr [ebp + 8]
		test ebx, ebx
		je near L_finalize
		test dl, dl
		je near L_not_20
		test cl, 8
		je L_mem_copy_path
		mov eax, dword ptr [ebp - 0xc]
		push 2
		push eax
		mov dword ptr [edi + 0x10c], ebx
		mov dword ptr [edi + 0x110], esi
		call inflate
		mov eax, dword ptr [edi + 0x110]
		add esp, 8
		sub esi, eax
		mov dword ptr [ebp - 4], esi
		mov eax, esi
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	L_mem_copy_path:
		mov dword ptr [ebp + 0x10], eax
		mov edi, dword ptr [ebp + 8]
		mov esi, dword ptr [ebp + 0x10]
		mov ebx, dword ptr [ebp - 8]
		lea ecx, [edi + edi*2]
		and ecx, 3
		sub ebx, ecx
		jle L_skip_first_movsb
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L_skip_first_movsb:
		add ecx, ebx
		rep movsb
		mov ecx, dword ptr [ebp - 0xc]
		mov eax, dword ptr [ebp - 8]
		mov dword ptr [ebp - 4], eax
		mov edi, dword ptr [ecx]
		add edi, eax
		mov dword ptr [ecx], edi
		mov ecx, dword ptr [ebp + 0x14]
		pop edi
		mov esi, dword ptr [ecx + 0x104]
		mov edx, dword ptr [ecx + 0x108]
		sub esi, eax
		add edx, eax
		mov dword ptr [ecx + 0x104], esi
		pop esi
		mov dword ptr [ecx + 0x108], edx
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	L_not_20:
		test cl, 0x10
		je L_chk_compressed
		push esi
		push ebx
		push eax
		call ReadVfsCompressed
		mov dword ptr [ebp - 4], eax
		mov al, byte ptr [edi + 0x13c]
		add esp, 0xc
		test al, 4
		je near L_finalize
		cmp dword ptr [ebp - 4], 2
		jb near L_finalize
		and al, 0xfb
		xor ecx, ecx
		mov byte ptr [edi + 0x13c], al
		mov cl, byte ptr [ebx]
		_emit 0x3b
		_emit 0x0d
		_emit 0x50
		_emit 0x94
		_emit 0x02
		_emit 0x10
		jne near L_finalize
		_emit 0xa1
		_emit 0x54
		_emit 0x94
		_emit 0x02
		_emit 0x10
		xor edx, edx
		mov dl, byte ptr [ebx + 1]
		cmp edx, eax
		jne near L_finalize
		push edi
		lea eax, [ebp - 0x10c]
		push offset s_vfs__gz_compressed_file____s___i_10029474
		push eax
		call sprintf
		lea ecx, [ebp - 0x10c]
		push 1
		push ecx
		push 0x5b4
		push offset s_D__Develop_Units_vfs_vfs_c_10029458
		call LogMessageInternal
		mov eax, dword ptr [ebp - 4]
		add esp, 0x1c
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	L_chk_compressed:
		test cl, 8
		je L_fread_path
		push esi
		push ebx
		push eax
		call gzread
		add esp, 0xc
		mov dword ptr [ebp - 4], eax
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	L_fread_path:
		mov edx, dword ptr [ebp + 0x10]
		push eax
		mov eax, dword ptr [ebp + 0xc]
		push edx
		push eax
		push ebx
		call fread
		add esp, 0x10
		mov dword ptr [ebp - 4], eax
	L_finalize:
		mov eax, dword ptr [ebp - 4]
		pop edi
		pop esi
		pop ebx
		mov esp, ebp
		pop ebp
		ret
	}
}

unsigned int ReadVfsData_unused(unsigned int* arg_8h, int arg_ch, int arg_10h, int arg_14h)
{
	int* stream_ptr;
	unsigned char stream_flags;
	unsigned int read_count;
	int copy_iter;
	unsigned int aligned_size;
	unsigned int tail_bytes;
	unsigned int* src_ptr;
	int log_ctx;
	int in_stack_ffffff08 = 0;
	int in_stack_ffffff0c = 0;
	int in_stack_ffffff10 = 0;
	int in_stack_ffffff14 = 0;
	int in_stack_ffffff1c = 0;
	int in_stack_ffffff28 = 0;
	unsigned int in_stack_ffffff2c = 0;
	int total_size;
	int result;

	result = -1;
	if ((arg_14h != 0) && (stream_flags = *(unsigned char*) (arg_14h + 0x13c), (stream_flags & 1) != 0)) {
		stream_ptr = (int*) (arg_14h + 0x100);
		src_ptr = (unsigned int*) *stream_ptr;
		if ((src_ptr != 0) || ((stream_flags & 0x20) != 0)) {
			total_size = arg_ch * arg_10h;
			if ((((stream_flags & 0x20) != 0) && ((stream_flags & 8) == 0)) &&
				(*(int*) (arg_14h + 0x104) < total_size)) {
				total_size = *(int*) (arg_14h + 0x104);
			}
			if (total_size == 0) {
				return 0;
			}
			if (arg_8h != 0) {
				if ((stream_flags & 0x20) != 0) {
					if ((stream_flags & 8) != 0) {
						*(unsigned int**) (arg_14h + 0x10c) = arg_8h;
						*(int*) (arg_14h + 0x110) = total_size;
						inflate((z_stream*) stream_ptr, 2);
						return total_size - *(int*) (arg_14h + 0x110);
					}
					read_count = (unsigned int) arg_8h * 3 & 3;
					aligned_size = total_size - read_count;
					tail_bytes = aligned_size;
					if (aligned_size != 0 && read_count <= (unsigned int) total_size) {
						for (; read_count != 0; read_count = read_count - 1) {
							*(unsigned char*) arg_8h = *(unsigned char*) src_ptr;
							src_ptr = (unsigned int*) ((char*) src_ptr + 1);
							arg_8h = (unsigned int*) ((char*) arg_8h + 1);
						}
						tail_bytes = aligned_size & 3;
						for (aligned_size = aligned_size >> 2; read_count = 0, aligned_size != 0;
							 aligned_size = aligned_size - 1) {
							*arg_8h = *src_ptr;
							src_ptr = src_ptr + 1;
							arg_8h = arg_8h + 1;
						}
					}
					for (copy_iter = read_count + tail_bytes; copy_iter != 0; copy_iter = copy_iter + -1) {
						*(unsigned char*) arg_8h = *(unsigned char*) src_ptr;
						src_ptr = (unsigned int*) ((char*) src_ptr + 1);
						arg_8h = (unsigned int*) ((char*) arg_8h + 1);
					}
					*stream_ptr = *stream_ptr + total_size;
					*(int*) (arg_14h + 0x104) = *(int*) (arg_14h + 0x104) - total_size;
					*(int*) (arg_14h + 0x108) = *(int*) (arg_14h + 0x108) + total_size;
					return total_size;
				}
				if ((stream_flags & 0x10) == 0) {
					if ((stream_flags & 8) != 0) {
						/* Decompiler artifact: gzread takes 3 args but Ghidra emits 9 (stack padding) */
#pragma warning(push)
#pragma warning(disable : 4020)
						read_count = gzread(
							src_ptr,
							arg_8h,
							in_stack_ffffff08,
							in_stack_ffffff0c,
							in_stack_ffffff10,
							in_stack_ffffff14,
							in_stack_ffffff1c,
							in_stack_ffffff28,
							in_stack_ffffff2c
						);
#pragma warning(pop)
						return read_count;
					}
					result = fread(arg_8h, arg_ch, arg_10h, (FILE*) src_ptr);
				}
				else {
					result = ReadVfsCompressed((int) src_ptr, (int) arg_8h, total_size);
					if ((((*(unsigned char*) (arg_14h + 0x13c) & 4) != 0) && (1 < result)) &&
						((*(unsigned char*) (arg_14h + 0x13c) = *(unsigned char*) (arg_14h + 0x13c) & 0xfb,
						  *arg_8h == *(unsigned int*) 0x10029450 &&
							  (*(unsigned int*) ((char*) arg_8h + 4) == *(unsigned int*) 0x10029454)))) {
						sprintf((char*) &log_ctx, (char*) 0x10029474, arg_14h);
						LogMessageInternal("D:\\Develop\\Units\\vfs\\vfs.c", 0x5b4, (char*) &log_ctx, 1);
						return result;
					}
				}
			}
		}
	}
	return result;
}

/* Opens a VFS stream for reading or writing. Initializes
 * compression state (zlib), sets up buffering, and links
 * the stream into the open stream list. */
