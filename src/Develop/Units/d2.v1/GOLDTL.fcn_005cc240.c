

void __cdecl d2_SetForm(int, int);
char* __cdecl io_AppendText(char*, ...);
void __cdecl d2_ClearWindowChildren(int, int);
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id);

extern int d2_CurrentWindowId;
extern char g_1016198[];
extern char s_6811b0[];

int __cdecl fcn_005cc240(int dlg, int sel, int alt)
{
	int prev;
	int old;

	d2_SetForm(dlg, sel);
	prev = ((int(*)[243])g_1016198)[d2_CurrentWindowId][0];
	io_AppendText(s_6811b0);
	d2_ClearWindowChildren(d2_CurrentWindowId, 1);
	if (alt != -1) {
		((int(*)[243])g_1016198)[d2_CurrentWindowId][0] = 0;
		old = d2_CurrentWindowId;
		d2_SetForm(dlg, alt);
		io_AppendText(s_6811b0);
		d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, old, 0x767);
		d2_SetForm(dlg, sel);
		return 0;
	}
	return prev;
}
