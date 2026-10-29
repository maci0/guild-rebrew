#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

int __cdecl fcn_00424130(char* set, char* name);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00424040 */
int __cdecl fcn_00424040(char* name)
{
	char* e;
	char* prev = 0;
	int ret = 0;

	if (name != 0) {
		int r;

		r = fcn_00424130(name, 0);
		if (r == 0) {
			for (e = *(char**) (g_6b7d68 + 0x3c); e != 0; e = *(char**) (e + 0x3c)) {
				if (strcmp(e, name) == 0) {
					if (prev != 0) {
						*(char**) (prev + 0x3c) = *(char**) (e + 0x3c);
					} else {
						*(char**) (g_6b7d68 + 0x3c) = *(char**) (e + 0x3c);
					}
					m_FreeTracked(e);
					g_6b7d6c++;
					return r;
				}
				prev = e;
			}
		}
		return r;
	}
	for (;;) {
		e = *(char**) (g_6b7d68 + 0x3c);
		if (e == 0) {
			break;
		}
		if (fcn_00424040(e) != 0) {
			return -1;
		}
		g_6b7d6c++;
	}
	return ret;
}
