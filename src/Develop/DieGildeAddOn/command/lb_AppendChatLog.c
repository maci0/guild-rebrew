


#include <string.h>

#include "Develop/Units/d2.v1/text_log_record.h"

extern TEXT_LOG_RECORD g_9ba3a0[15];
extern int g_9ba9f4;
extern int g_772e88;

char* __cdecl d3_GetSceneEntry(int);
int __cdecl fcn_0064d41a(char*, char*, ...);

void __cdecl lb_AppendChatLog(int a, int b, char* s)
{
	char* r;

	r = d3_GetSceneEntry(a);
	if (r != 0)
		fcn_0064d41a(g_9ba3a0[g_9ba9f4].text, "%s %s", r + 0x12, r + 0x22);
	else
		strcpy(g_9ba3a0[g_9ba9f4].text, "???????");
	g_9ba3a0[g_9ba9f4].a = a;
	g_9ba3a0[g_9ba9f4].b = b;
	strcpy(g_9ba3a0[g_9ba9f4].name, s);
	g_9ba9f4++;
	if (g_9ba9f4 >= 15)
		g_9ba9f4 = 0;
	if (g_772e88 < 15)
		g_772e88++;
}
