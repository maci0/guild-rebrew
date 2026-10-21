extern int g_6b7fdc;
void* __cdecl fcn_0042ff50(const char*, const char*, void*);
int __cdecl fcn_004306b0(char* buf, int size, int count, char* stream);
long __cdecl fcn_00430c50(char* a);
int __cdecl fcn_0044d770(void* h);
int __cdecl fcn_004011f0(void* a, void* x);
int __cdecl fcn_00430a80(char* s, int off, int whence);
void __cdecl fcn_00430580(void* f);

/* ADDRESS: GOLDTL 0x0044f010 */
int __cdecl fcn_0044f010(char* a1)
{
	char* p;
	int local[2];
	int result;
	int c;

	p = fcn_0042ff50(a1, (char*) 0x6750e8, *(void**) &g_6b7fdc);
	if (p == 0)
		return -1;
	fcn_004306b0((char*) &local[1], 4, 1, p);
	for (;;) {
		result = fcn_00430c50(p);
		c = fcn_0044d770(p);
		if (c == 0x2d) {
			fcn_004011f0(p, &a1);
			fcn_004011f0(p, &local[0]);
			if (local[0] == 0xfab50005) {
				fcn_00430580(p);
				return result;
			}
			fcn_00430a80(p, a1 - 4, 1);
		} else if (c == 0x2b) {
			fcn_00430580(p);
			return -1;
		} else {
			fcn_004011f0(p, &a1);
			fcn_00430a80(p, a1, 1);
		}
	}
}
