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

extern int g_67fbac;

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

/* ADDRESS: GOLDTL 0x004acee0 */
void __cdecl fcn_004acee0(void)
{
	g_7728c4 = g_67fbb0->key;
	g_7728cc = g_67fbb4->key;
}

/* ADDRESS: GOLD 0x004ad010 */
/* ADDRESS: GOLDTL 0x004ad130 */
char* __cdecl fcn_004ad130(int id, int* kind)
{
	int i;

	for (i = 0; i < g_67fba8; i++) {
		if (*(int*) ((char*) g_67fbb0 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x27;
			return (char*) g_67fbb0 + i * 0x2c;
		}
	}
	for (i = 0; i < g_67fbac; i++) {
		if (*(int*) ((char*) g_67fbb4 + i * 0x2c) == id) {
			if (kind != 0)
				*kind = 0x26;
			return (char*) g_67fbb4 + i * 0x2c;
		}
	}
	return 0;
}
