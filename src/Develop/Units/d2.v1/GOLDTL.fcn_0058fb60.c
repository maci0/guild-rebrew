extern int g_14b5798;
extern int g_14b5798;



int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl fcn_0058bb10(int, int, int, int, void*);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ConfirmGrabpflege(void);

void __cdecl d2_StartGrabpflege(int a)
{
	if (d2_CheckOwnerBlocked(a) == 0) {
		fcn_0058bb10(0, a, g_14b5798, 1, d2_ConfirmGrabpflege);
		d3_EndCameraAndUiMode();
	}
}
unsigned char _dpad_14b52fc[1180];
