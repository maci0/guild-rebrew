#include <string.h>
#include "client_data.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

extern unsigned char* lpGebaeudePROT;

void __cdecl cm_SendCopyEntityData(int a1);
char* __cdecl fcn_00502cd0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00488e10 */
void __cdecl fcn_00488e10(char* e)
{
	char s[0xf8];
	char* p;
	char* q;
	char* r;
	char* o; ENTITY_RECORD* rec;
	unsigned int f;
	int cnt;

	cnt = 1;
	rec = (ENTITY_RECORD*) g_7f4ca0;
	do {
		if (rec->entity_index != 0xffff
		    && *(int*) &rec->unk_16c == *(int*) (e + 0x16c)
		    && rec->unk_165[0] != 0
		    && (q = *(char**) rec->unk_17c) != 0
		    && *(unsigned char*) q == 0x8f) {
			cnt--;
		}
		rec++;
	} while ((int) &rec->unk_16c < 0x85a20c);
	if (cnt <= 0) {
		return;
	}
	q = *(char**) (e + 0x16c);
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) q].category != 0x1d) {
		return;
	}
	r = fcn_00502cd0(*(int*) (q + 0x5d), 2, 6, 0, 0x211);
	if (r == 0) {
		return;
	}
	memset(s, 0, 0xf8);
	q = *(char**) (e + 0x16c); *(char*) (s + 4) = 0x8f;
	*(int*) (s + 8) = *(int*) (*(unsigned short*) (q + 0x27) * 0x21c + 0x7f4ca4);
	*(int*) (s + 0xc) = *(int*) (q + 1);
	*(pos14_7f4c00*) (s + 0x28) = gm_GameTime;



	*(char*) (s + 0x36) = 1;
	*(int*) (s + 0x60) = *(int*) (r + 2);
	p = (char*) 0x7f4ca0;
	do {
		if ((int) (p + 0x17c) >= 0x85a21c) {
			break;
		}
		if (*(unsigned short*) p == 0xffff) {
			goto next;
		}
		if (*(int*) (p + 0x16c) != *(int*) (e + 0x16c)) {
			goto next;
		}
		if (*(char*) (p + 0x165) == 0) {
			goto next;
		}
		f = *(unsigned int*) (p + 0x1b4);
		if ((f & 0x10) == 0) {
			goto next;
		}
		o = *(char**) (p + 0x17c);
		if (o != 0) {
			if (*(unsigned char*) o != 0x8f) {
				goto next;
			}
			*(unsigned int*) (p + 0x1b4) = f & ~0x10;
			goto next;
		}
		o = *(char**) (p + 0x184);
		if (o == 0) {
			goto next;
		}
		if (*(int*) (o + 0x2c) != *(int*) (*(char**) (p + 0x16c) + 1)) {
			goto next;
		}
		*(unsigned int*) (p + 0x1b4) = f & ~0x10;
		if (*(unsigned char*) (p + 0x81) < *(unsigned char*) (p + 0x82)) {
			*(int*) (s + 0x58) = *(int*) (p + 4);
			*(int*) (s + 0x5c) = 1;
		} else {
			*(int*) (s + 0x58) = *(int*) (p + 4);
			*(int*) (s + 0x5c) = 2;
			if (*(unsigned char*) (p + 0x82) >= *(unsigned char*) (p + 0x84)) {
				*(int*) (s + 0x5c) = 4;
			}
		}
		cm_SendCopyEntityData((int) s);
		cnt--;
		*(int*) (p + 0x1c8) |= 4;
next:
		p += 0x21c;
	} while (cnt > 0);
}
