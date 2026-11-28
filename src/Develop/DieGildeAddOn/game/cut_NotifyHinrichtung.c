#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include <string.h>

extern char* g_14a9a44;
extern char str_empty[];

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_SendCmdMessage(char*, char*, char*, char*);


/* ADDRESS: GOLDTL 0x004e1960 */
/* ADDRESS: GOLDDE 0x004ce370 */
int __cdecl cut_NotifyHinrichtung(char* x)
{
	char buf[0x200];
	char* a;
	char* o;
	int i;

	if (x[0x7d] == 0) {
		a = gm_LookupEntityRecordById(*(int*) (x + 0x34));
		if (a == 0)
			return 0;
		if (a[2] == 6 || a[2] == 7) {
			io_FormatTextBuffer(buf, 0x11c5);
			strcat(buf, g_14a9a44);
			he_SendCmdMessage(a, x, buf, str_empty);
		}
		io_FormatTextBuffer(buf, 0x11c8, *(unsigned short*) a);
		for (i = 1; i < (unsigned char) x[0x30]; i++) {
			o = gm_LookupEntityRecordById(*(int*) (x + 0x34 + i * 4));
			if (o != 0 && (o[2] == 6 || o[2] == 7))
				he_SendCmdMessage(o, x, buf, str_empty);
		}
		return 1;
	}
	a = gm_LookupEntityRecordById(*(int*) (x + 0x34));
	if (a == 0)
		return 0;
	io_FormatTextBuffer(buf, 0x11c8, *(unsigned short*) a);
	for (i = 1; i < (unsigned char) x[0x30]; i++) {
		o = gm_LookupEntityRecordById(*(int*) (x + 0x34 + i * 4));
		if (o != 0 && (o[2] == 6 || o[2] == 7))
			he_SendCmdMessage(o, x, buf, str_empty);
	}
	return 1;
}
