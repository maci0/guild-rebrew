extern unsigned char g_7747b0;
extern unsigned char g_6a375c;
extern int g_77250c;



void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_0053ed60(int, int);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_SetBackdropResource(int);

int __cdecl d2_StartSinglePlayerChooseCity(void)
{
	int r;

	(*(int*)&g_7747b0) = 0;
	d2_SetOverlayAnimation(0, 0);
	(*(char*)&g_6a375c) = 1;
	r = fcn_0053ed60(1, 0);
	if (r == 0) {
		d2_ClearSurface(g_77250c);
		d2_SetBackdropResource(0x797);
	}
	return r;
}
