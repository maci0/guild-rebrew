


extern int g_11bb000[];
extern int g_6b7f98;
extern char g_67998c[];
extern char g_679964[];
int __cdecl fcn_0064f170(const char* a, const char* b, unsigned int n);
#include "Develop/Units/Error/error_message.h"

void __cdecl txt_ParseRandomText(char* s)
{
	int v;

	if (fcn_0064f170(s, g_67998c, 2) == 0) {
		v = s[2] - '1';
		if (v >= 0 && v <= 9) {
			g_11bb000[g_6b7f98] = v + 9;
			return;
		}
		ReportClientMessage(g_679964);
		g_11bb000[g_6b7f98] = *(volatile int*) &s;
		return;
	}
	g_11bb000[g_6b7f98] = *(volatile int*) &s;
}
