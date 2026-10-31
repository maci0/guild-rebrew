


extern int* g_665f08;
extern char g_6811b0[];

void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(char*, ...);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_00423460(int);
void __cdecl fcn_004237f0(int, int);

void __cdecl fcn_005804f0(void)
{
	d2_SetForm(g_665f08[13], 0);
	io_AppendText(g_6811b0);
	fcn_00471af0(g_665f08[13], 0);
	if (g_665f08[5] != 0) {
		if (fcn_00423460(g_665f08[5]) != 0) {
			fcn_004237f0(g_665f08[5], 0);
		}
		g_665f08[5] = 0;
	}
}
