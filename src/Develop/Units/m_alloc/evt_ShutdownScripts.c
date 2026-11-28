


// SIZE 0xc98
typedef struct {
	char used;
	char pad1[0xc97];
} Ctx;

// SIZE 0x4c
typedef struct {
	char name[0x4c];
} Var;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern void* g_6b7e9c;
extern void* evt_GlobalVariables;
extern void* g_6b7ea0;
extern void* g_6b7ea4;
extern void* evt_ScriptErrorLog;
void __cdecl evt_FreeScript(Ctx* c);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDDE 0x00424220 */
void __cdecl evt_ShutdownScripts(void)
{
	int i;

	for (i = 0; i < 0x80; i++) {
		if ((*(Ctx**)&evt_ScriptSlots)[i].used != 0) {
			evt_FreeScript(&(*(Ctx**)&evt_ScriptSlots)[i]);
		}
	}
	for (i = 0; i < 0x100; i++) {
		(*(Var**)&g_6b7e9c)[i].name[0] = 0;
	}
	if (evt_GlobalVariables != 0) {
		m_FreeTracked(evt_GlobalVariables);
		evt_GlobalVariables = 0;
	}
	if ((*(Var**)&g_6b7e9c) != 0) {
		m_FreeTracked((*(Var**)&g_6b7e9c));
		(*(Var**)&g_6b7e9c) = 0;
	}
	if (g_6b7ea0 != 0) {
		m_FreeTracked(g_6b7ea0);
		g_6b7ea0 = 0;
	}
	if (g_6b7ea4 != 0) {
		m_FreeTracked(g_6b7ea4);
		g_6b7ea4 = 0;
	}
	if (evt_ScriptErrorLog != 0) {
		m_FreeTracked(evt_ScriptErrorLog);
		evt_ScriptErrorLog = 0;
	}
	if ((*(Ctx**)&evt_ScriptSlots) != 0) {
		m_FreeTracked((*(Ctx**)&evt_ScriptSlots));
		(*(Ctx**)&evt_ScriptSlots) = 0;
	}
}
