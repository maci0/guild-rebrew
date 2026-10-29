#include <string.h>

extern double g_6640e8;
extern unsigned char g_773d75;

char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_005c6270(char* h, int n);
int __cdecl fcn_004a5e60(char* p, int kind, int mask, int b, int c, float r, int* out);
int __cdecl gm_ResolveEntityById(void** out, int a, int b, int id);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl gm_WalkEntityChain(int id);
int __cdecl fcn_0051af00(char* buf, int id, int a, int b);
int __cdecl fcn_004c51a0(int a, int b, unsigned char c, int d);
int __cdecl fcn_00545d40(int a, int b, char* s, int flag, int c, int d);

/* Builds a chat line for the owner of the record named by a0. */
/* ADDRESS: GOLDTL 0x004b7800 */
int __cdecl fcn_004b7800(int* a0)
{
	char buf[512];
	char* h;
	char* e;
	int x;
	int y;
	int r;
	int w;
	double d;

	h = fcn_00508e40(*a0);
	if (h == 0)
		return 1;
	if (fcn_005c6270(h, 0x290) != 0)
		return 0x400;
	if (fcn_004a5e60(h, 6, 0x400000, 0, 0, 100.0f, &x) == 0)
		return 0x400;
	if (gm_ResolveEntityById((void**) &y, 0, 0, x) == 0)
		return 0x400;
	d = (double) (gm_RandomMod(3) & 0xffff) + 1.0;
	r = (int) ((double) gm_WalkEntityChain(*(unsigned short*) h) * d * g_6640e8);
	w = *(unsigned short*) ((char*) a0 + 4);
	fcn_0051af00(buf, w + 0x12e7, y, r);
	fcn_004c51a0(-1, *a0, g_773d75, r);
	e = (char*) *(int*) (h + 4);
	fcn_00545d40((int) e, (int) e, buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
