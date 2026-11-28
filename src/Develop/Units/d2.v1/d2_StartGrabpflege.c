extern int d2_GrabpflegeTitleId;
extern int d2_GrabpflegeTitleId;



int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl d2_RunGraveyardPickerDialog(int, int, int, int, void*);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_ConfirmGrabpflege(void);

void __cdecl d2_StartGrabpflege(int a)
{
	if (d2_CheckOwnerBlocked(a) == 0) {
		d2_RunGraveyardPickerDialog(0, a, d2_GrabpflegeTitleId, 1, d2_ConfirmGrabpflege);
		d3_EndCameraAndUiMode();
	}
}
unsigned char _dpad_14b52fc[1180];
