#include <string.h>

struct reg_4e71a0 {
	int id;
	char rest[0x110];
};
// SIZE 0x114

extern char g_9a9660[];



#include "Develop/DieGildeAddOn/game/event_callbacks.h"
void __cdecl fcn_004d77e0(void);
void __cdecl fcn_004da170(void);
void __cdecl fcn_004da690(void);
void __cdecl fcn_004dc5f0(void);
void __cdecl fcn_004dc6e0(void);
void __cdecl fcn_004dcf50(void);
void __cdecl fcn_004dfba0(void);
void __cdecl fcn_004e0620(void);
void __cdecl fcn_004e1890(void);
void __cdecl fcn_004e1900(void);
void __cdecl fcn_004e1920(void);
void __cdecl fcn_004e1950(void);
void __cdecl fcn_004e1b00(void);
void __cdecl fcn_004e2090(void);
void __cdecl fcn_004e2890(void);
void __cdecl fcn_004e2b70(void);
void __cdecl fcn_004e3020(void);
void __cdecl fcn_004e33a0(void);
void __cdecl fcn_004e3de0(void);
void __cdecl fcn_004e3ff0(void);
void __cdecl fcn_004e4180(void);

/* ADDRESS: GOLD 0x004e5770 */
/* ADDRESS: GOLDTL 0x004e71a0 */

void __cdecl fcn_004e71a0(void)
{
	int i;

	memset(((struct reg_4e71a0*)g_9a9660), 0, sizeof(struct reg_4e71a0[96]));
	for (i = 0; i < 96; i++)
		((struct reg_4e71a0*)g_9a9660)[i].id = -1;
	fcn_004e7160(0, (void*) fcn_004e1920, (void*) fcn_004e1950, 0, 0, 0);
	fcn_004e7160(1, (void*) fcn_004da690, (void*) fcn_004dc5f0, (void*) fcn_004dc6e0, 0, 0);
	fcn_004e7160(2, (void*) fcn_004dcf50, (void*) fcn_004df1b0, (void*) fcn_004dfba0, fcn_004dc7d0, 0);
	fcn_004e7160(3, (void*) fcn_004d77e0, (void*) fcn_004da170, 0, fcn_004d74b0, 1);
	fcn_004e7160(4, (void*) fcn_004e0620, (void*) fcn_004e1900, (void*) fcn_004e1890, fcn_004e1330, 0);
	fcn_004e7160(5, (void*) fcn_004e1b00, 0, 0, fcn_004e1960, 0);
	fcn_004e7160(6, (void*) fcn_004e2090, 0, 0, fcn_004e1ea0, 0);
	fcn_004e7160(7, (void*) fcn_004e2890, 0, 0, fcn_004e27b0, 0);
	fcn_004e7160(8, (void*) fcn_004e2b70, 0, 0, fcn_004e2b40, 0);
	fcn_004e7160(9, (void*) fcn_004e3020, 0, 0, 0, 0);
	fcn_004e7160(10, (void*) fcn_004e33a0, (void*) fcn_004e3de0, (void*) fcn_004e3ff0, fcn_004e32c0, 1);
	fcn_004e7160(11, (void*) fcn_004e4180, 0, 0, 0, 0);
	fcn_004e4f10(0);
}
