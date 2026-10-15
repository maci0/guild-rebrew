#include <string.h>

extern char* g_6b5c20;
#include "client_types.h"
#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern void* g_14d0020[];
extern int g_1551f40[0x30];
extern void* g_6b5c5c;
extern char g_6b5c60[];

int __cdecl fcn_00406280();
int __cdecl fcn_00406410();
int __cdecl fcn_004065c0();
int __cdecl fcn_004066d0();
int __cdecl ch_TakingObject();
int __cdecl ch_DroppingObject();
int __cdecl fcn_00406db0();
int __cdecl fcn_00406e70();
int __cdecl fcn_00407390();
int __cdecl fcn_004079d0();
int __cdecl fcn_004079f0();
int __cdecl fcn_0040a600();
int __cdecl fcn_0040aa00();
int __cdecl fcn_0040b7f0();
int __cdecl fcn_0040ba00();
int __cdecl fcn_0040ba30();
int __cdecl fcn_0040bd80();
char* __cdecl m_alloc(int, const char*);
void __cdecl fcn_00406210(int, void*, int, const char*, int);
int __cdecl fcn_00408220(float);

/* ADDRESS: GOLD 0x0040afb0 */
/* ADDRESS: GOLDTL 0x0040bde0 */

/* Allocates the character action queue and registers the action handlers. */
int __cdecl fcn_0040bde0(void)
{
	g_6b5c20 = m_alloc(0xc5440, "ch:Open:ActionQueue");
	if (g_6b5c20 == 0) {
		return 0;
	}
	memset(((int*)g_14d0c40), 0, sizeof(int[0x4c0]));
	memset(((int*)g_14d0020), 0, sizeof(int[0x300]));
	fcn_00406210(7, fcn_004079f0, 1, "bewegung/dreh_90_rechts", 2);
	fcn_00406210(0, fcn_004079d0, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(23, fcn_00406280, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(45, fcn_0040a600, 1, "bewegung/gehen", 3);
	fcn_00406210(58, fcn_0040aa00, 1, "bewegung/gehen", 3);
	fcn_00406210(57, fcn_0040b7f0, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(46, fcn_00406280, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(47, fcn_00406410, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(48, fcn_004065c0, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(49, ch_TakingObject, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(50, ch_DroppingObject, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(51, fcn_00407390, 1, &(*(char*)g_6b5c60), 3);
	fcn_00406210(53, fcn_00406db0, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(54, fcn_00406e70, 1, &(*(char*)g_6b5c60), 0);
	fcn_00406210(55, fcn_0040ba00, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(56, fcn_0040ba30, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(59, fcn_0040bd80, 1, &(*(char*)g_6b5c60), 1);
	fcn_00406210(52, fcn_004066d0, 1, &(*(char*)g_6b5c60), 5);
	memset(g_1551f40, 0, sizeof(g_1551f40));
	(*(int*)&g_6b5c5c) = fcn_00408220(60.0f);
	return 1;
}
