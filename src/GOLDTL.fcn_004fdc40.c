

typedef struct
{
	char b[0x44];
} Rec44;
// SIZE 0x44

extern Rec44 g_690648[];
extern Rec44 g_690f98[];
extern Rec44 g_6918e8[];
extern Rec44 g_693228[];

unsigned short __cdecl gm_RandomMod(unsigned short n);

Rec44* __cdecl fcn_004fdc40(void)
{
	switch (gm_RandomMod(4)) {
	case 0:
		return &g_690648[gm_RandomMod(0x19)];
	case 1:
		return &g_690f98[gm_RandomMod(5)];
	case 2:
		return &g_6918e8[gm_RandomMod(0x46)];
	case 3:
		return &g_693228[gm_RandomMod(0x46)];
	}
	return 0;
}
