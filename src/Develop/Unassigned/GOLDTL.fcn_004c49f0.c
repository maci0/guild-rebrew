#include <string.h>

extern char* g_aed200;
extern char* g_aed324;
extern int g_14cbca0;

void __cdecl fcn_00421050(void);
unsigned short __cdecl fcn_004c3a50(char* n);

/* ADDRESS: GOLDTL 0x004c49f0 */
int __cdecl fcn_004c49f0(char* src)
{
	char* p;
	char* q;
	char** pn;

	p = g_aed200;
	if (p == 0) {
		if (g_14cbca0 != -1) {
			fcn_00421050();
		}
		return 1;
	}
	pn = (char**) (p + 0x95);
	g_aed200 = *pn;
	memcpy(p, src, 0x99);
	*(unsigned short*) (p + 1) = fcn_004c3a50(p);
	q = g_aed324;
	if (q != 0) {
		while (*(char**) (q + 0x95) != 0) {
			q = *(char**) (q + 0x95);
		}
		*(char**) (p + 0x91) = q;
		*pn = 0;
		*(char**) (q + 0x95) = p;
	} else {
		*(char**) (p + 0x91) = 0;
		*pn = 0;
		g_aed324 = p;
	}
	return 0;
}
