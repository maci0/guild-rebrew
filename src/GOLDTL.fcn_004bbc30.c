// FUNCTION: GOLD 0x004bb720
// SIZE: 172
// FUNCTION: GOLDTL 0x4bbc30
// SIZE: 172

#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern int g_7728e0;

__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
int __cdecl fcn_004bbce0(int);
void __cdecl fcn_004c5530(void*);

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
