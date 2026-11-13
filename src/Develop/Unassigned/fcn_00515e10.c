#include <string.h>
int __cdecl fcn_0064f170(void*, char*, int);
void* __cdecl fcn_00422460(int, char*);
int __cdecl fcn_00418c80(void*, void*, int, float);
int __cdecl fcn_004192b0(int, int, int, int);
extern int g_774934;
/* ADDRESS: GOLDTL 0x00515e10 */
void __cdecl fcn_00515e10(char* p)
{
	char buf[0x100];
	int bn, br, si, v, r;
	char* s;
	char* d;

	r = fcn_0064f170(p, (char*) 0x6a1f7c, 4);
	if (r != 0)
		return;

	s = p + 4;
	d = buf;
	do {
		*d = *s;
		d++;
	} while (*s++ != 0);


	bn = (strstr(buf, (char*) 0x6a1f78) == 0);
	br = (int) strstr(buf, (char*) 0x6a1f74);
	if (br != 0) {
		br = 0x7d0;
		bn = 0;
	} else {
		br = 0;
	}

	if (g_774934 != 0) {
		si = (int) fcn_00422460(0, buf);
		if (si != 0) {
			v = (int)(*(float*)(p + 0x68)) + 0x32;
			r = fcn_00418c80((void*) si, p, 0x7f, (float) v);
			if (r != 0)
				fcn_004192b0(r, 0, bn, br);
		}
	}

	*(int*)(p + 0x224) = 0;
	return;
}
