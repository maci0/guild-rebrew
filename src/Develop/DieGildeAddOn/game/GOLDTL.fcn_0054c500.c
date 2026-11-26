


// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	unsigned char level;
	char pad9[0x213];
};

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004c4450(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_005c6270(char*, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_00507ed0(float, float);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_00500cb0(char*, pos14_7f4c00*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunAction53(char* e)
{
	char* a;
	char* b;
	int mult;
	int i;
	int idx;
	int v;
	float f;

	a = gm_LookupEntityRecordById(*(int*) (e + 0xbc));
	b = gm_LookupEntityRecordById(*(int*) (e + 0xc));
	mult = 1;
	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		he_FreeAction(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (*(int*) (e + 0x84) != -1 && fcn_004c4450(*(int*) (e + 0x84)) == 0) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	if (a == 0) {
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
		fcn_004c5620(-1, e);
		return;
	}
	if (b != 0) {
		mult = (fcn_005c6270(b, 0x2c5) != 0) + 1;
	}
	idx = *(int*) (e + 0xc4);
	i = 0;
	while (*(int*) (e + 0xcc) != 0 && i < 16) {
		if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_index) != 0xffff && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_id) != *(int*) (e + 0xbc) && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_type) < 10
		    && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].health) > 0) {
			f = -fcn_00507ed0(*(float*) (e + 0xd0), gm_GetEntitySkill((char*) ((struct house*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx]), 4));
			v = (int) (f * 10.0f + 1.0f) * mult;
			fcn_004c54c0(*(int*) (e + 0xbc), (((ENTITY_RECORD_VIEW*)g_7f4ca0)[idx].entity_id), v, 1);
		}
		i++;
		*(int*) (e + 0xcc) = *(int*) (e + 0xcc) - 1;
		idx = (*(int*) (e + 0xc8) + idx) % 768;
	}
	*(int*) (e + 0xc4) = idx;
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	if (fcn_00500cb0(e + 0xac, &gm_GameTime) == 1) {
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 1, 0, 0);
		return;
	}
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	*(int*) (e + 0x84) = fcn_004c5620(-1, e);
}
