


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern float flt_0_0;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl ahm_FindRecipePrototypeByKey(int);
float __cdecl ahm_CalcResearchStep(char*, char*, int*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl he_AssignActionSlot(char*, int, int, char*);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl he_FreeAction(char*);

void __cdecl he_StartAhmRefineRecipe(char* u)
{
	char* h;
	char* p;

	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h != 0) {
		p = ahm_FindRecipePrototypeByKey(*(int*) (u + 0xb0));
		if (p != 0) {
			*(float*) (u + 0xb4) = ahm_CalcResearchStep(h, p, (int*) (u + 0xbc));
			if (!(*(float*) (u + 0xb4) <= flt_0_0)) {
				*(int*) (u + 0xb8) = *(int*) (u + 0xbc);
				*(pos14_7f4c00*) (u + 0xc0) = gm_GameTime;
				*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
				gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
				*(int*) (u + 0x70) = 0;
				he_AssignActionSlot(*(char**) (h + 0x16c),
				    fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b), *(unsigned short*) h, u);
				d3snd_PlayWorkerOrderVoice();
				return;
			}
		}
	}
	he_FreeAction(u);
}
