#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_004f4830(int idx, void* dst);
char* __cdecl gm_LookupEntityRecordById(int a1);
int __cdecl gm_ResolveEntityById(char** out, int a2, int a3, int a4);
float __cdecl fcn_004f4ed0(unsigned short* key);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_HasActiveSpecialObject(char* a1, int a2);
int __cdecl cm_SendAddStraftat(void* a1);

#pragma pack(1)
typedef struct {
	int a;
	pos14_7f4c00 pos;
	int b;
	int c;
	short d;
	char e;
	int f;
	int g;
	int h;
	int i;
} CRIME_REPORT_MSG;
#pragma pack()

/* ADDRESS: GOLDTL 0x004f4f60 */
int __cdecl gm_TryRecordCrime(int idx, int id, int actorId, int targetId, int locationId)
{
	char rec[36];
	CRIME_REPORT_MSG msg;
	char* h1;
	int origActorId;

	float f;


	if (!fcn_004f4830(idx, rec)) {
		goto fail;
	}
	origActorId = actorId;
	h1 = gm_LookupEntityRecordById(origActorId);
	gm_LookupEntityRecordById(targetId);
	gm_ResolveEntityById((char**)&actorId, 0, 0, locationId);
	switch ((unsigned char) *(int*) (rec + 0x14)) {
	case 1:
		if (*(int*) (rec + 0x18) != id) {
			goto fail;
		}
		break;
	case 2:
		if (*(int*) (rec + 0x18) == id) {
			goto fail;
		}
		break;
	case 6:
		if (*(int*) (rec + 0x18) > id) {
			goto fail;
		}
		break;
	case 5:
		if (*(int*) (rec + 0x18) >= id) {
			goto fail;
		}
		break;
	case 4:
		if (*(int*) (rec + 0x18) < id) {
			goto fail;
		}
		break;
	case 3:
		if (*(int*) (rec + 0x18) <= id) {
			goto fail;
		}
		break;
	case 7:
		if (*(int*) (rec + 0x18) == id || *(int*) (rec + 0x18) == 2) {
			goto fail;
		}
		break;
	default:
		goto fail;
	}
	f = fcn_004f4ed0((unsigned short*) h1);
	if (gm_RandomFloat01() >= f) {
		goto fail;
	}
	if (gm_HasActiveSpecialObject(h1, 0x22a) != 0) {
		if (gm_RandomFloat01() > 0.5) {
			goto fail;
		}
	}
	msg.pos = gm_GameTime;
	msg.f = id;
	msg.e = rec[0];
	msg.b = targetId;
	msg.c = origActorId;
	msg.d = *(short*) (rec + 0x10);
	msg.h = 1;
	msg.g = locationId;
	return cm_SendAddStraftat(&msg);
fail:
	return -1;
}
