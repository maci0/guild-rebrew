extern unsigned char gm_ClientModeFlags;
extern unsigned char gm_PlayerCount;
extern int d2_ScreenSurface;



void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl d2_RunChooseCityDialog(int, int);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_SetBackdropResource(int);

int __cdecl d2_StartSinglePlayerChooseCity(void)
{
	int r;

	(*(int*)&gm_ClientModeFlags) = 0;
	d2_SetOverlayAnimation(0, 0);
	(*(char*)&gm_PlayerCount) = 1;
	r = d2_RunChooseCityDialog(1, 0);
	if (r == 0) {
		d2_ClearSurface(d2_ScreenSurface);
		d2_SetBackdropResource(0x797);
	}
	return r;
}
