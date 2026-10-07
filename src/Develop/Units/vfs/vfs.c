extern char g_zlib_version[];
#include "../Error/error.h"
#include "../m_alloc/m_alloc.h"
#include "zlib.h"

#include <stdio.h>
#include <stdlib.h>

int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
typedef struct VFS_INFLATE {
	void* inbuf;            
	char* next_in;          
	unsigned int avail_in;  
	char pad_00c[4];
	char* next_out;         
	unsigned int avail_out; 
	unsigned int total_out; 
	char pad_01c[0x20];
	int in_off;             
	char pad_040[0x10];
	unsigned int crc;       
	char pad_054[4];
	unsigned int remaining; 
	unsigned int cap;       
	void* file;             
	int flag;               
	int base_off;           
} VFS_INFLATE;
// SIZE 0x6c
extern unsigned int __cdecl crc32(unsigned int crc, unsigned char* buf, unsigned int len);
extern int __cdecl inflate(void* zstrm, int flush); 

#include "../../DieGildeAddOn/game/entity.h"

int __cdecl vfs_CleanupObject(char*);
int __cdecl vfs_DestroyEntity(char*);
int __cdecl vfs_FlushAndClose(int);

extern char g_stream_pool[1];
#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl vfs_ReadCompressed(int zstrm, char* buf, unsigned int total);
extern int __cdecl gzread(void* handle, char* buf, unsigned int total);

#include <ctype.h>

extern void* __cdecl m_PoolAlloc(void* head, int size, int max_items);
extern void __cdecl m_pool_free(void* pool, void* item);

typedef struct {
	unsigned char read : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char compressed : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} vfs_mode_bits;

/* Reads a single byte from a VFS stream. Advances the read
 * position and returns the byte value, or error on EOF. */

/* Data span SERVER 0x1002944c..0x100294a0
 *
 * The reference places "rb\\0\\0" (fopen mode), then the gzip magic dwords
 * 0x1f / 0x8b, then the vfs.c path and the gz-compressed-file message.
 * Without the 12-byte prefix, this TU's named strings start at 0x1002944c
 * and displace everything after them.  Callers already push/cmp the raw
 * addresses (gm_Open, vfs_OpenStream, vfs_ReadData); nothing names these
 * symbols, but they must occupy this exact span. */

char s_gzip_mode_rb[4] = { 'r', 'b', 0, 0 };

unsigned int g_gzip_magic_1f = 0x1f;

unsigned int g_gzip_magic_8b = 0x8b;

/* Data span SERVER 0x100294a4
 * Must sit in this TU: link order already places vfs_OpenStream.c.obj
 * immediately before zutil.c.obj, so a named array here lands right before
 * z_errmsg.  A raw address cast emitted nothing and left the slot empty.
 * Declared before use — MSVC6 C requires it. */
int __cdecl vfs_DestroyEntity(char* entity)
{
	if (!entity) {
		return -102;
	}
	if (*(int*) (entity + 0x7c)) {
		vfs_CleanupObject(entity);
	}
	fclose((FILE*) *(int*) entity);
	free(entity);
	return 0;
}

int __cdecl vfs_ReadCompressed(int handle, char* buf, unsigned int len)
{
	VFS_INFLATE* s;
	int err;
	int total;
	unsigned int n;
	unsigned int i;
	char* start;
	unsigned int before;

	err = 0;
	total = 0;
	if (handle == 0) {
		return -102;
	}
	s = *(VFS_INFLATE**) (handle + 0x7c);
	if (s == 0) {
		return -102;
	}
	if (s->inbuf == 0) {
		return -100;
	}
	if (len == 0) {
		return 0;
	}
	s->avail_out = len;
	s->next_out = buf;
	if (len > s->cap) {
		s->avail_out = s->cap;
	}
	while (s->avail_out > 0) {
		if (s->avail_in == 0 && s->remaining > 0) {
			n = 0x4000;
			if (s->remaining < 0x4000) {
				n = s->remaining;
			}
			if (n == 0) {
				return 0;
			}
			if (fseek(s->file, s->base_off + s->in_off, 0) != 0) {
				return -1;
			}
			if (fread(s->inbuf, n, 1, s->file) != 1) {
				return -1;
			}
			s->in_off += n;
			s->remaining -= n;
			s->next_in = s->inbuf;
			s->avail_in = n;
		}
		if (s->flag == 0) {
			n = (s->avail_out < s->avail_in) ? s->avail_out : s->avail_in;
			for (i = 0; i < n; i++) {
				s->next_out[i] = s->next_in[i];
			}
			s->crc = crc32(s->crc, (unsigned char*) s->next_out, n);
			s->cap -= n;
			s->avail_in -= n;
			s->avail_out -= n;
			s->next_out += n;
			s->next_in += n;
			s->total_out += n;
			total += n;
		} else {
			before = s->total_out;
			start = s->next_out;
			err = inflate(&s->next_in, 2);
			n = s->total_out - before;
			s->crc = crc32(s->crc, (unsigned char*) start, n);
			s->cap -= n;
			total += n;
			if (err == 1) {
				return total;
			}
			if (err != 0) {
				return *(volatile int*) &err;
			}
		}
	}
	if (err == 0) {
		return *(volatile int*) &total;
	}
	return *(volatile int*) &err;
}

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
		inflateEnd((void*) (sub + 4));
	}
	*(int*) (sub + 0x40) = 0;
	free(sub);
	*(int*) (obj + 0x7c) = 0;
	return result;
}

