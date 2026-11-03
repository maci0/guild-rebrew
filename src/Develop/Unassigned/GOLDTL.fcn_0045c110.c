#include <string.h>

extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_10405c4;
extern int g_10404c0[32];
extern int g_10405c0;
extern int g_10405c8;
extern int g_6b7fac;
extern int g_6b8af0;

void __cdecl fcn_0045bfb0(char* p);

/* ADDRESS: GOLDTL 0x0045c110 */
void __cdecl fcn_0045c110(void)
{
	unsigned int i;
	char* p;

	p = g_104049c;
	for (i = 0; i < g_10404a0; i++, p += 0x70) {
		while (*(int*) (p + 0x40) > 0) {
			fcn_0045bfb0(p);
		}
	}
	memset(g_104049c, 0, g_10404a0 * 0x70);
	g_10405c4 = 0;
	g_10404c0[3] = 0;
	g_10404c0[2] = 0;
	g_10404c0[1] = 0;
	g_10404c0[0] = 0;
	g_10405c0 = 0;
	g_10405c8 = g_6b7fac;
	g_6b8af0 = 0;
}
