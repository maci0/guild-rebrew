


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
int* __cdecl ahm_PickRandomUnknownRecipe(char*);
int __cdecl ahm_CalcUnlockDuration(char*, int*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl he_AssignActionSlot(char*, int, int, char*);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl he_FreeAction(char*);

void __cdecl he_StartAhmUnlockRecipe(char* u)
{
	char* h;
	int* p;
	int r;

	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h != 0) {
		p = ahm_PickRandomUnknownRecipe(h);
		if (p != 0) {
			*(int*) (u + 0xb0) = *p;
			r = ahm_CalcUnlockDuration(h, p);
			*(int*) (u + 0xb4) = r;
			*(int*) (u + 0xb8) = r;
			*(pos14_7f4c00*) (u + 0xbc) = gm_GameTime;
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
			*(int*) (u + 0x70) = 0;
			he_AssignActionSlot(*(char**) (h + 0x16c), fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b),
			    *(unsigned short*) h, u);
			d3snd_PlayWorkerOrderVoice();
			return;
		}
	}
	he_FreeAction(u);
}
