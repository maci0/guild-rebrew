#include <math.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

int __cdecl fcn_0064d228(void);
int __cdecl fcn_0042e410(int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(char, char*);

/* ADDRESS: GOLDTL 0x0055a920 */
void __cdecl fcn_0055a920(char* rec)
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
		fcn_00546190(rec);
		return;
	}
	if ((*(unsigned char*) (rec + 0x78) & 4) != 0) {
		return;
	}
	n = *(int*) (rec + 0xb0);
	r = *(int*) (rec + 0xac);
	d = (double) r;
	if (ceil((double) (r + n)) == d) {
		d = ceil((double) (r + n));
	} else {
		d = (double) r;
	}
	want = fcn_0064d228();
	si = (unsigned short) fcn_0042e410(0x300);
	left = 0x300;
	do {
		if (cnt >= want) {
			break;
		}
		slot = g_7f4ca0 + si * 0x21c;
		if (*(unsigned short*) slot != 0xffff &&
		    *(unsigned char*) (slot + 2) <= 4 &&
		    *(unsigned char*) (slot + 0xc) == *(int*) (rec + 0xb4)) {
			fcn_004c4510(slot, *(int*) (slot + 4));
			fcn_004c4570(1, 1, 0xc, (char*) &flag);
			fcn_004c5360();
			cnt++;
		}
		si = (unsigned short) ((si + 1) % 0x300);
	} while (--left);
	if (cnt < want) {
		*(pos14_7f4c00*) (rec + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (rec + 0x52), 0, 5, 0);
		*(int*) (rec + 0x84) = fcn_004c5620(-1, rec);
	} else {
		*(int*) (rec + 0xb0) = *(int*) (rec + 0xb0) - 1;
		*(int*) (rec + 0xac) = *(int*) (rec + 0xac) - want;
		*(pos14_7f4c00*) (rec + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (rec + 0x52), 0x18, 0, 0);
		*(int*) (rec + 0x84) = fcn_004c5620(0, rec);
	}
}
