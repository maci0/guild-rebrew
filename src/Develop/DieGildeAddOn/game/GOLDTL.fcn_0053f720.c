#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_7e1d40;



#include "client_timer.h"
void __cdecl fcn_0053f4b0(void);
unsigned char* __cdecl fcn_004730c0(int, int, int, int, char*, int, int);
int __cdecl main_RunFrameLoop(void*, int);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_ClearBackdropResource(void);
void __cdecl d2_ClearSurface(int);
void __cdecl fcn_00473150(unsigned char*);

void __cdecl fcn_0053f720(void)
{
	int flags;
	unsigned char* p;

	flags = 0x24087;
	if (g_14cbca0 == -1) {
		flags = 0x24086;
	}
	tb_CloseFunction(fcn_0053f4b0);
	p = fcn_004730c0(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x1e, 1);
	while ((*p & 4) == 0) {
		main_RunFrameLoop(0, flags);
	}
	d2_DestroyForm(g_7e1d40);
	d2_ClearBackdropResource();
	d2_ClearSurface(g_77250c);
	d2_SuppressOverlay = 0;
	fcn_00473150(p);
}
