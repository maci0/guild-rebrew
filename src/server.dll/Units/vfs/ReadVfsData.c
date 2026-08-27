/* ReadVfsData — VFS stream read (0x10008E40). Reads from a memory buffer
 * (flags & 0x20: cursor at stream+0x100, flushed via fcn_100058d0 when
 * flags & 8), a gzip-in-zip payload (flags & 0x10 → ReadVfsCompressed), a
 * raw stream (flags & 8 → fcn_10003960) or a plain file (fcn_1001aa6a).
 * The stream handle/cursor is the first dword of the stream+0x100 zone.
 *
 * STATUS: PROVEN — semantic equivalence verified with `rebrew prove`
 * (EAX return-value equivalence via Z3 symbolic execution; 2 original +
 * 2 compiled states).  Byte-match (EXACT) remains blocked by the MSVC6
 * memcpy codegen fixed point below, so SIZE_MISMATCH was resolved via the
 * symbolic-proof path instead of further codegen forcing.
 *
 * Byte-level blocker: the target expands memcpy(buf, *zstrm, total) with a
 * dest-aligned prelude (target: stream→edi/total→esi, flags&0x20→dl,
 * `lea ecx,[edi+edi*2]; and ecx,3; sub len,ecx` — same alignment-pass
 * template as pool_alloc/InitPacketPool, docs/msvc6-allocator.md), while
 * msvc6 emits only the naive `shr ecx,2; rep movsd; and ecx,3; rep movsb`
 * from any C shape (candidate: stream→esi/total→ebx, flags&0x20 spilled).
 * Compiled 446 vs target 472 (26B delta); ~50 source variants + cflag/SP
 * sweeps across msvc4.2/5.0/6.0-sp0..sp6 did not flip it. */

// FUNCTION: SERVER 0x10008E40
// ReadVfsData

#include <string.h>

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern int __cdecl ReadVfsCompressed(int zstrm, char* buf, unsigned int total);
extern int __cdecl fcn_10003960(void* handle, char* buf, int total);
extern int __cdecl fcn_1001aa6a(char* buf, int size, int count, void* handle);
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
		memcpy(buf, *(char**) zstrm, total);
		result = total;
		*(char**) zstrm += total;
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
		result = fcn_10003960(*(char**) zstrm, buf, total);
		goto done;
	}
	result = fcn_1001aa6a(buf, size, count, *(char**) zstrm);
done:
	return result;
}

