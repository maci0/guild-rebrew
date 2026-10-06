// FUNCTION: GOLDTL 0x4ce090
// FUNCTION: GOLD 0x004cd510

#include "g_9baa20.h"

extern int g_9baadc;
extern unsigned char g_9baa96;
extern Rec9baa20 g_9baa20;
extern int g_9baa24[8];

char* __cdecl fcn_004ce190(int);

int __cdecl fcn_004ce090(void)
{
	unsigned int need;
	unsigned int cnt;
	int i;
	char* r;

	if (g_9baadc == 0x3f)
		need = g_9baa96;
	else
		need = g_9baa96;
	if (g_9baa20.count < need)
		return 0;
	cnt = 0;
	for (i = 0; i < 8; i++) {
		if (g_9baa24[i] != 0) {
			r = fcn_004ce190(g_9baa24[i]);
			if (r == 0)
				return 0;
			if (*(int*) (r + 4) == 1)
				cnt++;
		}
	}
	return cnt == need;
}
