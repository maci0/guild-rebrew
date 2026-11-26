extern char* g_aed32c;
#include "Develop/DieGildeAddOn/game/game_player.h"

int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl d2_CheckActionBlocker(char*, int);
float __cdecl gm_GetEntitySkill(char*, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
int __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestModifyHealth(int, int);
void __cdecl cm_SendBlockCharacter(int, int, int);
int __cdecl he_GetEntityHomeTarget(char*, int*, int*, int*);
int __cdecl ch_StartMovement(int, int, int, char*, int, char*);
int __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
void __cdecl d3_EndCameraAndUiMode(void);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x005aee90 */
void __cdecl d2_AttemptThiefRescue(char* rec)
{
	char text[0x400];
	char line[0x400];
	float f;
	int a;
	int b;
	char* ent;
	char* ent2;
	char* act;

	ent = (char*) (0x7f4ca0 + (unsigned int) g_774970 * 540);
	ent2 = (char*) (0x7f4ca0
	    + (unsigned int) *(unsigned short*) (rec + 0x27) * 540);
	d2_SetOverlayAnimation(0, 0);
	io_FormatTextBuffer(text, 0x3fea, *(unsigned char*) (ent + 0x1b1) * 2);
	if (fcn_00526120(text, 0x11) == 0) {
		goto done;
	}
	if (d2_CheckActionBlocker(ent, *(unsigned char*) (ent + 0x1b1) * 2) == 0) {
		goto done;
	}
	f = gm_GetEntitySkill(ent, 4);
	f = gm_GetEntitySkill(ent, 3) + f;
	f = gm_GetEntitySkill(ent, 2) + f;
	f = f * *(float*) 0x6629d0 + *(float*) 0x664328;
	cm_RequestModifyHealth(*(int*) (ent + 4), -(int) *(unsigned char*) (ent + 0x1b1) * 2);
	if (gm_RandomFloat01() < f) {
		int flags = -1;

		cm_BeginPacketFieldDelta(rec, *(int*) (rec + 1));
		cm_AppendPacketFieldDelta(4, 1, (int) (rec - g_aed32c) + 0x65, &flags);
		cm_RequestChangeAttribute();
		cm_SendBlockCharacter(*(int*) (ent + 4), -(int) *(unsigned char*) (ent + 0x1b1), 0);
		if (*(int*) (ent + 0x184) != 0) {
			if (he_GetEntityHomeTarget(ent, &a, &b, 0) != 0) {
				ch_StartMovement(*(int*) (ent + 4), a, b, 0, 0,
				    (char*) 0x6a69c8);
			}
		}
		act = he_StartHandlungSearch(1, 0, 0x3d);
		while (act != 0) {
			if (*(int*) (act + 0xb0) == *(int*) (rec + 1)
			    && *(int*) (ent + 4) == *(int*) (act + 0xac)) {
				break;
			}
			act = he_fn_Handlung();
		}
		if (act != 0) {
			*(int*) (act + 0x84) = cm_SendSetHE(-1, act);
		}
		io_FormatTextBuffer(line, 0x3feb);
		he_PostEntityMessage(*(int*) (ent + 4), -1, line, 0, 0x5f3, 0);
		io_FormatTextBuffer(line, 0x3fed, *(unsigned short*) ent);
		he_PostEntityMessage(*(int*) (ent2 + 4), -1, line, 0, 0x5f3, 0);
		d3_EndCameraAndUiMode();
		return;
	}
	io_FormatTextBuffer(text, 0x3fec);
	he_PostEntityMessage(*(int*) (ent + 4), -1, text, 0, 0x5f3, 0);
	io_FormatTextBuffer(text, 0x3fee, *(unsigned short*) ent);
	he_PostEntityMessage(*(int*) (ent2 + 4), -1, text, 0, 0x5f3, 0);
done:
	d3_EndCameraAndUiMode();
}
