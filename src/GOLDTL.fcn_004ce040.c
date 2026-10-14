


#include "g_9ba3a0.h"

extern int g_772e8c;
extern int g_9ba9f4;
extern logrec g_9ba3a0[15];

char* __cdecl fcn_004ce040(void)
{
	int n;
	int m;

	n = g_772e8c;
	m = g_9ba9f4;
	if (n == m) {
		return 0;
	}
	n++;
	g_772e8c = n;
	if (n == m) {
		return 0;
	}
	if (n == 0xf) {
		n = 0;
		g_772e8c = n;
	}
	return (char*) g_9ba3a0 + n * 108;
}
