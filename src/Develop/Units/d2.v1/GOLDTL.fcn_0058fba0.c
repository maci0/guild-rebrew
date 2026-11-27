

extern int g_14b57e4;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl d2_RunGraveyardPickerDialog(int, char*, int, int, void*);
int __cdecl d2_ShowFriedhofGehilfenDialog();
void __cdecl d3_EndCameraAndUiMode(void);

void __cdecl fcn_0058fba0(char* e)
{
	if (d2_CheckOwnerBlocked(e) == 0) {
		d2_RunGraveyardPickerDialog(0, e, g_14b57e4, 0, d2_ShowFriedhofGehilfenDialog);
	}
	d3_EndCameraAndUiMode();
}
