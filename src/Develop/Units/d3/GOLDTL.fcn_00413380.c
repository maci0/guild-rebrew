

extern int g_6b5cc0;
extern int g_6b5cbc;
#include "Develop/Units/d3/d3_camera.h"
extern char* g_6b5cf8;
extern int g_67a370;
#ifdef REBREW_GOLD
#define OBJ_SND_OFF 0x208
#else
#define OBJ_SND_OFF 0x20c
#endif

void __cdecl fcn_00433780(void*);
void __cdecl fcn_00418860(char*);

/* ADDRESS: GOLD 0x00411c10 */
void __cdecl fcn_00413380(void)
{
	if ((*(char**)&g_6b5cc0) != 0) {
		g_6b5cbc = 1;
		if ((*(char**)&g_6b5cc0)[0x2d] & 0x20) {
			fcn_00433780(g_6b8014);
			g_6b5cbc = 0;
			(*(char**)&g_6b5cc0) = 0;
		}
	}
	if (g_6b5cf8 != 0 && g_67a370 == *(int*) (g_6b5cf8 + OBJ_SND_OFF)) {
		fcn_00418860(g_6b5cf8);
	}
}
