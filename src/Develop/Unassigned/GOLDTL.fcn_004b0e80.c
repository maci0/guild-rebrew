#include <string.h>

typedef struct {
	short v[7];
} stamp14_4b0e80;
// SIZE 0xe

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	unsigned char type;
	char pad3[9];
	unsigned char faith;
	char padd[0x21c - 0xd];
} Entity_4b0e80;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char* g_773da8;
extern char g_7f4ca0[];

int __cdecl fcn_0064eeec(char*);
void __cdecl fcn_004c5530(void*);

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


/* ADDRESS: GOLDTL 0x004b0e80 */
int __cdecl fcn_004b0e80(int a1, int a2, char* a3)
{
	char m[0xf8];
	char names[2][16] = { "KATHOLISCH", "EVANGELISCH" };
	int per;
	char lo[4];
	char hi[4];
	int cnt;
	int faith;
	int i;
	int n;
	int num;
	int k;

	if (*a3 != '-') {
		return 0;
	}
	a3++;
	for (i = 0; i < 2; i++) {
		if (memcmp(a3, names[i], strlen(names[i])) == 0) {
			break;
		}
	}
	if (i == 0) {
		faith = 1;
	} else if (i == 1) {
		faith = 0;
	} else {
		return 0;
	}
	a3 += strlen(names[i]);
	if (*a3 != '_') {
		return 0;
	}
	n = 0;
	a3++;
	*(int*) hi = 0;
	*(int*) lo = 0;
	while (*a3 != 0 && *a3 != '_' && n < 3) {
		if (*a3 < '0' || *a3 > '9') {
			return 0;
		}
		hi[n] = *a3;
		n++;
		a3++;
	}
	if (*a3 == 0 || n == 0) {
		return 0;
	}
	n = 0;
	a3++;
	while (*a3 != 0 && n < 3) {
		if (*a3 < '0' || *a3 > '9') {
			return 0;
		}
		lo[n] = *a3;
		n++;
		a3++;
	}
	if (n == 0) {
		return 0;
	}
	per = fcn_0064eeec(hi);
	num = fcn_0064eeec(lo);
	if (per < 1 || per > 0x50 || num < 1 || num > 8) {
		return 0;
	}
	cnt = 0;
	for (i = 0; i < 0x300; i++) {
		if (((Entity_4b0e80*)g_7f4ca0)[i].slot != 0xffff && ((Entity_4b0e80*)g_7f4ca0)[i].type <= 4 && ((Entity_4b0e80*)g_7f4ca0)[i].faith == faith) {
			cnt++;
		}
	}
	k = (int) ((float) cnt * per * 0.01f);
	if (k == 0) {
		return 1;
	}
	num = MAX(MIN(num, k / 3), 1);
	memset(m, 0, sizeof(m));
	m[4] = (char) 0x81;
	*(int*) (m + 8) = *(int*) (g_773da8 + 4);
	*(int*) (m + 0x60) = faith;
	*(int*) (m + 0xc) = -1;
	m[0x36] = 2;
	*(int*) (m + 0x58) = k;
	*(int*) (m + 0x5c) = num;
	*(stamp14_4b0e80*) (m + 0x28) = (*(stamp14_4b0e80*)&g_7f4c00);
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	fcn_004c5530(m);
	return 1;
}
