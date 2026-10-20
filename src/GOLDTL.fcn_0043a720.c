#include <string.h>

extern char g_6b5c60;

void __cdecl fcn_004315c0(int obj);
void __cdecl fcn_004316c0(int obj);

/* ADDRESS: GOLDTL 0x0043a720 */
char __cdecl fcn_0043a720(int obj, char* name)
{
	int v2;
	int p;
	int i;
	int n;

	if (obj == 0 || name == 0) {
		return 0;
	}
	if (*(int*) (obj + 0x1fc) == 0) {
		return 0;
	}
	if (*(int*) (obj + 0x1ec) == 0) {
		return 0;
	}
	*(char*) (*(int*) (obj + 0x1ec) + 0xb4) = g_6b5c60;
	v2 = *(int*) (obj + 0x1fc);
	if (*(int*) (v2 + 0x1ec) == 0) {
		return 0;
	}
	p = *(int*) (*(int*) (v2 + 0x1ec) + 0x40c);
	if (p == 0) {
		return 0;
	}
	n = *(unsigned char*) (p + 0x2a0);
	for (i = 0; i < n; i++) {
		if (strcmp((char*) (p + 0x74 + i * 0x58), name) == 0) {
			break;
		}
	}
	if (i >= n) {
		return 0;
	}
	strcpy((char*) (*(int*) (obj + 0x1ec) + 0xb4), name);
	fcn_004315c0(v2);
	fcn_004316c0(v2);
	return 1;
}
