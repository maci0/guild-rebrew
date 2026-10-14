/* ADDRESS: GOLDTL 0x0044cba0 */
/* ADDRESS: GOLD 0x0044e570 */
// fcn_0044e570 — (popcount32(a) == 1).

unsigned char __cdecl fcn_0044e570(int a)
{
	int i;
	int n;
	n = 0;
	for (i = 0; i < 0x20; i++) {
		n += a & 1;
		a >>= 1;
	}
	return n == 1;
}



// Lives in fcn_0044e570's file on purpose: with the callee defined in the same
// TU, c2 knows the size check writes no memory and keeps h in edi across it.
// ok is volatile: the reference stores the flag although nothing reads it.

#include <string.h>

char* __cdecl fcn_0045be40(int tex);
unsigned char __cdecl fcn_00401590(char* name, int* w, int* h, int z);

int __cdecl fcn_0044cbd0(int tex, char verbose)
{
	char* name;
	int h;
	int w;
	volatile int ok;
	char msg[256];

	name = fcn_0045be40(tex);
	if (name == 0 || (ok = fcn_00401590(name, &w, &h, 0)) == 0) {
		if (verbose) {
			h = -1;
			w = -1;
			strcpy(msg, name);
			strcat(msg, " is an unknown Bitmap-Type!");
			return 0;
		}
	}
	if (w != h && verbose) {
		strcpy(msg, name);
		strcat(msg, " is not square!");
		return -2;
	}
	if (!fcn_0044e570(w) || !fcn_0044e570(h)) {
		if (verbose) {
			strcpy(msg, name);
			strcat(msg, " does not have power of 2 dimensions!");
			return 0;
		}
	}
	return 1;
}
