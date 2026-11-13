#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

void __cdecl fcn_00546190(char*);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl fcn_00558370(char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

/* ADDRESS: GOLDTL 0x00558d10 */
void __cdecl fcn_00558d10(char* e)
{
	char buf[0x200];
	pos14_7f4c00* clock;
	char* q;
	char* p;
	int idx;
	unsigned char c;
	unsigned int bit_lo;
	unsigned int bit_hi;
	int n;

	clock = (pos14_7f4c00*) (e + 0x52);
	*clock = g_7f4c00;
	idx = *(int*) (e + 0xb8);
	n = 0x100;
	p = 0;
	do {
		q = lpGebaeudeINST + idx * 0xa9;
		c = *(unsigned char*) (lpGebaeudePROT + (unsigned int) *(unsigned char*) q * 0x24d);
		bit_lo = 0;
		bit_hi = 0;
		if (c > 31) {
			bit_hi = 1U << ((c - 32) & 31);
		} else {
			bit_lo = 1U << c;
		}
		if (*(unsigned short*) (q + 0x27) != 0xffff
		    && ((bit_lo & 0x807c4110U) != 0 || (bit_hi & 1) != 0)) {
			p = q;
			break;
		}
		n--;
		idx = (idx + *(int*) (e + 0xbc)) % 0x100;
	} while (n != 0);
	*(int*) (e + 0xb8) = (*(int*) (e + 0xbc) + idx) % 0x100;
	if (p != 0) {
		io_FormatTextBuffer(buf, "EvtSensenmann: next target = %G", p);
	} else {
		fcn_00546190(e);
	}
	*(int*) (e + 0xb4) = *(int*) (p + 1);
	if (fcn_00558370(e) == 0) {
		fcn_00546190(e);
	}
	fcn_00500bb0(clock, 0, 0xf, 0);
}
