

extern int g_14b57e4;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl fcn_0058bb10(int, char*, int, int, void*);
int __cdecl d2_ShowFriedhofGehilfenDialog();
void __cdecl fcn_00532ef0(void);

void __cdecl fcn_0058fba0(char* e)
{
	if (d2_CheckOwnerBlocked(e) == 0) {
		fcn_0058bb10(0, e, g_14b57e4, 0, d2_ShowFriedhofGehilfenDialog);
	}
	fcn_00532ef0();
}
