/* Formats the network statistics summary and its 106 hourly rows. */

#include <stdio.h>

extern unsigned int g_6b7d58;
extern unsigned int g_6b7d54;
extern unsigned int g_6b7d60;
extern unsigned int g_6b7d5c;
extern double g_662c38;


/* ADDRESS: GOLDTL 0x00420bf0 */
void __cdecl fcn_00420bf0(void)
{
	unsigned int i;
	char buf[256];
	unsigned int* p;

	sprintf(buf, (char*) 0x678aa4, g_6b7d58, g_6b7d54, g_6b7d60, g_6b7d5c);
	p = (unsigned int*) 0x14cbccc;
	for (i = 0; i < 0x6a; i++, p += 4) {
		sprintf(buf, (char*) 0x678a40, i,
		        p[-3],
		        (double) p[-3] * g_662c38 / g_6b7d58,
		        p[-2],
		        (double) p[-2] * g_662c38 / g_6b7d54,
		        p[-1],
		        (double) p[-1] * g_662c38 / g_6b7d60,
		        p[0],
		        (double) p[0] * g_662c38 / g_6b7d5c);
	}
}
