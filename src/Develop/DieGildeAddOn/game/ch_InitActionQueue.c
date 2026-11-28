#include <string.h>

extern char* g_6b5c20;
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/ch_queue.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_1551f40[0x30];
extern void* g_6b5c5c;
extern char g_6b5c60[];

int __cdecl ch_ExecPlayAnimation();
int __cdecl ch_RunAnimationEvent();
int __cdecl ch_RunStandUpAnimation();
int __cdecl UsingGate();
int __cdecl ch_TakingObject();
int __cdecl ch_DroppingObject();
int __cdecl ch_ExecTurnTowards();
int __cdecl ch_ExecuteAttachAnimation();
int __cdecl ch_Move2Universe();
int __cdecl ch_ExecuteTurn90();
int __cdecl ch_WalkOnPath();
int __cdecl ch_WalkOnPath58();
int __cdecl ch_RunWalkToRandomDummy();
int __cdecl ch_DequeueIfIdle();
int __cdecl ch_UpdateFade();
int __cdecl ch_UpdateWait();
char* __cdecl m_alloc(int, const char*);
void __cdecl ch_DeclareAction(int, void*, int, const char*, int);
int __cdecl ch_AllocMap(float);


/* Allocates the character action queue and registers the action handlers. */
/* ADDRESS: GOLDTL 0x0040bde0 */
int __cdecl ch_InitActionQueue(void)
{
	g_6b5c20 = m_alloc(0xc5440, "ch:Open:ActionQueue");
	if (g_6b5c20 == 0) {
		return 0;
	}
	memset(((int*)ch_ActionDefinitions), 0, sizeof(int[0x4c0]));
	memset(((int*)ch_CharacterSlots), 0, sizeof(int[0x300]));
	ch_DeclareAction(7, ch_ExecuteTurn90, 1, "bewegung/dreh_90_rechts", 2);
	ch_DeclareAction(0, ch_ExecFinishAnimation, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(23, ch_ExecPlayAnimation, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(45, ch_WalkOnPath, 1, "bewegung/gehen", 3);
	ch_DeclareAction(58, ch_WalkOnPath58, 1, "bewegung/gehen", 3);
	ch_DeclareAction(57, ch_RunWalkToRandomDummy, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(46, ch_ExecPlayAnimation, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(47, ch_RunAnimationEvent, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(48, ch_RunStandUpAnimation, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(49, ch_TakingObject, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(50, ch_DroppingObject, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(51, ch_Move2Universe, 1, &(*(char*)g_6b5c60), 3);
	ch_DeclareAction(53, ch_ExecTurnTowards, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(54, ch_ExecuteAttachAnimation, 1, &(*(char*)g_6b5c60), 0);
	ch_DeclareAction(55, ch_DequeueIfIdle, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(56, ch_UpdateFade, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(59, ch_UpdateWait, 1, &(*(char*)g_6b5c60), 1);
	ch_DeclareAction(52, UsingGate, 1, &(*(char*)g_6b5c60), 5);
	memset(g_1551f40, 0, sizeof(g_1551f40));
	(*(int*)&g_6b5c5c) = ch_AllocMap(60.0f);
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
