// FUNCTION: GOLD 0x583e30
// SIZE: 209
// FUNCTION: GOLDTL 0x0058c410
// SIZE: 209

extern int g_772514;
extern char g_6a96b8[];
extern char g_6a9694[];
extern char g_6811b0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_00519190(char*, ...);
void __cdecl fcn_0058bfd0(int*);

int __cdecl fcn_0058c410(int* s, int a2)
{
	if (s[7] == 0) {
		return 0;
	}
	s[0] = fcn_00470820(0, 0, g_6a96b8);
	fcn_00473a90(0, 0);
	fcn_00471b60(s[0]);
	fcn_004727a0(s[0], 0);
	fcn_005340f0(g_772514);
	fcn_004727a0(s[0], 1);
	s[1] = g_772514;
	fcn_00519190(g_6a9694, a2);
	fcn_004727a0(s[0], 2);
	s[2] = g_772514;
	fcn_004727a0(s[0], 3);
	s[4] = g_772514;
	fcn_004727a0(s[0], 5);
	s[5] = g_772514;
	fcn_004727a0(s[0], 4);
	s[6] = g_772514;
	fcn_00519190(g_6811b0);
	fcn_0058bfd0(s);
	return 1;
}
