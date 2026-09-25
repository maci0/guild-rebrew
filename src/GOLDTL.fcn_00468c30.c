#include <string.h>

extern char* g_1015ea0;

// FUNCTION: GOLDTL 0x468c30
// SIZE: 145
void __cdecl fcn_00468c30(int slot, int n, char* out)
{
	char buf[0x400];
	char* p;
	char* q;
	int i;

	i = 0;
	strcpy(buf, g_1015ea0 + slot * 0x2f4 + 0xe8);
	q = buf;
	p = strchr(buf + 1, '|');
	for (; i < n; i++) {
		if (p == 0) {
			return;
		}
		q = p;
		p = strchr(p + 1, '|');
	}
	if (p != 0) {
		*p = 0;
		strcpy(out, q);
	}
}
