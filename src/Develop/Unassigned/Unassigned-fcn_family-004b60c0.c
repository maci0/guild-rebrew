extern signed char g_6a3440;

int __cdecl fcn_004b5b40(void);
int __cdecl fcn_004b5df0(void);

int __cdecl fcn_004b60e0(void);
int __cdecl fcn_004b6210(void);
extern int g_14cbca0;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_6a3760;
extern char g_7f4ca0[];

int __cdecl fcn_004b60c0(void);
int __cdecl fcn_004b62c0(void);
int __cdecl fcn_004b62e0(void);

/* ADDRESS: GOLDTL 0x004b60c0 */
int __cdecl fcn_004b60c0(void)
{
	if (g_6a3440 == 5)
		return fcn_004b5b40();
	return fcn_004b5df0();
}

/* ADDRESS: GOLDTL 0x004b62c0 */
int __cdecl fcn_004b62c0(void)
{
	if (g_6a3440 == 5)
		return fcn_004b60e0();
	return fcn_004b6210();
}

/* ADDRESS: GOLDTL 0x004b6470 */
int __cdecl fcn_004b6470(void)
{
	if (g_14cbca0 != -1) {
		if (*(int*) (g_7f4ca0 + g_774970 * 540 + 4) == g_6a3760)
			return fcn_004b60c0();
		return fcn_004b62c0();
	}
	return fcn_004b62e0();
}
