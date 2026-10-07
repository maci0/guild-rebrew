typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046fcd0_Ent;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_1015ea4;
extern int g_1040490;
extern int g_1040494;
extern int g_67d398;
extern char g_67d5bc[];

int __cdecl fcn_00469890(void);
int __cdecl fcn_0041db70(int, char*);
int __cdecl fcn_0046b520(char*, int);

// FUNCTION: GOLDTL 0x46fcd0
int __cdecl fcn_0046fcd0(int a1, int a2, char* name)
{
	int idx;
	char c;
	char* s;
	char* d;

	idx = fcn_00469890();
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x88 / 4] = fcn_0041db70(0x101, g_67d5bc);
	if (((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x88 / 4] == 0) {
		return -1;
	}
	s = name;
	d = (char*) ((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x88 / 4];
	do {
		c = *s;
		s++;
		*d = c;
		d++;
	} while (c != 0);
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x84 / 4] = g_67d398;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x20 / 4] = 0x43;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x10 / 4] = a1;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x14 / 4] = a2;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x18 / 4] = fcn_0046b520(name, ((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x84 / 4]) + 0x60;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x1c / 4] = g_1015ea4;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x24 / 4] = 2;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x30 / 4] = 0;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x34 / 4] = g_1040490;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x28 / 4] = 0;
	((fcn_0046fcd0_Ent*)g_1015ea0)[idx].i[0x2c / 4] = g_1040494;
	return idx;
}
