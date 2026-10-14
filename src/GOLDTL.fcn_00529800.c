int* __cdecl fcn_004ce610(char*);

// SIZE 0x20

#include "client_types.h"
extern s_7e2ac0 g_7e2ac0[48];

/* ADDRESS: GOLD 0x00524940 */
/* ADDRESS: GOLDTL 0x00529800 */


int __cdecl fcn_00529800(char* a, int* out)
{
	int n;
	int i;
	unsigned char* s;
	int* p;

	n = 0;
	s = *(unsigned char**) (a + 0x17c);
	if (s != 0 && *s != 0) {
		for (i = 0; i < 48; i++) {
			if (g_7e2ac0[i].key == *s) {
				out[n++] = g_7e2ac0[i].v;
				if (g_7e2ac0[i].w != -1) {
					out[n++] = *(unsigned short*) (s + g_7e2ac0[i].w) + 0xdf;
					break;
				}
			}
		}
	}
	p = fcn_004ce610(a);
	if (p != 0 && *p != 0) {
		out[n++] = *p + 0xdf;
	}
	return n;
}
