/* vfs_ReadData - TL client VFS read dispatch.  Reads from a memory buffer
 * (flags & 0x20, cursor at stream+0x100), a gzip-in-zip payload
 * (flags & 0x10 -> unzReadCurrentFile), a raw stream (flags & 8 -> gzread)
 * or a plain file (fread).  Returns the byte count read, or -1. */

#include <string.h>

extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern int __cdecl unzReadCurrentFile(char* zstrm, char* buf, unsigned int total);
extern int __cdecl gzread(char* handle, char* buf, unsigned int total);
extern int __cdecl fread(char* buf, int size, int count, char* handle);
struct z_stream_s;
extern int __cdecl fcn_004616e0(struct z_stream_s* zstrm, int flush);

/* ADDRESS: GOLDTL 0x004306b0 */
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream)
{
	int result;
	int total;
	char* zstrm;
	char name[0x100];
	unsigned char flags, memory;
	char* src;

	result = -1;
	if (stream == 0) {
		goto done;
	}
	flags = (unsigned char) stream[0x13c];
	if (!(flags & 1)) {
		goto done;
	}
	zstrm = stream + 0x100;
	src = *(char**) zstrm;
	if (src == 0 && !(flags & 0x20)) {
		goto done;
	}
	total = size * count;
	memory = (flags >> 5) & 1;
	if (memory && !(flags & 8)) {
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
	if (memory) {
		if (flags & 8) {
			*(char**) (stream + 0x10c) = buf;
			*(int*) (stream + 0x110) = total;
			fcn_004616e0((struct z_stream_s*) zstrm, 2);
			result = total - *(int*) (stream + 0x110);
			goto done;
		}
		{
			count = (int) src;
			__asm {
				mov edi, buf
				mov esi, count
				mov ebx, total
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short CopyDone
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			CopyDone:
				add ecx, ebx
				rep movsb
			}
		}
		result = total;
		*(char**) zstrm += total;
		{
			int avail = *(int*) (stream + 0x104);
			int consumed = *(int*) (stream + 0x108);

			*(int*) (stream + 0x104) = avail - total;
			*(int*) (stream + 0x108) = consumed + total;
		}
		goto done;
	}
	if (flags & 0x10) {
		result = unzReadCurrentFile(src, buf, (unsigned int) total);
		flags = (unsigned char) stream[0x13c];
		if (!(flags & 4)) {
			goto done;
		}
		if ((unsigned int) result < 2) {
			goto done;
		}
		*(unsigned char*) (stream + 0x13c) =
		    (unsigned char) (flags & ~4);
		if (*(unsigned char*) buf != *(int*) 0x679e60 ||
		    *((unsigned char*) buf + 1) != *(int*) 0x679e64) {
			goto done;
		}
		sprintf(name, "vfs: gz-compressed file (\"%s\") in zip found!", stream);
		goto done;
	}
	if (flags & 8) {
		result = gzread(src, buf, (unsigned int) total);
		goto done;
	}
	result = fread(buf, size, count, src);
done:
	return result;
}
