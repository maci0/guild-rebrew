#include <math.h>
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern char gm_EntitySlotTable[];


int __cdecl gm_RandomMod(int);
void __cdecl he_FreeAction(char*);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(char, char*);

/* ADDRESS: GOLDTL 0x0055a920 */
void __cdecl he_RunAction0x81(char* rec)
{
	int cnt;
	int flag;
	double d;
	int n;
	int r;
	int want;
	char* slot;
	unsigned short si;
	int left;

	cnt = 0;
	flag = 1 - *(int*) (rec + 0xb4);
	if (*(int*) (rec + 0x70) < 0 || *(int*) (rec + 0xb0) <= 0 ||
	    *(int*) (rec + 0xac) <= 0) {
		he_FreeAction(rec);
		return;
	}
	if ((*(unsigned char*) (rec + 0x78) & 4) != 0) {
		return;
	}
	n = *(int*) (rec + 0xb0);
	r = *(int*) (rec + 0xac);
	d = (double) r;
	if (d < ceil((double) (r + n))) {
		d = (double) *(int*) (rec + 0xac);
	} else {
		d = ceil((double) (*(int*) (rec + 0xb0) + *(int*) (rec + 0xac)));
	}
	want = (int) d;
	si = (unsigned short) gm_RandomMod(0x300);
	left = 0x300;
	do {
		if (cnt >= want) {
			break;
		}
		slot = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[si]);
		if (*(unsigned short*) slot != 0xffff &&
		    *(unsigned char*)&((ENTITY_RECORD_VIEW*)slot)->entity_type <= 4 &&
		    *(unsigned char*)&((ENTITY_RECORD_VIEW*)slot)->side == *(int*) (rec + 0xb4)) {
			cm_BeginPacketFieldDelta(slot, *(int*)&((ENTITY_RECORD_VIEW*)slot)->entity_id);
			cm_AppendPacketFieldDelta(1, 1, 0xc, (char*) &flag);
			cm_RequestChangeAttribute();
			cnt++;
		}
		si = (unsigned short) ((si + 1) % 0x300);
	} while (--left);
	if (cnt < want) {
		*(pos14_7f4c00*) (rec + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (rec + 0x52), 0, 5, 0);
		*(int*) (rec + 0x84) = cm_SendSetHE(-1, rec);
	} else {
		*(int*) (rec + 0xb0) = *(int*) (rec + 0xb0) - 1;
		*(int*) (rec + 0xac) = *(int*) (rec + 0xac) - want;
		*(pos14_7f4c00*) (rec + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (rec + 0x52), 0x18, 0, 0);
		*(int*) (rec + 0x84) = cm_SendSetHE(0, rec);
	}
}
