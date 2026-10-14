typedef struct VfsFlags {
	unsigned char plain : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char gz : 1;
	unsigned char zip : 1;
	unsigned char mem : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} VfsFlags;
// SIZE 0x1

long __cdecl fcn_00465540(void* h);
long __cdecl fcn_0045fa50(void* h);
long __cdecl fcn_0064e30c(void* h);

/* ADDRESS: GOLD 0x00431170 */
/* ADDRESS: GOLDTL 0x00430c50 */
long __cdecl fcn_00430c50(char* a)
{
	void* h;
	long r;

	r = -1;
	if (a != 0) {
		h = *(void**) (a + 0x100);
		if (h != 0 || ((VfsFlags*) (a + 0x13c))->mem) {
			if (((VfsFlags*) (a + 0x13c))->mem) {
				r = *(long*) (a + 0x108);
			} else if (((VfsFlags*) (a + 0x13c))->plain) {
				if (((VfsFlags*) (a + 0x13c))->zip) {
					r = fcn_00465540(h);
				} else if (((VfsFlags*) (a + 0x13c))->gz) {
					r = fcn_0045fa50(h);
				} else {
					r = fcn_0064e30c(h);
				}
			} else if (((VfsFlags*) (a + 0x13c))->gz) {
				r = fcn_0045fa50(h);
			} else {
				r = fcn_0064e30c(h);
			}
		}
	}
	return r;
}
