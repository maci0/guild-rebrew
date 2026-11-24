#include <stdio.h>
#include "zlib.h"

extern char g_6b7fe4[];
extern int g_6b7fec;

int __cdecl unzCloseCurrentFile(char*);
int __cdecl unzClose(char*);
void __cdecl m_pool_free(int* pool, void* block);

/* ADDRESS: GOLD 0x00430aa0 */
int __cdecl fcn_00430aa0(void* stream)
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
					inflateEnd((z_streamp) ((char*) stream + 0x100));
				} else {
					deflate((z_streamp) ((char*) stream + 0x100), 4);
					deflateEnd((z_streamp) ((char*) stream + 0x100));
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
					unzCloseCurrentFile(*(char**) ((char*) stream + 0x100));
					unzClose(*(char**) ((char*) stream + 0x100));
				} else if (*(unsigned char*) ((char*) stream + 0x13c) & 8) {
					gzclose(*(void**) ((char*) stream + 0x100));
				} else {
					fclose(*(FILE**) ((char*) stream + 0x100));
				}
			}
		}
		g_6b7fec--;
		m_pool_free((int*) g_6b7fe4, stream);
	}
	return result;
}
