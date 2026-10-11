// FUNCTION: GOLD 0x004b7ac0
// FUNCTION: GOLDTL 0x4b7e70

extern char g_7f4ca0[];
void* __cdecl fcn_00508e40(int);
int  __cdecl fcn_004a55c0(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004b7e70(void* a1)
{
	char buf[0x400];
	int d2;
	unsigned short w1;
	void* p;
	void* e;
	int n;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	d2 = 0x600c01;
	if (fcn_004a55c0(p, 1, &d2, 33.0f, 100.0f, &w1) == 0) {
		return 0x400;
	}
	e = (void*) ((int) g_7f4ca0 + 540 * w1);
	n = 2 * gm_RandomMod(7) + 6;
	fcn_004c54c0(*(int*) ((char*) p + 4), *(int*) ((char*) e + 4), n, 1);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7,
	    *(unsigned short*) e, *(unsigned short*) e);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
