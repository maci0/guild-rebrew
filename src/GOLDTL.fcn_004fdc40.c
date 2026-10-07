// FUNCTION: GOLDTL 0x004fdc40

typedef struct
{
	char b[0x44];
} Rec44;
// SIZE 0x44

extern Rec44 g_690648[];
extern Rec44 g_690f98[];
extern Rec44 g_6918e8[];
extern Rec44 g_693228[];

unsigned short __cdecl fcn_0042e410(unsigned short n);

Rec44* __cdecl fcn_004fdc40(void)
{
	switch (fcn_0042e410(4)) {
	case 0:
		return &g_690648[fcn_0042e410(0x19)];
	case 1:
		return &g_690f98[fcn_0042e410(5)];
	case 2:
		return &g_6918e8[fcn_0042e410(0x46)];
	case 3:
		return &g_693228[fcn_0042e410(0x46)];
	}
	return 0;
}
