#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_AddTime(char* sel, int a, int b, int c);
int __cdecl gm_TryRecordCrime(int a, int b, int c, int d, int e);
float __cdecl gm_CalcSkillDuelScore(char* a, char* b, int c);
double __cdecl gm_RandomFloat01(void);
int __cdecl cm_RequestChangeBits(int a, int b, int c, int d, int e);
int __cdecl cm_SendSetHE(int a, char* e);
int __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
int __cdecl he_PostEntityMessage(int a, int b, char* s, int c, int d, int e);
int __cdecl fcn_004e7b70(char* e, void* a, void* b);
int __cdecl fcn_0042e410(int code);
float __cdecl gm_GetEntitySkill(char* e, int a);
int __cdecl amt_AdjustOfficeHoldersFavor(char* e, int a, int b);
int __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);
int __cdecl gm_AdvanceGameTime(char* p, int id, int a, int b, int c);
int __cdecl cm_SendCopyEntityData(void* p);

/* ADDRESS: GOLDTL 0x0054f910 */
void __cdecl he_StartDuellCutscene(char* action)
{
	char* challenger;
	char* target;
	unsigned char flags;
	int level;
	int home;
	int dmg;
	float score;
	int tmp[6];
	int tmp2[6];

	*(int*) (action + 0x84) = -1;
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;



	gm_AddTime(action + 0x52, 0x18, 0, 0);
	flags = *(unsigned char*) (action + 0x78);
	*(short*) (action + 0x56) = 6;
	*(int*) (action + 0x58) = 0x1e;
	if ((flags & 2) == 0) {
		return;
	}
	challenger = gm_LookupEntityRecordById(*(int*) (action + 0xac));
	target = gm_LookupEntityRecordById(*(int*) (action + 0xb0));
	if (challenger == 0 || target == 0) {
		if ((*(int*) (challenger + 0x1c8) & 0x400) != 0
		    || (*(int*) (target + 0x1c8) & 0x400) != 0) {
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;



			gm_AddTime(action + 0x52, 0, 2, 0);
			*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
			return;
		}
	}
	level = -1;
	home = *(int*) (challenger + 0x170);
	if (home == 0) {
		home = *(int*) (target + 0x170);
	}
	if (home != 0) {
		level = *(int*) (home + 1);
	}
	gm_TryRecordCrime(4, 1, *(int*) (challenger + 4),
	    *(int*) (target + 4), level);
	if (*(unsigned char*) (target + 2) == 6
	    || *(unsigned char*) (target + 2) == 7) {
		goto big;
	}
	score = gm_CalcSkillDuelScore(target, challenger, 3);
	score = score + gm_RandomFloat01();
	if (score >= 1.0f) {
		cm_RequestChangeBits(*(int*) (challenger + 4),
		    0x1c8, 4, 0x400, 0);
		cm_RequestChangeBits(*(int*) (target + 4),
		    0x1c8, 4, 0x400, 0);
		*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;



		gm_AddTime(action + 0x52, 0x18, 0, 0);
		*(short*) (action + 0x56) = 6;
		*(int*) (action + 0x58) = 0x1e;
		if (*(unsigned char*) (challenger + 2) == 6
		    || *(unsigned char*) (challenger + 2) == 7) {
			char text[0x100];
			io_FormatTextBuffer(text, 0x1d83,
			    *(unsigned short*) (target), action + 0x52,
			    *(unsigned short*) (target));
			he_PostEntityMessage(*(int*) (challenger + 4),
			    *(int*) (challenger + 4),
			    text, 0, 0x5fa, (int) (char*) 0x6a5b08);
		}
		*(int*) (action + 0x84) = cm_SendSetHE(2, action);
		return;
	}
	level = 0;
	if (*(unsigned char*) (challenger + 2) == 6
	    || *(unsigned char*) (challenger + 2) == 7) {
		char text[0x100];
		io_FormatTextBuffer(text, 0x1d81,
		    *(unsigned short*) (target), *(unsigned short*) (target),
		    (*(unsigned char*) (target + 9) != 0) + 0x1d68);
		he_PostEntityMessage(*(int*) (challenger + 4),
		    *(int*) (challenger + 4),
		    text, 0, 0x5fa, 0);
	}
	if (*(unsigned char*) (target + 0x166) != 0) {
		home = fcn_004e7b70(target, tmp, tmp2);
		if (home != 0) {
			level = tmp[1];
		} else {
			level = (fcn_0042e410(3) & 0xffff) + 1;
		}
	}
	dmg = -9 - (int) (gm_GetEntitySkill(challenger, 4) * 8.0f);
	dmg -= fcn_0042e410(8) & 0xffff;
	amt_AdjustOfficeHoldersFavor(target, level, dmg);
	cm_RequestCopyEntityData(*(int*) (target + 4),
	    *(int*) (challenger + 4), -0x14, 1);
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;



	gm_AddTime(action + 0x52, 0, 2, 0);
	*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
	return;
big:
	{
	int blk[0x3e];
	for (home = 0; home < 0x3e; home++) {
		blk[home] = 0;
	}
	blk[2] = *(int*) (target + 4);
	blk[3] = blk[2];
	*((unsigned char*) &blk[1]) = 0x46;
	*((unsigned char*) blk + 0x36) = 9;
	blk[0x16] = *(int*) (action + 4);
	gm_AdvanceGameTime((char*) &blk[10],
	    *(unsigned short*) (target), 6, 0, 0);
	cm_SendCopyEntityData(blk);
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;



	gm_AddTime(action + 0x52, 0x18, 0, 0);
	*(short*) (action + 0x56) = 6;
	*(int*) (action + 0x58) = 0x1e;
	*(int*) (action + 0x84) = cm_SendSetHE(1, action);
	cm_RequestChangeBits(*(int*) (challenger + 4), 0x1c8, 4, 0x400, 0);
	cm_RequestChangeBits(*(int*) (target + 4), 0x1c8, 4, 0x400, 0);
	}
}
