typedef int(__stdcall* Fn1)(void* self);

extern void* g_6b5de0;
extern unsigned long d3_LastReleaseRefCount;

int __stdcall fcn_00610011(void* dev, int a, int b, int c, int d, int e, int f, void** out);

/* ADDRESS: GOLDTL 0x00437110 */
/* ADDRESS: GOLDDE 0x00430610 */
int __cdecl d3_CreateDeviceTexture(int size, int a2, int a3, void** out, unsigned char levels)
{
	if (*out != 0) {
		(*(int*)&d3_LastReleaseRefCount) = ((Fn1) (*(void***) *out)[2])(*out);
		*out = 0;
	}
	return fcn_00610011(g_6b5de0, size, size, levels + 1, a3, a2, ~a3 & 1, out);
}
