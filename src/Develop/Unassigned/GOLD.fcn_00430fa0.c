#include <stdio.h>
#include "zlib.h"
#include "Develop/Units/m_alloc/m_alloc.h"
#include "Develop/Units/Error/error_message.h"

extern int __cdecl unzReadCurrentFile(int zstrm, char* buf, unsigned int total);
extern int __cdecl unzCloseCurrentFile(char*);
extern long __cdecl unztell(void* file);
extern int __cdecl unzOpenCurrentFile(char* file);

/* ADDRESS: GOLD 0x00430fa0 */
int __cdecl fcn_00430fa0(char* s, int off, int whence)
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
							if (unzReadCurrentFile(*(int*) (s + 0x100), (char*) buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					} else {
						unzCloseCurrentFile(*(char**) (s + 0x100));
						if (unzOpenCurrentFile(*(char**) (s + 0x100)) == 0) {
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_SET,skip)");
							if (unzReadCurrentFile(*(int*) (s + 0x100), (char*) buf, off) == off) {
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
							if (unzReadCurrentFile(*(int*) (s + 0x100), (char*) buf, off) == off) {
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
