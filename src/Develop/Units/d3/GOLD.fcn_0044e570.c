// fcn_0044e570 — (popcount32(a) == 1).

/* ADDRESS: GOLDTL 0x0044cba0 */
/* ADDRESS: GOLDDE 0x00442b90 */
unsigned char __cdecl d3_IsPowerOfTwo(int value)
{
	int i;
	int n;
	n = 0;
	for (i = 0; i < 0x20; i++) {
		n += value & 1;
		value >>= 1;
	}
	return n == 1;
}



// Lives in fcn_0044e570's file on purpose: with the callee defined in the same
// TU, c2 knows the size check writes no memory and keeps h in edi across it.

#include <string.h>

char* __cdecl d3_ResolveTexturePath(int tex);
unsigned char __cdecl vfs_ReadBmpInfo(char* name, int* w, int* h, int z);

/* ADDRESS: GOLDDE 0x00442bc0 */
int __cdecl d3_ValidateTextureDimensions(int tex, char verbose)
{
	char* name;
	int h;
	int w;
	int ok;
	char msg[256];

	name = d3_ResolveTexturePath(tex);
	if (name != 0)
		ok = vfs_ReadBmpInfo(name, &w, &h, 0);
	if (name == 0 || ok == 0) {
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
	if (!d3_IsPowerOfTwo(w) || !d3_IsPowerOfTwo(h)) {
		if (verbose) {
			strcpy(msg, name);
			strcat(msg, " does not have power of 2 dimensions!");
			return 0;
		}
	}
	return 1;
}
