#include <string.h>

#pragma optimize("y", off)

extern char s_689d24[];

void* __cdecl m_alloc(int, char*);
void __cdecl fcn_00426170(char*, int);
void* __cdecl fcn_004c0a60(void);

/* ADDRESS: GOLDTL 0x004c0a80 */
int __cdecl fcn_004c0a80(char* a0, int a1)
{
	char* p;
	void* q;
	volatile int n;
	volatile int v;

	if (a0 == 0) {
		return 0;
	}
	p = m_alloc(0x10, s_689d24);
	if (p == 0) {
		return 0;
	}
	n = 0x10;
	v = 0;
	memset(p, v, n);
	fcn_00426170(a0, 1);
	*(char**) p = a0;
	*(int*) (p + 4) = a1;
	q = fcn_004c0a60();
	if (q != 0) {
		*(void**) ((char*) q + 0xc) = p;
		return 1;
	}
	*(void**) 0x772d34 = p;
	return 1;
}

#pragma optimize("", on)