int __cdecl CloseVfsStream(void* stream)
{
	int result;
	int n;
	unsigned int value;
	char* write_cursor;

	result = 0;
	if (stream != 0) {
		if (*(unsigned char*) ((char*) stream + 0x13c) & 0x20) {
			if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
				if (*(unsigned char*) ((char*) stream + 0x13c) & 1) {
					inflateEnd((char*) stream + 0x100);
				} else {
					deflate((char*) stream + 0x100, 4);
					deflateEnd((char*) stream + 0x100);
					if (*(unsigned int*) ((char*) stream + 0x110) >= 8) {
						write_cursor = *(char**) ((char*) stream + 0x10c);
						value = *(unsigned int*) ((char*) stream + 0x138);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						value = *(unsigned int*) ((char*) stream + 0x108);
						n = 4;
						do {
							*write_cursor = (char) value;
							value >>= 8;
							write_cursor++;
						} while (--n != 0);
						*(unsigned int*) ((char*) stream + 0x114) += 8;
						*(char**) ((char*) stream + 0x10c) += 8;
						*(unsigned int*) ((char*) stream + 0x110) -= 8;
					}
				}
			}
			if (!(*(unsigned char*) ((char*) stream + 0x13c) & 1)) {
				result = *(unsigned int*) ((char*) stream + 0x114);
			}
		} else {
				if (*(void**) ((char*) stream + 0x100) != 0) {
					if ((*(unsigned char*) ((char*) stream + 0x13c) & 1) && (*(unsigned char*) ((char*) stream + 0x13c) & 0x10)) {
						vfs_CleanupObject(*(void**) ((char*) stream + 0x100));
						vfs_DestroyEntity(*(void**) ((char*) stream + 0x100));
					} else if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
						vfs_FlushAndClose((int) *(void**) ((char*) stream + 0x100));
					} else {
						fclose(*(void**) ((char*) stream + 0x100));
					}
				}
		}
		g_stream_count--;
		m_pool_free((int*) &g_stream_pool, stream);
	}
	return result;
}

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream)
{
	char name[0x100];
	int result;
	char* zstrm;
	/* The target homes the cursor pointer at [ebp-0xc] and the byte count
	 * at [ebp-8].  The count's home comes from the copy prelude, which
	 * names it as an asm operand; this local supplies the cursor's. */
	int zp;
	int total;
	char flags;

	result = -1;
	if (stream == 0) {
		goto done;
	}
	flags = *(unsigned char*) (stream + 0x13c);
	if (!(flags & 1)) {
		goto done;
	}
	zstrm = stream + 0x100;
	zp = (int) zstrm;
	if (*(int*) zstrm == 0 && !(flags & 0x20)) {
		goto done;
	}
	total = size * count;
	if ((flags & 0x20) && !(flags & 8)) {
		unsigned int avail;

		avail = *(unsigned int*) (stream + 0x104);
		if (avail < (unsigned int) total) {
			total = (int) avail;
		}
	}
	if (total == 0) {
		result = total;
		goto done;
	}
	if (buf == 0) {
		goto done;
	}
	if (flags & 0x20) {
		if (flags & 8) {
			*(char**) (stream + 0x10c) = buf;
			*(int*) (stream + 0x110) = total;
			inflate((void*) zp, 2);
			result = total - *(int*) (stream + 0x110);
			goto done;
		}
		{
			char* fsrc;

			fsrc = *(char**) zp;
			/* The original's copy is the 24-byte hand-written alignment
			 * prelude (docs/msvc6-allocator.md Finding 19): dest-align,
			 * then dwords, then the remainder, with a short-count fallback.
			 * No msvc6 C memcpy spelling emits it. */
			__asm {
				mov edi, buf
				mov esi, fsrc
				mov ebx, total
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L1
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L1:
				add ecx, ebx
				rep movsb
			}
		}
		result = total;
		*(char**) zp += total;
		{
			int avail;
			int consumed;
			avail = *(int*) (stream + 0x104);
			consumed = *(int*) (stream + 0x108);
			avail -= total;
			consumed += total;
			*(int*) (stream + 0x104) = avail;
			*(int*) (stream + 0x108) = consumed;
		}
		goto done;
	}
	if (flags & 0x10) {
		result = vfs_ReadCompressed(*(int*) zstrm, buf, (unsigned int) total);
		flags = *(unsigned char*) (stream + 0x13c);
		if (!(flags & 4)) {
			goto done;
		}
		if ((unsigned int) result < 2) {
			goto done;
		}
		*(unsigned char*) (stream + 0x13c) = (unsigned char) (flags & ~4);
		if ((unsigned int) *(unsigned char*) buf != *(unsigned int*) &g_gzip_magic_1f ||
		    (unsigned int) *(unsigned char*) (buf + 1) != *(unsigned int*) &g_gzip_magic_8b) {
			goto done;
		}
		sprintf(name, "vfs: gz-compressed file (\"%s\") in zip found!", stream);
		LogMessageInternal("D:\\Develop\\Units\\vfs\\vfs.c", 0x5b4, name, 1);
		goto done;
	}
	if (flags & 8) {
		result = gzread(*(char**) zstrm, buf, total);
		goto done;
	}
	result = fread(buf, size, count, *(char**) zstrm);
done:
	return result;
}

