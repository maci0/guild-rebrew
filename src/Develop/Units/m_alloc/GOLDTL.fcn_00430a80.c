#include <stdio.h>

long __cdecl unztell(void* file);
int __cdecl unzCloseCurrentFile(void* file);
int __cdecl unzOpenCurrentFile(void* file);
int __cdecl unzReadCurrentFile(void* z, void* buf, int len);
void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
#include "Develop/Units/Error/error_message.h"
int __cdecl gzseek(void* gz, int off, int whence);


/* vfs_fseek: seeks a plain, gzip or zip-member stream; zip members seek forward by reading. */
/* ADDRESS: GOLDTL 0x00430a80 */
int __cdecl fcn_00430a80(char* s, int off, int whence)
{
	int r;
	int pos;
	void* buf;

	r = -1;
	if (s != 0 && *(void**) (s + 0x100) != 0 && (s[0x13c] & 0x20) == 0) {
		if (s[0x13c] & 1) {
			if (s[0x13c] & 0x10) {
				s[0x13c] &= ~4;
				if (whence == 0) {
					pos = unztell(*(void**) (s + 0x100));
					if (pos <= off) {
						if (pos == off) {
							r = 0;
						} else {
							off -= pos;
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_SET,skip)");
							if (unzReadCurrentFile(*(void**) (s + 0x100), buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					} else {
						unzCloseCurrentFile(*(void**) (s + 0x100));
						if (unzOpenCurrentFile(*(void**) (s + 0x100)) == 0) {
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_SET,skip)");
							if (unzReadCurrentFile(*(void**) (s + 0x100), buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					}
				} else if (whence == 1) {
					if (off >= 0) {
						if (off == 0) {
							r = 0;
						} else {
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_CUR,skip)");
							if (unzReadCurrentFile(*(void**) (s + 0x100), buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					} else {
						ReportClientMessage("Unsupported vfs_fseek(inzip,SEEK_CUR)");
					}
				} else {
					ReportClientMessage("Unsupported vfs_fseek(inzip,SEEK_END)");
				}
			} else if (s[0x13c] & 8) {
				r = gzseek(*(void**) (s + 0x100), off, whence);
				r = r != -1 ? 0 : -1;
			} else {
				r = fseek(*(FILE**) (s + 0x100), off, whence);
				r = r != 0 ? -1 : 0;
			}
		} else {
			ReportClientMessage("Seeking only supported in read-only files");
		}
	}
	return r;
}
