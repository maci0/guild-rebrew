#include <string.h>

void* __cdecl fcn_00466190(int idx);
char* __cdecl fcn_0047b620(char* p, int i);

/* ADDRESS: GOLDTL 0x0046b520 */
int __cdecl fcn_0046b520(char* a0, int a1)
{
	int len;
	int total;
	int i;
	char c;
	void* tbl;
	char* entry;

	total = 0;
	len = strlen(a0);
	tbl = fcn_00466190(a1);
	for (i = 0; i < len; i++) {
		c = a0[i];
		if (c != '~') {
			entry = fcn_0047b620((char*) tbl, (unsigned char) c);
			if (i != 0 && a0[i - 1] != ' ')
				total -= *(unsigned short*) (entry + 0x11);
			if (c != ' ')
				total += *(unsigned short*) (entry + 0x15) + *(int*) 0x67d384;
			else
				total += *(unsigned short*) (entry + 0x15) + *(int*) 0x67d380 + *(int*) 0x67d384;
		}
	}
	return *(int*) 0x67d384 + total;
}
