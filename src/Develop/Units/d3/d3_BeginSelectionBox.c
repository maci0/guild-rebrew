extern short io_ActiveCursorX;
extern short io_ActiveCursorY;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_7e4304;
extern int g_7e4308;
extern int g_7e430c;
extern int g_7e4310;




#define MAX_(a, b) ((a) > (b) ? (a) : (b))
#define MIN_(a, b) ((a) < (b) ? (a) : (b))

void __cdecl d3_BeginSelectionBox(void)
{
	int a;
	int b;

	a = MIN_(MAX_(g_1042570, io_ActiveCursorX), d3_ViewportRight - 1);
	b = MIN_(MAX_(g_1042574, io_ActiveCursorY), d3_ViewportBottom - 1);
	g_7e4304 = a;
	g_7e430c = a;
	d3_SelectionBoxActive = 1;
	g_7e4308 = b;
	g_7e4310 = b;
}
