#include "he_tables.h"

#include "Develop/Units/Error/error_message.h"

extern HE_AP_EVENT g_7dcae0[256];




#include <string.h>

HE_AP_EVENT* __cdecl he_RegisterApEvent(int a, char* name, int b, int c)
{
	int i;
	HE_AP_EVENT* r;

	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].value_08 == 0 && g_7dcae0[i].value_0c == 0 && g_7dcae0[i].name[0] == 0) {
			break;
		}
	}
	if (i >= 256) {
		ReportClientMessage("he_RegisterApEvent(): Too many ApEvents...");
		return 0;
	}
	r = &g_7dcae0[i];
	r->subject_id = a;
	r->value_08 = b;
	r->value_0c = c;
	r->lifetime = 2;
	strncpy(r->name, name, 0x3f);
	return r;
}
