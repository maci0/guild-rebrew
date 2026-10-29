#include "g_67fbb0.h"

extern int g_67fba8;
extern Entry2c* g_67fbb0;
extern Entry2c* g_67fbb4;
extern int g_7728c0;
extern int g_7728c4;
extern int g_7728c8;
extern int g_7728cc;
extern int g_7728d0;

int __cdecl fcn_004acc00(int*);


/* ADDRESS: GOLDTL 0x004acbb0 */
int __cdecl fcn_004acbb0(void)
{
	int r;

	g_7728c0 = -1;
	g_7728c8 = -1;
	g_7728c4 = -1;
	g_7728cc = -1;
	g_7728d0 = -1;
	r = fcn_004acc00(&g_67fba8);
	if (r == 0) {
		g_7728c4 = g_67fbb0->key;
		g_7728cc = g_67fbb4->key;
	}
	return r;
}
