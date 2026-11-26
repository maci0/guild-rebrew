


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern float g_696550[];
extern float g_696540[];

int __cdecl gm_GetSeason(pos14_7f4c00*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ahm_CheckFlag(char*);
char* __cdecl ahm_FindRecipeSlot(char*, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_005b3190(char*, char*, int, int);
void __cdecl fcn_004eea30(char*, int, float);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl he_FreeAction(char*);
int __cdecl ahm_HasActiveLabFeature(char*, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl gm_GetElapsedMinutes(pos14_7f4c00*, pos14_7f4c00*);

void __cdecl he_RunAhmRefineRecipe(char* u)
{
	int k;
	char* h;
	char* o;
	char* s;
	int q;
	int t;

	k = gm_GetSeason(&gm_GameTime);
	s = 0;
	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	if (h == 0 || ahm_CheckFlag(h) == 0 || (s = ahm_FindRecipeSlot(h, *(int*) (u + 0xb0))) == 0) {
		*(int*) (u + 0x70) = -2;
	}
	if (*(int*) (u + 0x70) != -2) {
		t = (unsigned short) gm_GameTime.b;
		if (!(t >= g_696550[k]) && !(t < g_696540[k])) {
			if (ahm_HasActiveLabFeature(*(char**) (h + 0x16c), 0x24b) != 0) {
				*(pos14_7f4c00*) (u + 0xc0) = gm_GameTime;
				gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 0xf, 0);
				return;
			}
			if (*(int*) (u + 0x70) == 1) {
				q = fcn_00502cd0(*(int*) (*(char**) (h + 0x16c) + 0x5d), 2, 6, 0, 0x24b);
				o = gm_LookupEntityRecordById(*(int*) (u + 0xc));
				if (o != 0) {
					fcn_005b3190(o, h, q, *(int*) (u + 0xb0));
				}
				fcn_004eea30(h, *(int*) (u + 0xb0), *(float*) (u + 0xb4) + *(float*) (s + 4));
				fcn_00529160(0, 0, *(unsigned short*) h, 0);
				he_FreeAction(u);
				return;
			}
			if (*(int*) (u + 0x70) != 0) {
				return;
			}
			*(int*) (u + 0xb8) -= gm_GetElapsedMinutes((pos14_7f4c00*) (u + 0xc0), &gm_GameTime);
			*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 5, 0);
			*(pos14_7f4c00*) (u + 0xc0) = gm_GameTime;
			if (*(int*) (u + 0xb8) <= 0) {
				*(int*) (u + 0x70) = 1;
			}
			return;
		}
		*(pos14_7f4c00*) (u + 0xc0) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (u + 0x52), 1, 0, 0);
		return;
	}
	he_FreeAction(u);
}
