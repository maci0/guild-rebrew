


extern int g_772514;
extern char g_6a96b8[];
extern char g_6a9694[];
extern char g_6811b0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(char*, ...);
void __cdecl fcn_0058bfd0(int*);

int __cdecl fcn_0058c410(int* s, int a2)
{
	if (s[7] == 0) {
		return 0;
	}
	s[0] = fcn_00470820(0, 0, g_6a96b8);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(s[0]);
	d2_SetForm(s[0], 0);
	fcn_005340f0(g_772514);
	d2_SetForm(s[0], 1);
	s[1] = g_772514;
	io_AppendText(g_6a9694, a2);
	d2_SetForm(s[0], 2);
	s[2] = g_772514;
	d2_SetForm(s[0], 3);
	s[4] = g_772514;
	d2_SetForm(s[0], 5);
	s[5] = g_772514;
	d2_SetForm(s[0], 4);
	s[6] = g_772514;
	io_AppendText(g_6811b0);
	fcn_0058bfd0(s);
	return 1;
}
