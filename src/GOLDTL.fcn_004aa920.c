/* Owned (both targets) by src/GOLDTL.fcn_004cef70.c. */
extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004a54a0(short*, int, int, unsigned short*, float, float, unsigned short*);
float __cdecl fcn_00507e70(short*, char*, int);
float __cdecl gm_RandomFloat01(void);

// FUNCTION: GOLD 0x4aa800
// FUNCTION: GOLDTL 0x4aa920

int __cdecl fcn_004aa920(short* a1, int a2, char* a3)
{
	unsigned short dst;
	unsigned short ids[4];
	unsigned short src;
	float f;

	ids[0] = 0xffff;
	ids[1] = 0xffff;
	ids[2] = 0xffff;
	ids[3] = 0xffff;
	if (*(int*) ((char*) a1 + 0x194) < 3)
		return 0;
	ids[0] = *a1;
	if (fcn_004a54a0(a1, 0xf00500, 4, ids, 0.0f, gm_RandomMod(0x10) + 33.0, &src) == 0)
		return 0;
	ids[1] = src;
	if (fcn_004a54a0(a1, 0xf00500, 4, ids, 50.0f, 100.0f, &dst) == 0)
		return 0;
	a3[0] = 7;
	*(int*) (a3 + 4) = *(int*) (g_7f4ca0 + src * 540 + 4);
	f = fcn_00507e70(a1, g_7f4ca0 + src * 540, 4);
	if (!(gm_RandomFloat01() + f >= 1.0f))
		return 0;
	*(int*) (a3 + 8) = *(int*) (g_7f4ca0 + dst * 540 + 4);
	return 1;
}
