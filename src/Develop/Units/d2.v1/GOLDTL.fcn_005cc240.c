

void __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(char*, ...);
void __cdecl fcn_0046f2c0(int, int);
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id);

extern int g_772514;
extern char g_1016198[];
extern char s_6811b0[];

int __cdecl fcn_005cc240(int dlg, int sel, int alt)
{
	int prev;
	int old;

	d2_SetForm(dlg, sel);
	prev = ((int(*)[243])g_1016198)[g_772514][0];
	io_AppendText(s_6811b0);
	fcn_0046f2c0(g_772514, 1);
	if (alt != -1) {
		((int(*)[243])g_1016198)[g_772514][0] = 0;
		old = g_772514;
		d2_SetForm(dlg, alt);
		io_AppendText(s_6811b0);
		fcn_0046e830(-1, -1, g_772514, old, 0x767);
		d2_SetForm(dlg, sel);
		return 0;
	}
	return prev;
}
