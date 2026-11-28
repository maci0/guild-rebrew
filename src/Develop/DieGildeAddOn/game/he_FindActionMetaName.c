


#include <string.h>

// SIZE 0x20
typedef struct {
	int kind;
	char name[16];
	int timed;
	char pad18[8];
} Job;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;
extern s_7e2ac0 g_7e2ac0[48];
extern float g_696540[];
extern float g_696550[];

int __cdecl gm_GetSeason(int* stamp);

int __cdecl he_FindActionMetaName(char* ent, int owner, char* out)
{
	int hour;
	int i;
	float t;

	hour = gm_GetSeason(&(*(int*)&gm_GameTime));
	for (i = 0; ((Job*)g_7e2ac0)[i].kind != 0; i++) {
		if (((Job*)g_7e2ac0)[i].kind == *(unsigned char*) (ent + 0x180)) {
			if ((*(unsigned int*) (ent + 0x1cc) & 0x1000000) != 0) {
				break;
			}
			if (*(int*) (ent + 0x16c) != owner) {
				break;
			}
			if (((Job*)g_7e2ac0)[i].timed != 0) {
				t = (float) ((*(int*)&gm_GameTimeHour) & 0xffff);
				if (!(t < g_696550[hour])) {
					break;
				}
				if (!(t >= g_696540[hour])) {
					break;
				}
			}
			strcpy(out, ((Job*)g_7e2ac0)[i].name);
			return 1;
		}
	}
	return 0;
}
