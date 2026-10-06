typedef struct
{
	int i[0x2f4 / 4];
} fcn_00468cf0_Ent;
// SIZE 0x2f4

typedef struct
{
	char pad00[0x52];
	short f52;
} fcn_00468cf0_Def;
// SIZE 0x54

extern char* g_1015ea0;
extern char* g_772500;
extern int g_1040490;
extern int g_1040494;
extern int g_67d398;

int __cdecl fcn_00469890(void);
int __cdecl fcn_00466190(int);
void __cdecl fcn_0046f9b0(int, int);
void __cdecl fcn_00469900(int);

// FUNCTION: GOLDTL 0x468cf0
int __cdecl fcn_00468cf0(int a1, int a2, int a3, int a4)
{
	int idx;

	idx = fcn_00469890();
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x20 / 4] = 9;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x5c / 4] = 1;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x1d0 / 4] = 3;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x10 / 4] = a1;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x1c / 4] = ((fcn_00468cf0_Def*)g_772500)[a3].f52;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x14 / 4] = a2;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x8 / 4] = a3;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x30 / 4] = 0;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x34 / 4] = g_1040490;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x28 / 4] = 0;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x2c / 4] = g_1040494;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0x84 / 4] = g_67d398;
	((fcn_00468cf0_Ent*)g_1015ea0)[idx].i[0xc / 4] = fcn_00466190(a3);
	fcn_0046f9b0(idx, a4);
	fcn_00469900(a3);
	return idx;
}