int __cdecl vfs_OpenStream(unsigned char* buf, unsigned int size, char* mode_flags)
{
	char* stream;
	char* path_cursor;
	int result;
	int mode14;
	unsigned char mode13;
	unsigned char mode18;

	result = 0;
	*(unsigned char*) &mode14 = 1;
	mode18 = 1;
	mode13 = 1;
	if (buf == 0 || size <= 0) {
		goto done;
	}
	for (path_cursor = mode_flags; *path_cursor != 0; path_cursor++) {
	switch (toupper(*path_cursor)) {
		case 'N':
			mode18 = 0;
			mode13 = 0;
			break;
		case 'R':
			*(unsigned char*) &mode14 = 1;
			break;
		case 'W':
			*(unsigned char*) &mode14 = 0;
			break;
		case 'Z':
			mode18 = 1;
			mode13 = 0;
			break;
		default:
			break;
		}
	}
	stream = (char*) m_PoolAlloc((void*) &g_stream_pool, 0x140, 0x10);
	*(unsigned char*) (stream + 0x13c) = (unsigned char) ((*(unsigned char*) (stream + 0x13c) & 0xeb) | 0x22);
	if (*(unsigned char*) &mode14 != 0) {
		if (mode13 != 0) {
			if (size <= 10) {
				mode18 = 0;
			} else if (buf[0] == *(int*) &g_gzip_magic_1f && buf[1] == *(int*) &g_gzip_magic_8b) {
				mode18 = 1;
				goto inflate_setup;
			} else {
				mode18 = 0;
			}
		} else if (mode18 != 0) {
			goto inflate_setup;
		}
		*(char**) (stream + 0x100) = (char*) buf;
		*(unsigned int*) (stream + 0x104) = size;
		*(int*) (stream + 0x108) = 0;
		goto finalize;
	inflate_setup:
		*(char**) (stream + 0x100) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x104) = size - 10;
		*(int*) (stream + 0x10c) = 0;
		*(int*) (stream + 0x110) = 0;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		if (inflateInit2_((void*) (stream + 0x100), -0xf, (char*) &g_zlib_version, 0x38) == 0) {
			goto finalize;
		}
		goto cleanup;
	}
	if (mode18 != 0) {
		if (size < 0x12) {
			goto cleanup;
		}
		buf[0] = *(unsigned char*) &g_gzip_magic_1f;
		buf[1] = *(unsigned char*) &g_gzip_magic_8b;
		buf[2] = 8;
		buf[8] = 0;
		buf[7] = 0;
		buf[6] = 0;
		buf[5] = 0;
		buf[4] = 0;
		buf[3] = 0;
		buf[9] = 0xb;
		*(char**) (stream + 0x100) = 0;
		*(unsigned int*) (stream + 0x104) = 0;
		*(char**) (stream + 0x10c) = (char*) buf + 10;
		*(unsigned int*) (stream + 0x110) = size - 10;
		*(int*) (stream + 0x120) = 0;
		*(int*) (stream + 0x124) = 0;
		*(int*) (stream + 0x138) = crc32(0, 0, 0);
		if (deflateInit2_((void*) (stream + 0x100), -1, 8, -0xf, 8, 0, (char*) &g_zlib_version, 0x38) != 0) {
			goto cleanup;
		}
		*(int*) (stream + 0x114) = 0xa;
	} else {
		*(char**) (stream + 0x10c) = (char*) buf;
		*(unsigned int*) (stream + 0x110) = size;
		*(int*) (stream + 0x114) = 0;
	}
