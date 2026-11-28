

#include <string.h>

#include "Develop/DieGildeAddOn/game/game_timestamp.h"






// SIZE 0xe


typedef struct {
	int f0;
	unsigned char type;
	char pad5[3];
	int who;
	int fc;
	char pad10[0x18];
	GAME_TIMESTAMP t;
	unsigned char f36;
	char pad37[0x21];
	int f58;
	char pad5c[0x9c];
} Msg;
// SIZE 0xf8

extern char gm_EntityIdField[];

void __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char *, int, int, int, int, int, int);
void __cdecl cm_SendCopyEntityData(Msg *);
float __cdecl gm_GetEntityMaxHealth(char *);
int __cdecl he_GetEntityHomeTarget(char *, int *, int *, int);
void __cdecl he_AssignActionSlot(int, int, int, int);
char *__cdecl evt_FindScriptById(int);
int __cdecl evt_RequestScriptExit(char *);
void __cdecl ch_StartMovement(int, int, int, int, int, char *);

/* ADDRESS: GOLDDE 0x0052fdf0 */
void __cdecl he_ResolveAccidentOutcome(char *a1, char *entity, char *a3, char *a4, int a5, float value)
{
	int x0;
	int x4;
	float f;
	Msg m;
	char buf[0x800];

	if (value <= 0.0f) {
		if (a3[2] == 6 || a3[2] == 7) {
			io_FormatTextBuffer(buf, 0x1632, *(unsigned short *) entity, a4);
			he_MessageBoxQuickjump(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
		}
		memset(&m, 0, sizeof(m));
		m.type = 0x71;
		if (a1 != 0) {
			m.who = *(int *) (gm_EntityIdField + *(unsigned short *) (a1 + 8) * 0x21c);
		} else {
			m.who = *(int *) (a3 + 4);
		}
		m.fc = -1;
		m.t = *(GAME_TIMESTAMP*) &gm_GameTime;
		m.f36 = 2;
		m.f58 = *(int *) (entity + 4);
		cm_SendCopyEntityData(&m);
	} else {
		f = gm_GetEntityMaxHealth(entity) * 0.5f;
		if (value < f && he_GetEntityHomeTarget(entity, &x0, &x4, 0) != 0 && *(char **) (entity + 0x184) != 0) {
			he_AssignActionSlot(0, 0, *(unsigned short *) entity, 0);
			if (*(int *) (*(char **) (entity + 0x184) + 0x28) != -1) {
				evt_RequestScriptExit(evt_FindScriptById(*(int *) (*(char **) (entity + 0x184) + 0x28)));
			}
			if (x4 == -1) {
				ch_StartMovement(*(int *) (entity + 4), x0, x4, 0, 1, "Unfall");
			} else {
				ch_StartMovement(*(int *) (entity + 4), x0, x4, 0, 0, "Unfall");
			}
			if (a3[2] == 6 || a3[2] == 7) {
				io_FormatTextBuffer(buf, 0x1631, *(unsigned short *) entity, a4, a5 + 0x1626);
				he_MessageBoxQuickjump(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
			}
			return;
		}
		if (a3[2] == 6 || a3[2] == 7) {
			io_FormatTextBuffer(buf, 0x1630, *(unsigned short *) entity, a4, a5 + 0x1626);
			he_MessageBoxQuickjump(*(int *) (a3 + 4), *(int *) (a4 + 1), buf, 0, 0x5ed, *(int *) (a4 + 1), -1, 0, 0);
		}
	}
}
