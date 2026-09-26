// FUNCTION: GOLD 0x00473b20
// SIZE: 224

#include <string.h>

#include "gold_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_0046ea00(const char* text, int font);

void __cdecl fcn_00473b20(int slot, char* text)
{
	GuiEnt* s;
	char* par;
	int n;

	s = &g_00f8f080[slot];
	par = (char*) s->parent;
	if (par && s->buf) {
		if (s->u.edit.len) {
			memmove(s->buf, s->buf + s->u.edit.len, strlen(*(char**) (par + 0x2c)) - (s->buf - *(char**) (par + 0x2c)) + 1);
		}
		n = strlen(text);
		s->u.edit.len = n;
		memmove(s->buf + n, s->buf, strlen(*(char**) (par + 0x2c)) - (s->buf - *(char**) (par + 0x2c)) + 1);
		memcpy(s->buf, text, n);
		s->w = fcn_0046ea00(text, s->font);
		strcpy(s->u.edit.copy, text);
	}
}