finalize:
	if (stream != 0) {
		g_stream_count = g_stream_count + 1;
		((vfs_mode_bits*) (stream + 0x13c))->read = *(unsigned char*) &mode14;
		((vfs_mode_bits*) (stream + 0x13c))->compressed = mode18;
		sprintf(stream, "0x%08X -> length: %u, read: %u compressed: %u", buf, size, (unsigned char) mode14, mode18);
	}
	result = (int) stream;
done:
	return result;
cleanup:
	m_pool_free((void*) &g_stream_pool, stream);
	return 0;
}

/* Client-only functions of this TU (TL client 0x42e520, 0x42f420, 0x42fcd0).
 * The server never calls them and /OPT:REF discards them, but their CRT
 * references still load strupr.obj, findfile.obj and mkdir.obj. They follow
 * vfs_OpenStream: the reference loads those members after toupper.obj
 * (findfile.obj puts GetLastError after toupper.obj's imports). */
#include <io.h>
#include <direct.h>

extern char g_vfs_case_sensitive;

/* Upper-cases a name unless the file system is case-sensitive. */
char* __cdecl vfs_NormalizeCase(char* name)
{
	if (g_vfs_case_sensitive != 0) {
		return name;
	}
	return _strupr(name);
}

/* SIZE 0x11c */
typedef struct VFS_DIR {
	char name[0x100];
	int count;
	void* files;
	struct VFS_DIR* next;
	struct VFS_DIR* child;
	struct VFS_DIR* parent;
	void* items;
	char loaded;
} VFS_DIR;

/* Writes the path of dir relative to its ancestor stop into out. */
char* __cdecl vfs_GetDirPath(VFS_DIR* dir, VFS_DIR* stop, char* out)
{
	char tmp[0x100];
	VFS_DIR* p;

	p = dir;
	if (p == 0) {
		return 0;
	}
	strcpy(out, p->name);
	while (p != 0) {
		if (p->parent == stop) {
			break;
		}
		p = p->parent;
		strcpy(tmp, p->name);
		strcat(tmp, out);
		strcpy(out, tmp);
	}
	return out;
}

/* Creates every missing directory of path below dir. */
char __cdecl vfs_MakeDirs(char* path, VFS_DIR* dir)
{
	char* s;
	long h;
	char p[0x100];
	char rest[0x100];
	char cur[0x100];
	char base[0x100];
	struct _finddata_t fd;

	if (path == 0 || *path == 0) {
		return 0;
	}
	strcpy(p, path);
	s = strrchr(p, '/');
	if (s != 0) {
		vfs_GetDirPath(dir, 0, base);
		s[1] = 0;
		strcpy(rest, p);
		s = strchr(rest, '/');
		while (s != 0) {
			s++;
			strcpy(p, s);
			*s = 0;
			strcat(base, rest);
			strcpy(cur, base);
			s = strrchr(cur, '/');
			if (s != 0) {
				*s = 0;
			}
			h = _findfirst(cur, &fd);
			if (h == -1) {
				if (_mkdir(cur) != 0) {
					return 0;
				}
			} else {
				_findclose(h);
			}
			strcpy(rest, p);
			s = strchr(rest, '/');
		}
	}
	return 1;
}
