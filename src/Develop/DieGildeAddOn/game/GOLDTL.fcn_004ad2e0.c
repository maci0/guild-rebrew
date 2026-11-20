#include <string.h>
#include "client_data.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

typedef struct Hit4ad2e0 {
	ENTITY_RECORD* p;
	float f;
} Hit4ad2e0;

void __cdecl fcn_004ad4d0(int a1);
char* __cdecl fcn_004e9110(int kind);
float __cdecl fcn_004ad500(unsigned char* a1, unsigned short* a2, int a3, int a4);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
int __cdecl io_FormatTextBuffer(char* buf, int a, int b);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);

/* ADDRESS: GOLDTL 0x004ad2e0 */
void __cdecl fcn_004ad2e0(void)
{
	Hit4ad2e0 hits[4];
	char text[0x104];
	int idx;
	int requiredMask;
	int v4;
	int excludedMask;
	int v6;
	int count;
	int i;
	int pos;
	char* obj;
	ENTITY_RECORD* rec;
	float f;

	if (gm_GameTime.a < 4) {
		return;
	}
	idx = gm_GameTime.a % 4;
	if (idx == 0) {
		return;
	}
	requiredMask = *(int*) (idx * 4 + 0x664e18);
	v4 = *(int*) (idx * 4 + 0x664e0c);
	excludedMask = *(int*) (idx * 4 + 0x664e24);
	idx--;
	v6 = *(int*) (idx * 4 + 0x664e34);
	fcn_004ad4d0(idx);
	obj = fcn_004e9110(v4);
	if (obj == 0) {
		return;
	}
	count = 0;
	memset(hits, 0, sizeof(hits));
	rec = (ENTITY_RECORD*) 0x7f4ca0;
	do {
		if (!(excludedMask & rec->entity_flags) && (requiredMask & rec->entity_flags) && rec->unk_00d >= 7 &&
		    (rec->entity_state == 6 || rec->entity_state == 7 ||
		     rec->entity_state == 5 || rec->entity_state == 4 ||
		     rec->entity_state == 3 || rec->entity_state == 2)) {
			f = fcn_004ad500((unsigned char*) rec, (unsigned short*) obj, v4, 0);
			for (i = 4; i > 0; i--) {
				if (!(f > hits[i - 1].f)) {
					break;
				}
			}
			pos = i;
			if (pos < 4) {
				for (i = 3; i > pos; i--) {
					hits[i] = hits[i - 1];
				}
				hits[pos].f = f;
				hits[pos].p = rec;
				count++;
			}
		}
		rec++;
	} while ((int) &rec->entity_state < 0x85a0a2);
	if (count >= 4) {
		count = 4;
	}
	for (i = 0; i < count; i++) {
		if (hits[i].p == 0) {
			return;
		}
		fcn_004c5420(hits[i].p->entity_id, 0x1cc, 4, v6, 0);
		if ((char) hits[i].p->entity_state == 6 || (char) hits[i].p->entity_state == 7) {
			io_FormatTextBuffer(text, 0x42b1, (hits[i].p->gender != 0 ? 0x28 : 0) + 0x253 + v4);
			fcn_00545d40(hits[i].p->entity_id, -1, text, 0, 0x5fd, "_NACHRICHTEN_NEU_14");
		}
	}
}
