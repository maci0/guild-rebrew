extern unsigned char g_7747b0;
extern unsigned char g_6a375c;
extern int g_77250c;



void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_0053ed60(int, int);
void __cdecl fcn_00476970(int);
void __cdecl fcn_00469e30(int);

int __cdecl fcn_0053f460(void)
{
	int r;

	(*(int*)&g_7747b0) = 0;
	d2_SetOverlayAnimation(0, 0);
	(*(char*)&g_6a375c) = 1;
	r = fcn_0053ed60(1, 0);
	if (r == 0) {
		fcn_00476970(g_77250c);
		fcn_00469e30(0x797);
	}
	return r;
}
