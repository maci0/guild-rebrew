#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

extern int* __cdecl GetErrnoPointer(void);
extern int __cdecl WriteFileBufferLocked(void*, int, int, int);
extern void __cdecl FreeHeapBlockWithRuntimeLock(void*);
extern int __cdecl free_game_subobject(void*);
extern int __cdecl cleanup_subobject(void*);
extern int __cdecl compress_block(void*, int);
extern int __cdecl locked_fwrite(void*, int, int, void*);
extern int __cdecl game_getbyte(int);
extern int __cdecl flush_stream(int, int);
extern void __cdecl write_uint32_le(int, unsigned int);
extern int __cdecl close_stream(int);
extern int __cdecl crt_locked_putc(int, int);
extern void __cdecl entity_cleanup(char*);
extern void __cdecl stream_close(int);
extern void __cdecl mem_free(char*);
extern int __cdecl func_1001a46e(int handle, int position, int origin);
extern int __cdecl func_1001aa6a(int stream, unsigned int size, int count, int handle);
extern int __cdecl crc32_update(int checksum, int buffer, unsigned int size);
extern int __cdecl func_100058d0(int* ctx, int flag);
extern void __cdecl free_subobj(void*);
extern int __cdecl inflateEnd(void* strm);
extern int __cdecl deflate(void* strm, int flush);
extern int __cdecl deflateEnd(void* strm);
extern int __cdecl cleanup_object(char*);
extern int __cdecl destroy_entity(char*);
extern int __cdecl flush_and_close_stream(int);
extern void __cdecl pool_free(void* pool, void* item);
extern unsigned int gzread(unsigned int*, unsigned int*, int, int, int, int, int, int, unsigned int);
extern int ReadVfsCompressed(unsigned int*, unsigned int*, int);
extern void func_1001a299(int*, int, int);
extern void LogMessageInternal(const char*, int, int*, int);
extern char* __cdecl pool_alloc(char*, int, int); /* 0x10006d20 */;
extern int __cdecl inflateInit2_(char*, int, char*, int); /* 0x100057c0 */;
extern int __cdecl deflateInit2_(char*, int, int, int, int, int, char*, int); /* 0x10001330 */;

;
;
;

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 114
// SYMBOL: _game_getbyte
// FUNCTION: SERVER 0x10003820
// game_getbyte

unsigned int __cdecl game_getbyte(int* param_1)
{
	int* piVar2;
	int iVar3;

	if (param_1[0xf] != 0) {
		return (unsigned int) -1;
	}
	if (param_1[1] == 0) {
		piVar2 = GetErrnoPointer();
		*piVar2 = 0;
		iVar3 = WriteFileBufferLocked((void*) param_1[0x11], 1, 0x4000, param_1[0x10]);
		param_1[1] = iVar3;
		if (iVar3 == 0) {
			param_1[0xf] = 1;
			if ((*(unsigned char*) (param_1[0x10] + 0xc) & 0x20) != 0) {
				param_1[0xe] = -1;
			}
			return (unsigned int) -1;
		}
		param_1[0] = param_1[0x11];
	}
	param_1[1] = param_1[1] - 1;
	iVar3 = (unsigned char) *(unsigned char*) param_1[0];
	param_1[0] = param_1[0] + 1;
	return (unsigned int) iVar3;
}

// ORIGIN: GAME
// BLOCKER: zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 18
// STATUS: RELOC
// SIZE: 177
// SYMBOL: _close_stream
// FUNCTION: SERVER 0x100038a0
// close_stream

