typedef struct Kind {
	unsigned char type;
	char pad1[0x24c];
} Kind;
// SIZE 0x24d

extern unsigned char* g_868050;
extern unsigned char* g_90e094;
extern char g_7f4ca0[];

int __cdecl gm_CheckStatLevel(int, int);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004a5340(unsigned short* e, int n, int* lim, float a4, float r, unsigned short* ids);

// FUNCTION: GOLD 0x004abd00
// FUNCTION: GOLDTL 0x4abe20

int __cdecl fcn_004abe20(int a1, unsigned short* a2, int a3, char* a4)
{
	int lim;
	unsigned short id;
	int lvl;
	int n;
	int i;
	unsigned char* e;
	char* p;

	lvl = gm_CheckStatLevel(*a2, 0xe);
	lim = 0;
	if ((*((unsigned char*) a2 + 0x1cc) & 0x20) != 0)
		return 0;
	if (*(int*) ((char*) a2 + 0x194) < 2)
		return 0;
	if (a1 != 0x47 && a1 != 0)
		return 0;
	if (a3 != 0 || lvl == 0 || *((unsigned char*) a2 + 2) == 3)
		return 0;
	e = g_90e094;
	for (i = 0; i < 0x100; i++, e += 0xa9) {
		if (e[0] != 0 && *(unsigned short*) (e + 0x27) == *a2
		    && ((Kind*)g_868050)[e[0]].type == 0x1f
		    && fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x276) != 0) {
			lim = 0xf00500;
			if (fcn_004a5340(a2, 1, &lim, 0.0f, gm_RandomMod(0x20) + 25.0f, &id) == 0)
				return 0;
			p = g_7f4ca0 + id * 540;
			n = *(int*) ((char*) a2 + 0x194);
			if (n >= 8)
				n = 8;
			n = gm_RandomMod(n);
			if (n <= 2)
				n = 2;
			*(int*) (a4 + 4) = *(int*) (p + 4);
			*(int*) (a4 + 0x10) = n;
			*(int*) (a4 + 0xc) = 0;
			a4[0] = 7;
			return 0x45;
		}
	}
	return 0;
}
