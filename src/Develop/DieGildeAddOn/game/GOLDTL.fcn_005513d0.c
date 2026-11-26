#include <string.h>

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern int gm_GameTime;
#include "client_actions.h"



char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDTL 0x005513d0 */
void __cdecl fcn_005513d0(char* action)
{
	char msg[0x114];
	char* entry;
	char* rec;
	int* ids;
	int v20;
	int count;
	int i;
	int state;
	float f; double factor;
	float threshold; int rec_id;

	v20 = -1;
	entry = ((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (action + 8)]);
	rec = gm_LookupEntityRecordById(*(int*) (entry + 0x5c));
	if (rec == 0 || rec[8] == 0 || entry[8] == 0)
		goto tail;
	state = *(int*) (action + 0x70);
	if (state == -2)
		goto tail;
	if (state != 0) {
		if (state != 1)
			return;
		if (*(float*) (action + 0xac) >= 3.0) {
			if (entry[2] == 6) {
				rec_id = *(int*) (rec + 4); memset(msg, 0, sizeof(msg));
				*(int*) (msg + 0xc) = *(int*) (entry + 4);
				*(int*) (msg + 0x34) = *(int*) (entry + 4);
				*(int*) (msg + 0x18) = gm_GameTime;
				*(int*) (msg + 0x1c) = g_7f4c04;
				*(int*) (msg + 0x38) = rec_id;
				msg[8] = 7;
				msg[0x26] = 0x20;
				*(int*) (msg + 0x14) = -1;
				msg[0x30] = 2;
				*(int*) (msg + 0x20) = g_7f4c08;
				*(short*) (msg + 0x24) = g_7f4c0c;
				gm_AddTime(msg + 0x18, 0, 0x1e, 0);
				fcn_004c5980(msg);
			}
			*(float*) (action + 0xac) = 0;
			if (*(int*) (entry + 0x170) != 0)
				v20 = *(int*) (*(int*) (entry + 0x170) + 1);
			if (entry[9] == 0) {
				fcn_004c4fc0(8, *(int*) (entry + 4), *(int*) (rec + 4), 0, v20, 0, 0, 2);
			} else {
				fcn_004c4fc0(8, *(int*) (rec + 4), *(int*) (entry + 4), 0, v20, 0, 0, 2);
			}
			*(int*) (action + 0x70) = 0;
			*(int*) (action + 0x52) += (gm_RandomMod(8) & 0xffff) + 1;
			return;
		}
		*(int*) (action + 0x52) += 1;
		*(float*) (action + 0xac) = *(float*) (action + 0xac) + 1.0;
		return;
	}
	count = 0;
	ids = (int*) (entry + 0x68);
	for (i = 5; i > 0; i--, ids++) {
		if (*ids != -1 && gm_LookupEntityRecordById(*ids) != 0)
			count++;
	}
	if (count != 5) {
		factor = (5.0f - (float) count) * 0.2f;
		f = (float) (factor * factor);
		threshold = (float) (f * *(float*) (action + 0xac));
		if ((1.0f - f) + gm_RandomFloat01() < threshold) {
			*(int*) (action + 0x70) = 1;
			*(int*) (action + 0x52) += 1;
			*(float*) (action + 0xac) = 0;
			return;
		}
		*(float*) (action + 0xac) = f * 0.1 + *(float*) (action + 0xac);
		return;
	}
tail:
	he_FreeAction(action);
}
