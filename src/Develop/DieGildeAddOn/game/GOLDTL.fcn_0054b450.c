#include "client_types.h"

unsigned short* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_CalcSkillDuelScore(char*, char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl he_FreeAction(char*);
void __cdecl fcn_00545780(char*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);
void __cdecl io_FormatTextBuffer(int, int, ...);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_SetForm(int, int);
int __cdecl d3snd_PlaySoundEffect(int, int, char*, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
int __cdecl gm_CompareGameTime(void*, void*);
void __cdecl gm_AddTime(void*, int, int, int);

extern pos14_7f4c00 gm_GameTime;
extern float g_6628a0;
/* ADDRESS: GOLDTL 0x0054b450 */
void __cdecl fcn_0054b450(char* a0)
{
	float dist;
	char buf[0x100];
	unsigned short* entityA;
	unsigned short* v4;
	unsigned short* entityC;
	char* a;

	a = a0;
	entityA = gm_LookupEntityRecordById(*(int*) (a + 0xac));
	v4 = gm_LookupEntityRecordById(*(int*) (a + 0xb0));
	entityC = gm_LookupEntityRecordById(*(int*) (a + 0xb4));
	if (*(int*) (a + 0x70) == -2 || entityA == 0 || v4 == 0 || entityC == 0) {
		he_FreeAction(a);
		if (*(int*) (a + 0x74) != 0)
			fcn_00545780(a);
		return;
	}
	if (*(int*) (a + 0x70) == -1 ||
	    (*(char*) (entityC + 1) != 6 && *(char*) (entityC + 1) != 7))
		*(int*) (a + 0x70) = 2;
	switch (*(int*) (a + 0x70)) {
	case 0:
		fcn_00545670(a, 0, 0, (char*) 0x6a5a10, 0x5ec);
		if (*(int*) (a + 0x74) == 0) {
			he_FreeAction(a);
			return;
		}
		d2_SetForm(*(int*) (*(int*) (a + 0x74) + 8), 0);
		io_AppendText(0x1763, *(unsigned short*) v4, *(unsigned short*) entityA);
		*(pos14_7f4c00*) (a + 0x44) = gm_GameTime;
		*(pos14_7f4c00*) (a + 0x52) = gm_GameTime;
		gm_AddTime(a + 0x52, 0x18, 0, 0);
		d3snd_PlaySoundEffect(-7, 0, (char*) 0x6a59fc, 0);
		(*(int*) (a + 0x70))++;
		return;
	case 1:
		if (gm_CompareGameTime((void*) 0x7f4c00, a0 + 0x52) > 0) {
			fcn_00545780(a);
			*(int*) (a + 0x70) = 2;
			return;
		}
		if (*(int*) 0x100f884 == *(int*) (*(int*) (a + 0x74) + 8) &&
		    *(int*) 0x100f1dc != -1) {
			if (*(int*) 0x100f1dc == 2) {
				io_FormatTextBuffer((int) buf, 0x1764, *(unsigned short*) entityC,
				             *(unsigned short*) entityA);
				he_PostEntityMessage(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
				cm_RequestCopyEntityData(*(int*) (entityA + 2), *(int*) (entityC + 2), -0x14, 1);
			} else if (*(int*) 0x100f1dc == 1) {
				io_FormatTextBuffer((int) buf, 0x1765, *(unsigned short*) entityC,
				             *(unsigned short*) entityA);
				he_PostEntityMessage(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
				cm_RequestCopyEntityData(*(int*) (v4 + 2), *(int*) (entityC + 2), -0xf, 1);
				cm_RequestCopyEntityData(*(int*) (entityC + 2), *(int*) (v4 + 2), -0xf, 1);
			}
			fcn_00545780(a);
			he_FreeAction(a);
			return;
		}
		return;
	case 2:
		dist = gm_CalcSkillDuelScore((char*) v4, (char*) entityA, 4);
		if (1.0f <= gm_RandomFloat01() + dist) {
			io_FormatTextBuffer((int) buf, 0x1764, *(unsigned short*) entityC, *(unsigned short*) entityA);
			v4 = (unsigned short*) *(int*) (v4 + 2);
			he_PostEntityMessage((int) v4, (int) v4, buf, 0, 0x5fa, 0);
			cm_RequestCopyEntityData(*(int*) (entityA + 2), *(int*) (entityC + 2), -0x14, 1);
		} else {
			io_FormatTextBuffer((int) buf, 0x1765, *(unsigned short*) entityC, *(unsigned short*) entityA);
			he_PostEntityMessage(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
			cm_RequestCopyEntityData(*(int*) (v4 + 2), *(int*) (entityC + 2), -0xf, 1);
			cm_RequestCopyEntityData(*(int*) (entityC + 2), *(int*) (v4 + 2), -0xf, 1);
		}
		he_FreeAction(a);
	}
}
