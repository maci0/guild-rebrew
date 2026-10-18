#include <windows.h>
#include "client_cursor.h"

/* ADDRESS: GOLD 0x004113f0 */
void __cdecl fcn_004113f0(int x, int y)
{
	int mode;

	mode = CursorOsBypass;
	CursorX1 = (short) x;
	CursorY1 = (short) y;
	CursorX2 = (short) x;
	CursorY2 = (short) y;
	g_01467380 = (short) x;
	g_01467382 = (short) y;
	if (mode == 0)
		SetCursorPos(x, y);
}
