#include <string.h>

void __cdecl fcn_0051af00(void* out, int id, ...);
void __cdecl fcn_004fa5f0(void* buf, int a, char* b);

/* ADDRESS: GOLDTL 0x004f8570 */
int __cdecl fcn_004f8570(char* a1, int* a2)
{
	char buf[0x200];
	char* s;
	int* d;
	int t;
	unsigned char v;

	s = a1;
	d = a2;
	t = *d;
	if (t != 3 && t != 1) {
		return 1;
	}
	v = (unsigned char) s[0x166];
	if (v != 0x1b && v != 0xf && v != 0x15 && v != 0xd) {
		return 1;
	}
	if (t == 3) {
		if (s[2] == 6) {
			unsigned char q;
			memset(buf, 0, 0x200);
			q = (unsigned char) s[9];
			fcn_0051af00(buf, 0x1da2, (q ? 0x28 : 0) + 0x253 + v);
			fcn_004fa5f0(buf, 0, (char*) 0x657c7);
		}
		return 2;
	}
	if (t == 1 && s[2] == 6) {
		fcn_0051af00(((char*) d) + 0x14, 0x679060, 0x1da1);
	}
	return 2;
}
