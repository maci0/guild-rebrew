/* ReadVfsData — VFS stream read (0x10008E40), SIZE_MISMATCH (obj 455 vs
 * target 472): register allocation (stream→edi in target) and the
 * dest-alignment memcpy prelude (lea ecx,[edi+edi*2]; ...) are
 * unreproducible msvc6 expansions (docs/msvc6-allocator.md). */

// FUNCTION: SERVER 0x10008E40
// ReadVfsData

#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern int __cdecl ReadVfsCompressed(int zstrm, char* buf, unsigned int total);
extern int __cdecl fcn_10003960(char* buf, int size, int count);
extern int __cdecl fcn_1001aa6a(char* buf, int size, int count, void* zstrm);
extern int __cdecl fcn_100058d0(void* zstrm, int flush);

int __cdecl ReadVfsData(char* buf, int size, int count, char* stream)
{
	char name[0x100];
	int result;
	char* zstrm;
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
	if (*(int*) zstrm == 0 && !(flags & 0x20)) {
		goto done;
	}
	total = size * count;
	if ((flags & 0x20) && !(flags & 8)) {
		if (*(unsigned int*) (stream + 0x104) < (unsigned int) total) {
			total = *(int*) (stream + 0x104);
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
			fcn_100058d0(zstrm, 2);
			result = total - *(int*) (stream + 0x110);
			goto done;
		}
		memcpy(buf, *(char**) (stream + 0x10c), total);
		result = total;
		*(char**) (stream + 0x10c) += total;
		*(int*) (stream + 0x104) -= total;
		*(int*) (stream + 0x108) += total;
		goto done;
	}
	if (flags & 0x10) {
		result = ReadVfsCompressed(*(int*) zstrm, buf, (unsigned int) total);
		flags = *(unsigned char*) (stream + 0x13c);
		if (!(flags & 4)) {
			goto done;
		}
		if ((unsigned int) result < 2) {
			goto done;
		}
		*(unsigned char*) (stream + 0x13c) = (unsigned char) (flags & ~4);
		if (*(unsigned char*) buf != *(unsigned char*) 0x10029450 ||
		    *(unsigned char*) (buf + 1) != *(unsigned char*) 0x10029454) {
			goto done;
		}
		sprintf(name, "vfs: gz-compressed file (\"%s\") in zip found!", stream);
		LogMessageInternal((char*) 0x10029458, 0x5b4, name, 1);
		goto done;
	}
	if (flags & 8) {
		result = fcn_10003960(buf, size, count);
		goto done;
	}
	result = fcn_1001aa6a(buf, size, count, zstrm);
done:
	return result;
}

