typedef struct {
	int who;
	unsigned short op;
} fcn_004bbbd0_msg;

typedef int(__cdecl* fcn_004bbbd0_handler)(fcn_004bbbd0_msg*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern fcn_004bbbd0_handler g_6811b8[];

char* __cdecl gm_LookupEntityRecordById(int);
#include <string.h>

typedef struct {
	short v[7];
} stamp14;

extern int g_7728e0;

__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
int __cdecl fcn_004bbce0(int);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x004bbbd0 */
int __cdecl fcn_004bbbd0(fcn_004bbbd0_msg* m)
{
	char* p;

	if ((*(int*)&g_7f4c00) < 8)
		return 0;
	if (m == 0)
		return -1;
	p = gm_LookupEntityRecordById(m->who);
	if (p == 0 || *(unsigned char*) (p + 0x1b1) > 0)
		return 0x400;
	if (m->op < 0x45)
		return g_6811b8[m->op](m);
	return -2;
}

/* ADDRESS: GOLD 0x004bb720 */
/* ADDRESS: GOLDTL 0x004bbc30 */
int __cdecl fcn_004bbc30(int a1, int a2)
{
	char m[0xf8];
	int n;
	int i;

	n = fcn_004bbce0(a1 + 1);
	g_7728e0 = GetTickCount();
	memset(m, 0, sizeof(m));
	m[4] = 0x42;
	*(int*) (m + 8) = a2;
	*(int*) (m + 0xc) = -1;
	*(stamp14*) (m + 0x28) = (*(stamp14*)&g_7f4c00);
	m[0x36] = 1;
	for (i = 0; i < n; i++) {
		*(short*) (m + 0x5c) = fcn_004bbce0(0x45);
		*(int*) (m + 0x58) = a2;
		fcn_004c5530(m);
	}
	return n;
}

/* ADDRESS: GOLDTL 0x004bbce0 */
unsigned int __cdecl fcn_004bbce0(unsigned int n)
{
	if (n == 0)
		return 0;
	(*(unsigned int*)&g_7728e0) = (*(unsigned int*)&g_7728e0) * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &(*(unsigned int*)&g_7728e0) + 1) % 0x7fffu % n;
}
