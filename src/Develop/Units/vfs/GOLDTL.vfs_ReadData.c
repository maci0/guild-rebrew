/* vfs_ReadData - TL client VFS read dispatch.  Reads from a memory buffer
 * (flags & 0x20, cursor at stream+0x100), a gzip-in-zip payload
 * (flags & 0x10 -> unzReadCurrentFile), a raw stream (flags & 8 -> gzread)
 * or a plain file (fread).  Returns the byte count read, or -1. */

#include <string.h>

extern int __cdecl sprintf(char* buf, const char* fmt, ...);
extern int __cdecl unzReadCurrentFile(char* zstrm, char* buf, unsigned int total);
extern int __cdecl gzread(char* handle, char* buf, unsigned int total);
extern int __cdecl fread(char* buf, int size, int count, char* handle);
extern int __cdecl inflate(void* zstrm, int flush);

/* ADDRESS: GOLDTL 0x004306b0 */
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream)
{
	int result;
	int total;
	char* zstrm;
	char name[0x100];

	result = -1;
	if (stream == 0) {
		goto done;
	}
	if (!(*(unsigned char*) (stream + 0x13c) & 1)) {
		goto done;
	}
	zstrm = stream + 0x100;
	if (*(char**) zstrm == 0 && !(*(unsigned char*) (stream + 0x13c) & 0x20)) {
		goto done;
	}
	total = size * count;
	if (((*(unsigned char*) (stream + 0x13c) >> 5) & 1) &&
	    !(*(unsigned char*) (stream + 0x13c) & 8)) {
		unsigned int avail;

		avail = *(unsigned int*) (stream + 0x104);
		if (avail < (unsigned int) total) {
			total = (int) avail;
		}
	}
	if (total == 0) {
		result = total;
		return result;
	}
	if (buf == 0) {
		goto done;
	}
	if ((*(unsigned char*) (stream + 0x13c) >> 5) & 1) {
		if (*(unsigned char*) (stream + 0x13c) & 8) {
			*(char**) (stream + 0x10c) = buf;
			*(int*) (stream + 0x110) = total;
			inflate(zstrm, 2);
			result = total - *(int*) (stream + 0x110);
			return result;
		}
		memcpy(buf, *(char**) zstrm, total);
		result = total;
		*(char**) zstrm += total;
		*(int*) (stream + 0x104) -= total;
		*(int*) (stream + 0x108) += total;
		return result;
	}
	if (*(unsigned char*) (stream + 0x13c) & 0x10) {
		result = unzReadCurrentFile(*(char**) zstrm, buf, (unsigned int) total);
		if (!(*(unsigned char*) (stream + 0x13c) & 4)) {
			goto done;
		}
		if ((unsigned int) result < 2) {
			goto done;
		}
		*(unsigned char*) (stream + 0x13c) =
		    (unsigned char) (*(unsigned char*) (stream + 0x13c) & ~4);
		if (*(unsigned char*) buf != *(int*) 0x679e60 ||
		    *((unsigned char*) buf + 1) != *(int*) 0x679e64) {
			goto done;
		}
		sprintf(name, "vfs: gz-compressed file (\"%s\") in zip found!", stream);
		return result;
	}
	if (*(unsigned char*) (stream + 0x13c) & 8) {
		result = gzread(*(char**) zstrm, buf, (unsigned int) total);
		return result;
	}
	result = fread(buf, size, count, *(char**) zstrm);
done:
	return result;
}
