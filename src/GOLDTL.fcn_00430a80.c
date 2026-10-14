#include <stdio.h>

int __cdecl fcn_00465540(void* z);
void __cdecl fcn_00465630(void* z);
int __cdecl fcn_00465020(void* z);
int __cdecl fcn_00465350(void* z, void* buf, int len);
void* __cdecl m_alloc(int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl gzseek(void* gz, int off, int whence);

/* ADDRESS: GOLD 0x00430fa0 */
/* ADDRESS: GOLDTL 0x00430a80 */

/* vfs_fseek: seeks a plain, gzip or zip-member stream; zip members seek forward by reading. */
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
					pos = fcn_00465540(*(void**) (s + 0x100));
					if (pos <= off) {
						if (pos == off) {
							r = 0;
						} else {
							off -= pos;
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_SET,skip)");
							if (fcn_00465350(*(void**) (s + 0x100), buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					} else {
						fcn_00465630(*(void**) (s + 0x100));
						if (fcn_00465020(*(void**) (s + 0x100)) == 0) {
							buf = m_alloc(off, "vfs:fseek(inzip,SEEK_SET,skip)");
							if (fcn_00465350(*(void**) (s + 0x100), buf, off) == off) {
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
							if (fcn_00465350(*(void**) (s + 0x100), buf, off) == off) {
								r = 0;
							}
							m_FreeTracked(buf);
						}
					} else {
						fcn_0041d9e0("Unsupported vfs_fseek(inzip,SEEK_CUR)");
					}
				} else {
					fcn_0041d9e0("Unsupported vfs_fseek(inzip,SEEK_END)");
				}
			} else if (s[0x13c] & 8) {
				r = gzseek(*(void**) (s + 0x100), off, whence);
				r = r != -1 ? 0 : -1;
			} else {
				r = fseek(*(FILE**) (s + 0x100), off, whence);
				r = r != 0 ? -1 : 0;
			}
		} else {
			fcn_0041d9e0("Seeking only supported in read-only files");
		}
	}
	return r;
}
