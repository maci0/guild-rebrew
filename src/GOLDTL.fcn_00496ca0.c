// GLOBAL: GOLDTL 0x67eab0
extern char g_67eab0[];
// GLOBAL: GOLD 0x5ffe48
extern char g_67eab0[];
// GLOBAL: GOLDTL 0x664164
extern float g_664164;
// GLOBAL: GOLD 0x5ebb1c
extern float g_664164;
// GLOBAL: GOLDTL 0x662ac8
extern float g_662ac8;
// GLOBAL: GOLD 0x5eb9a0
extern float g_662ac8;
/* Owned (both targets) by src/GOLDTL.fcn_005b24b0.c. */
extern unsigned char g_773d75;

void* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

// FUNCTION: GOLDTL 0x496ca0
// SIZE: 285
// FUNCTION: GOLD 0x4972c0
// SIZE: 285

int __cdecl fcn_00496ca0(int a1, char* a2, int a3)
{
	char buf[0x400];
	int v;
	int r;
	float f;
	void* e;

	if (*(char*) a2 != 7) {
		return 0;
	}
	if (*(char*) a3 != 0x12) {
		return 0;
	}
	e = fcn_00508e40(*(int*) ((char*) a2 + 4));
	if (e == 0) {
		return 0;
	}
	fcn_004c5150(*(int*) ((char*) e + 4), *(int*) ((char*) a1 + 4), g_773d75,
	    *(int*) ((char*) a3 + 8));
	if (*(int*) ((char*) a1 + 0x1cc) & 0x800) {
		f = g_664164;
	} else {
		f = g_662ac8;
	}
	v = *(int*) ((char*) a3 + 0x10) + 1;
	r = (int) (v * f);
	fcn_004c54c0(*(int*) ((char*) a1 + 4), *(int*) ((char*) e + 4), r, 1);
	fcn_004c5420(*(int*) ((char*) a1 + 4), 0x1e8, 4, 0x400, 0);
	if (*(char*) ((char*) e + 2) == 6 || *(char*) ((char*) e + 2) == 7) {
		fcn_0051af00(buf, 0x1751, *(unsigned short*) a1, *(int*) ((char*) a3 + 8));
		fcn_00545d40(*(int*) ((char*) e + 4), -1, buf, 0, 0x5fb, g_67eab0);
	}
	return 9;
}
