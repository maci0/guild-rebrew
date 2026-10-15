#include "he_tables.h"

#include "Develop/Units/Error/error_message.h"

extern ApEvent g_7dcae0[256];




#include <string.h>

ApEvent* __cdecl fcn_00546ef0(int a, char* name, int b, int c)
{
	int i;
	ApEvent* r;

	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].f8 == 0 && g_7dcae0[i].fc == 0 && g_7dcae0[i].name[0] == 0) {
			break;
		}
	}
	if (i >= 256) {
		fcn_0041d9e0("he_RegisterApEvent(): Too many ApEvents...");
		return 0;
	}
	r = &g_7dcae0[i];
	r->f4 = a;
	r->f8 = b;
	r->fc = c;
	r->b0 = 2;
	strncpy(r->name, name, 0x3f);
	return r;
}