int __cdecl close_stream(void* param_1)
{
	int iVar1;
	int* piVar2;
	int result;

	result = 0;
	if (param_1 == 0) {
		return -2;
	}
	if (*(void**) ((int) param_1 + 0x50) != 0) {
		FreeHeapBlockWithRuntimeLock(*(void**) ((int) param_1 + 0x50));
	}
	if (*(int*) ((int) param_1 + 0x1c) != 0) {
		if (*(char*) ((int) param_1 + 0x5c) == 'w') {
			result = free_game_subobject(param_1);
		}
		else if (*(char*) ((int) param_1 + 0x5c) == 'r') {
			result = cleanup_subobject(param_1);
		}
	}
	if (*(FILE**) ((int) param_1 + 0x40) != 0) {
		iVar1 = fclose(*(FILE**) ((int) param_1 + 0x40));
		if (iVar1 != 0) {
			piVar2 = GetErrnoPointer();
			if (*piVar2 != 0x1d) {
				result = -1;
			}
		}
	}
	if (*(int*) ((int) param_1 + 0x38) < 0) {
		result = *(int*) ((int) param_1 + 0x38);
	}
	if (*(void**) ((int) param_1 + 0x44) != 0) {
		FreeHeapBlockWithRuntimeLock(*(void**) ((int) param_1 + 0x44));
	}
	if (*(void**) ((int) param_1 + 0x48) != 0) {
		FreeHeapBlockWithRuntimeLock(*(void**) ((int) param_1 + 0x48));
	}
	if (*(void**) ((int) param_1 + 0x54) != 0) {
		FreeHeapBlockWithRuntimeLock(*(void**) ((int) param_1 + 0x54));
	}
	FreeHeapBlockWithRuntimeLock(param_1);
	return result;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 182
// SYMBOL: _flush_stream
// FUNCTION: SERVER 0x10003b90
// flush_stream

unsigned int __cdecl flush_stream(int param_1, int param_2)
{
	int done;
	int iVar2;
	int iVar3;

	done = 0;
	if (param_1 == 0 || *(char*) (param_1 + 0x5c) != 'w') {
		return 0xFFFFFFFE;
	}
	*(int*) (param_1 + 4) = 0;
	do {
		iVar3 = 0x4000 - *(int*) (param_1 + 0x10);
		if (iVar3 != 0) {
			iVar2 = locked_fwrite(*(int*) (param_1 + 0x48), 1, iVar3, *(int*) (param_1 + 0x40));
			if (iVar2 != iVar3) {
				*(int*) (param_1 + 0x38) = -1;
				return (unsigned int) -1;
			}
			*(int*) (param_1 + 0x10) = 0x4000;
			*(int*) (param_1 + 0x0c) = *(int*) (param_1 + 0x48);
		}
		if (done) {
			break;
		}
		iVar2 = compress_block(param_1, param_2);
		*(int*) (param_1 + 0x38) = iVar2;
		if (iVar3 == 0 && iVar2 == -5) {
			*(int*) (param_1 + 0x38) = 0;
		}
		if (*(int*) (param_1 + 0x10) == 0 && *(int*) (param_1 + 0x38) != 1) {
			done = 0;
		}
		else {
			done = 1;
		}
	} while (*(int*) (param_1 + 0x38) == 0 || *(int*) (param_1 + 0x38) == 1);
	if (*(unsigned int*) (param_1 + 0x38) != 1) {
		return *(unsigned int*) (param_1 + 0x38);
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 77
// SYMBOL: _flush_and_close_stream
// FUNCTION: SERVER 0x10003C50
// read_uint32_be

int __cdecl read_uint32_be(int param_1)
{
	int result;
	int last;

	result = game_getbyte(param_1);
	result = result + (game_getbyte(param_1) << 8);
	result = result + (game_getbyte(param_1) << 16);
	last = game_getbyte(param_1);
	if (last == -1) {
		*(unsigned int*) (param_1 + 0x38) = 0xfffffffd;
	}
	return (last << 24) + result;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 65
// SYMBOL: _read_uint32_be
// FUNCTION: SERVER 0x10003CA0
// flush_and_close_stream

int __cdecl flush_and_close_stream(int param_1)
{
	int iVar1;

	if (param_1 == 0) {
		return -2;
	}
	if (*(char*) (param_1 + 0x5c) == 'w') {
		iVar1 = flush_stream(param_1, 4);
		if (iVar1 == 0) {
			write_uint32_le(*(int*) (param_1 + 0x40), *(unsigned int*) (param_1 + 0x4c));
			write_uint32_le(*(int*) (param_1 + 0x40), *(unsigned int*) (param_1 + 8));
		}
	}
	return close_stream(param_1);
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 43
// SYMBOL: _write_uint32_le
// FUNCTION: SERVER 0x10003CF0
// write_uint32_le

void __cdecl write_uint32_le(int stream, unsigned int value)
{
	int i;

	i = 4;
	do {
		crt_locked_putc(value & 0xff, stream);
		value = value >> 8;
		i = i - 1;
	} while (i != 0);
	return;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 53
// SYMBOL: _destroy_entity
// GHIDRA: cleanup_entity
// FUNCTION: SERVER 0x10008A50
// destroy_entity

int __cdecl destroy_entity(char* entity)
{
	if (!entity) {
		return -102;
	}
	if (*(int*) (entity + 0x7c)) {
		entity_cleanup(entity);
	}
	stream_close(*(int*) entity);
	mem_free(entity);
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// SIZE: 492
// SYMBOL: _ReadVfsCompressed
// BLOCKER_DELTA: 466
// FUNCTION: SERVER 0x10008a90
// ReadVfsCompressed

int __cdecl ReadVfsCompressed(int param_1, int param_2, unsigned int param_3)
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

	if (param_1 == 0) {
		return -0x66;
	}

	ctx = *(int**) (param_1 + 0x7c);
	if (ctx == 0) {
		return -0x66;
	}
	if (*ctx == 0) {
		return -100;
	}

	if (param_3 == 0) {
		return 0;
	}

	ctx[5] = param_3;
	ctx[4] = param_2;
	if ((unsigned int) ctx[0x17] < param_3) {
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
			if (func_1001a46e(ctx[0x18], ctx[0x1a] + ctx[0xf], 0) != 0) {
				return -1;
			}
			if (func_1001aa6a(*ctx, chunk_size, 1, ctx[0x18]) != 1) {
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
			ctx[0x14] = crc32_update(ctx[0x14], ctx[4], copy_count);
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
			decomp_status = func_100058d0(ctx + 1, 2);
			produced = ctx[6] - old_processed;
			ctx[0x14] = crc32_update(ctx[0x14], old_dest, produced);
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 129
// SYMBOL: _cleanup_object
// FUNCTION: SERVER 0x10008C80
// cleanup_object

int __cdecl cleanup_object(char* obj)
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
		free_subobj(sub + 4);
	}
	*(int*) (sub + 0x40) = 0;
	free(sub);
	*(int*) (obj + 0x7c) = 0;
	return result;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 301
// SYMBOL: _CloseVfsStream
// FUNCTION: SERVER 0x10008d10
// CloseVfsStream

/* GLOBAL: SERVER 0x10034678 */
extern int g_stream_count;

/* GLOBAL: SERVER 0x10034670 */
extern char g_stream_pool;

int __cdecl CloseVfsStream(void* stream)
{
	unsigned char flags;
	int result;

	result = 0;
	if (stream == 0) {
		return 0;
	}

	flags = *((unsigned char*) stream + 0x13c);
	if ((flags & 0x20) != 0) {
		if ((flags & 8) != 0) {
			if ((flags & 1) != 0) {
				inflateEnd((char*) stream + 0x100);
			}
			else {
				deflate((char*) stream + 0x100, 4);
				deflateEnd((char*) stream + 0x100);
				if (*(unsigned int*) ((char*) stream + 0x110) >= 8) {
					unsigned char* dst;
					unsigned int val;
					int cnt;

					dst = *(unsigned char**) ((char*) stream + 0x10c);
					val = *(unsigned int*) ((char*) stream + 0x138);
					cnt = 4;
					do {
						*dst = (unsigned char) val;
						val >>= 8;
						dst++;
						cnt--;
					} while (cnt != 0);

					val = *(unsigned int*) ((char*) stream + 0x108);
					cnt = 4;
					do {
						*dst = (unsigned char) val;
						val >>= 8;
						dst++;
						cnt--;
					} while (cnt != 0);

					*(unsigned int*) ((char*) stream + 0x114) = *(unsigned int*) ((char*) stream + 0x114) + 8;
					*(unsigned int*) ((char*) stream + 0x10c) = *(unsigned int*) ((char*) stream + 0x10c) + 8;
					*(unsigned int*) ((char*) stream + 0x110) = *(unsigned int*) ((char*) stream + 0x110) - 8;
				}
			}
		}
		if ((flags & 1) == 0) {
			result = *(int*) ((char*) stream + 0x114);
		}
	}
	else {
		void* fp;
		fp = *(void**) ((char*) stream + 0x100);
		if (fp != 0) {
			if ((flags & 1) != 0 && (flags & 0x10) != 0) {
				cleanup_object(fp);
				destroy_entity(fp);
			}
			else {
				if ((flags & 8) != 0) {
					flush_and_close_stream((int) fp);
				}
				else {
					fflush(fp);
				}
			}
		}
	}

	g_stream_count--;
	pool_free(&g_stream_pool, stream);
	return result;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: jump condition swap, loop rotation / branch layout
// BLOCKER_DELTA: 257
// BLOCKER: instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 472
// SYMBOL: _ReadVfsData
// FUNCTION: SERVER 0x10008e40
// ReadVfsData

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 448
// ANALYSIS: Virtual File System Read function. Handles reading from standard files, raw memory buffers (streamFlags & 0x20), and decompresses gzip streams on the fly (streamFlags & 0x08). Uses zlib inflation state machine to pull compressed file chunks.

unsigned int ReadVfsData(unsigned int* arg_8h, int arg_ch, int arg_10h, int arg_14h)
{
	int* piVar1;
	unsigned char uVar2;
	unsigned int uVar3;
	int iVar4;
	unsigned int uVar5;
	unsigned int uVar6;
	unsigned int* arg_14h_00;
	int var_10ch;
	int in_stack_ffffff08 = 0;
	int in_stack_ffffff0c = 0;
	int in_stack_ffffff10 = 0;
	int in_stack_ffffff14 = 0;
	int in_stack_ffffff1c = 0;
	int in_stack_ffffff28 = 0;
	unsigned int in_stack_ffffff2c = 0;
	int var_8h;
	int var_4h;

	var_4h = -1;
	if ((arg_14h != 0) && (uVar2 = *(unsigned char*) (arg_14h + 0x13c), (uVar2 & 1) != 0)) {
		piVar1 = (int*) (arg_14h + 0x100);
		arg_14h_00 = (unsigned int*) *piVar1;
		if ((arg_14h_00 != 0) || ((uVar2 & 0x20) != 0)) {
			var_8h = arg_ch * arg_10h;
			if ((((uVar2 & 0x20) != 0) && ((uVar2 & 8) == 0)) && (*(int*) (arg_14h + 0x104) < var_8h)) {
				var_8h = *(int*) (arg_14h + 0x104);
			}
			if (var_8h == 0) {
				return 0;
			}
			if (arg_8h != 0) {
				if ((uVar2 & 0x20) != 0) {
					if ((uVar2 & 8) != 0) {
						*(unsigned int**) (arg_14h + 0x10c) = arg_8h;
						*(int*) (arg_14h + 0x110) = var_8h;
						func_100058d0(piVar1, 2);
						return var_8h - *(int*) (arg_14h + 0x110);
					}
					uVar3 = (unsigned int) arg_8h * 3 & 3;
					uVar5 = var_8h - uVar3;
					uVar6 = uVar5;
					if (uVar5 != 0 && uVar3 <= (unsigned int) var_8h) {
						for (; uVar3 != 0; uVar3 = uVar3 - 1) {
							*(unsigned char*) arg_8h = *(unsigned char*) arg_14h_00;
							arg_14h_00 = (unsigned int*) ((char*) arg_14h_00 + 1);
							arg_8h = (unsigned int*) ((char*) arg_8h + 1);
						}
						uVar6 = uVar5 & 3;
						for (uVar5 = uVar5 >> 2; uVar3 = 0, uVar5 != 0; uVar5 = uVar5 - 1) {
							*arg_8h = *arg_14h_00;
							arg_14h_00 = arg_14h_00 + 1;
							arg_8h = arg_8h + 1;
						}
					}
					for (iVar4 = uVar3 + uVar6; iVar4 != 0; iVar4 = iVar4 + -1) {
						*(unsigned char*) arg_8h = *(unsigned char*) arg_14h_00;
						arg_14h_00 = (unsigned int*) ((char*) arg_14h_00 + 1);
						arg_8h = (unsigned int*) ((char*) arg_8h + 1);
					}
					*piVar1 = *piVar1 + var_8h;
					*(int*) (arg_14h + 0x104) = *(int*) (arg_14h + 0x104) - var_8h;
					*(int*) (arg_14h + 0x108) = *(int*) (arg_14h + 0x108) + var_8h;
					return var_8h;
				}
				if ((uVar2 & 0x10) == 0) {
					if ((uVar2 & 8) != 0) {
						uVar3 = gzread(
							arg_14h_00,
							arg_8h,
							in_stack_ffffff08,
							in_stack_ffffff0c,
							in_stack_ffffff10,
							in_stack_ffffff14,
							in_stack_ffffff1c,
							in_stack_ffffff28,
							in_stack_ffffff2c
						);
						return uVar3;
					}
					var_4h = func_1001aa6a(arg_8h, arg_ch, arg_10h, arg_14h_00);
				}
				else {
					var_4h = ReadVfsCompressed(arg_14h_00, arg_8h, var_8h);
					if ((((*(unsigned char*) (arg_14h + 0x13c) & 4) != 0) && (1 < var_4h)) &&
						((*(unsigned char*) (arg_14h + 0x13c) = *(unsigned char*) (arg_14h + 0x13c) & 0xfb,
						  *arg_8h == *(unsigned int*) 0x10029450 &&
							  (*(unsigned int*) ((char*) arg_8h + 4) == *(unsigned int*) 0x10029454)))) {
						func_1001a299(&var_10ch, 0x10029474, arg_14h);
						LogMessageInternal("D:\\Develop\\Units\\vfs\\vfs.c", 0x5b4, &var_10ch, 1);
						return var_4h;
					}
				}
			}
		}
	}
	return var_4h;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 704
// SYMBOL: _OpenVfsStream
// FUNCTION: SERVER 0x10009020
// OpenVfsStream

/* Game function - compression stream initialization */
/* Parses flag string (R/W/N/Z), allocates pool object, sets up zlib inflate/deflate */
// BLOCKER_DELTA: 626

int __cdecl OpenVfsStream(unsigned char* param_1, unsigned int param_2, char* param_3)
{
	char is_read;
	char use_zlib;
	char has_mode;
	char* obj;

	use_zlib = 1;
	has_mode = 1;
	is_read = 1;

	if (param_1 == 0) {
		return 0;
	}

	if (param_2 == 0) {
		return 0;
	}

	{
		char* p;
		char c;

		p = param_3;
		c = *p;
		while (c != 0) {
			int ch;
			ch = toupper(*p);

			switch (ch) {
			case 'N':
				use_zlib = 0;
				has_mode = 0;
				break;
			case 'R':
				is_read = 1;
				break;
			case 'W':
				is_read = 0;
				break;
			case 'Z':
				use_zlib = 1;
				has_mode = 0;
				break;
			}

			p++;
			c = *p;
		}
	}

	obj = pool_alloc((char*) 0x10034670, 0x140, 0x10);
	{
		unsigned char flags;
		flags = *(unsigned char*) (obj + 0x13c);
		flags = (flags & 0xeb) | 0x22;
		*(unsigned char*) (obj + 0x13c) = flags;
	}

	if (is_read) {
		if (has_mode) {
			if (param_2 > 0xa && (unsigned int) param_1[0] == *(unsigned int*) 0x10029450 &&
				(unsigned int) param_1[1] == *(unsigned int*) 0x10029454) {
				use_zlib = 1;
				goto setup_inflate;
			}
			use_zlib = 0;
		}
		else {
			if (use_zlib) {
				goto setup_inflate;
			}
		}

		*(int*) (obj + 0x100) = (int) param_1;
		*(int*) (obj + 0x104) = (int) param_2;
		*(int*) (obj + 0x108) = 0;
		goto done;

	setup_inflate:
		*(int*) (obj + 0x100) = (int) (param_1 + 10);
		*(int*) (obj + 0x104) = (int) param_2 - 10;
		*(int*) (obj + 0x10c) = 0;
		*(int*) (obj + 0x110) = 0;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		{
			int ret;
			ret = inflateInit2_(obj + 0x100, -15, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				goto done;
			}
			goto fail;
		}
	}
	else {
		if (!use_zlib) {
			*(int*) (obj + 0x10c) = (int) param_1;
			*(int*) (obj + 0x110) = (int) param_2;
			*(int*) (obj + 0x114) = 0;
			goto done;
		}

		if (param_2 <= 0x11) {
			goto fail;
		}

		param_1[0] = *(unsigned char*) 0x10029450;
		param_1[1] = *(unsigned char*) 0x10029454;
		param_1[2] = 8;
		param_1[8] = 0;
		param_1[7] = 0;
		param_1[6] = 0;
		param_1[5] = 0;
		param_1[4] = 0;
		param_1[3] = 0;
		param_1[9] = 0xb;

		*(int*) (obj + 0x100) = 0;
		*(int*) (obj + 0x104) = 0;
		*(int*) (obj + 0x10c) = (int) (param_1 + 10);
		*(int*) (obj + 0x110) = (int) param_2 - 10;
		*(int*) (obj + 0x120) = 0;
		*(int*) (obj + 0x124) = 0;

		*(int*) (obj + 0x138) = crc32_update(0, 0, 0);

		{
			volatile int ret;
			ret = deflateInit2_(obj + 0x100, -1, 8, -15, 8, 0, (char*) 0x1002706c, 0x38);
			if (ret == 0) {
				*(int*) (obj + 0x114) = 10;
				goto done;
			}
		}
	}

fail:
	pool_free((char*) 0x10034670, obj);
	return 0;

done:
	if (obj != 0) {
		unsigned char flag_byte;

		*(int*) 0x10034678 = *(int*) 0x10034678 + 1;
		flag_byte = *(unsigned char*) (obj + 0x13c);
		flag_byte = (flag_byte & 0xf6) ^ (is_read & 1);
		flag_byte |= (use_zlib & 1) << 3;
		*(unsigned char*) (obj + 0x13c) = flag_byte;

		sprintf(obj, (char*) 0x100294a4, param_1, param_2, is_read & 0xff, use_zlib & 0xff);
	}

	return (int) obj;
}
