#include "client_types.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern pos14_7f4c00 gm_GameTime;
extern char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

void __cdecl he_FreeAction(char*);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl fcn_00558370(char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDTL 0x00558d10 */
void __cdecl fcn_00558d10(char* e)
{
	char buf[0x200];
	pos14_7f4c00* clock;
	char* p;
	int idx;
	unsigned char c;
	unsigned int bit_lo;
	unsigned int bit_hi;
	int n;

	clock = (pos14_7f4c00*) (e + 0x52);
	*clock = gm_GameTime;
	idx = *(int*) (e + 0xb8);
	n = 0x100;
	do {
		p = lpGebaeudeINST + idx * 0xa9;
		bit_hi = 0;
		bit_lo = 0;
		c = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[(unsigned int) *(unsigned char*) p].category;
		if (c > 31) {
			bit_hi = 1U << (c - 32);
		} else {
			bit_lo = 1U << c;
		}
		if (*(unsigned short*) (p + 0x27) != 0xffff
		    && ((bit_lo & 0x807c4110U) != 0 || (bit_hi & 1) != 0)) {

			break;
		}
		p = 0;
		n--;
		idx = (idx + *(int*) (e + 0xbc)) % 0x100;
	} while (n != 0);
	*(int*) (e + 0xb8) = (*(int*) (e + 0xbc) + idx) % 0x100;
	if (p == 0) {
		he_FreeAction(e);
	} else {
		io_FormatTextBuffer(buf, "EvtSensenmann: next target = %G", p);
	}
	*(int*) (e + 0xb4) = *(int*) (p + 1);
	if (fcn_00558370(e) == 0) {
		he_FreeAction(e);
	}
	gm_AddTime(clock, 0, 0xf, 0);
}
