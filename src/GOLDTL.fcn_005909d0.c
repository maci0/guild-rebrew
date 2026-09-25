// FUNCTION: GOLD 0x00588430
// SIZE: 419
// FUNCTION: GOLDTL 0x005909d0
// SIZE: 419

extern char* g_868050;
extern int g_772514;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern char s_6a99f4[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
void __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0050d200(void*, int);

int __cdecl fcn_005909d0(int i)
{
	char roman[7][4] = { "", "I", "II", "III", "IV", "V", "VI" };
	char* rec;
	int dlg;

	rec = g_868050 + i * 589;
	dlg = fcn_00470820(0, 0, s_6a99f4);
	fcn_00471b60(dlg);
	fcn_004727a0(0, 1);
	if (rec[0] != 10) {
		fcn_00519190(0x27, i * 14 + 0x48e, roman[(unsigned char) rec[0x247]]);
	} else {
		fcn_00519190(i * 14 + 0x48e);
	}
	fcn_004727a0(0, 2);
	fcn_0046f740(0, 0, i + 0x427, g_772514);
	fcn_00519190(i * 14 + 0x48f);
	if (rec[0] != 10) {
		fcn_004727a0(0, 3);
		fcn_00519190(0x2a, roman[(unsigned char) rec[0x247]]);
		fcn_00519190(0x28, fcn_0050d200(g_7f4ca0 + g_774970 * 540, i));
		fcn_00519190(0x29, *(int*) (rec + 0x243));
	}
	return dlg;
}
