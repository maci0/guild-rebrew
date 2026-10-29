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
int __cdecl UsingGate();
int __cdecl ch_TakingObject();
int __cdecl ch_DroppingObject();
int __cdecl fcn_00406db0();
int __cdecl fcn_00406e70();
int __cdecl ch_Move2Universe();
int __cdecl fcn_004079f0();
int __cdecl ch_WalkOnPath();
int __cdecl fcn_0040aa00();
int __cdecl fcn_0040b7f0();
int __cdecl fcn_0040abd0();
int __cdecl fcn_0040ba30();
int __cdecl fcn_0040bd80();
char* __cdecl m_alloc(int, const char*);
void __cdecl ch_DeclareAction(int, void*, int, const char*, int);
int __cdecl fcn_00408220(float);


/* Allocates the character action queue and registers the action handlers. */
/* ADDRESS: GOLDTL 0x0040bde0 */
int __cdecl fcn_0040bde0(void)
{
	g_6b5c20 = m_alloc(0xc5440, "ch:Open:ActionQueue");
	if (g_6b5c20 == 0) {
		return 0;
	}
	memset(((int*)g_14d0c40), 0, sizeof(int[0x4c0]));
	memset(((int*)g_14d0020), 0, sizeof(int[0x300]));
	ch_DeclareAction(7, fcn_004079f0, 1, "bewegung/dreh_90_rechts", 2);
	ch_DeclareAction(0, fcn_004079d0, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(23, fcn_00406280, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(45, ch_WalkOnPath, 1, "bewegung/gehen", 3);
	ch_DeclareAction(58, fcn_0040aa00, 1, "bewegung/gehen", 3);
	ch_DeclareAction(57, fcn_0040b7f0, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(46, fcn_00406280, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(47, fcn_00406410, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(48, fcn_004065c0, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(49, ch_TakingObject, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(50, ch_DroppingObject, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(51, ch_Move2Universe, 1, &(*(char*)g_6b5c60), 3);
	ch_DeclareAction(53, fcn_00406db0, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(54, fcn_00406e70, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(55, fcn_0040abd0, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(56, fcn_0040ba30, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(59, fcn_0040bd80, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(52, UsingGate, 1, &(*(char*)g_6b5c60), 5);
	memset(g_1551f40, 0, sizeof(g_1551f40));
	(*(int*)&g_6b5c5c) = fcn_00408220(60.0f);
	return 1;
}
unsigned char _dpad_6b5c60[92] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
