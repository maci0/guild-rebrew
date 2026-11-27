#include <string.h>
#include "gold_gui.h"

typedef struct Slot {
	char pad0[0x18];
	int w;
	char pad1c[0x40 - 0x1c];
	char* link;
	char pad44[0x84 - 0x44];
	int font;
	int pad88;
	char* buf;
	char copy[0x40];
	int len;
	char padd4[0x2f4 - 0xd4];
} Slot;
// SIZE 0x2f4

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern char* g_1015ea0;

int __cdecl d2_CalcTextWidth(const char* text, int font);
int __cdecl d2_MeasureTextWidth(const char* text, int font);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00473b20 */
void __cdecl d2_SetEditControlText(int slot, char* text)
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
		s->w = d2_CalcTextWidth(text, s->font);
		strcpy(s->u.edit.copy, text);
	}
}
#else
/* ADDRESS: GOLDTL 0x0046ff90 */
void __cdecl d2_SetEditControlText(int slot, char* text)
{
	Slot* s;
	char* par;
	int n;

	s = &((Slot*)g_1015ea0)[slot];
	par = s->link;
	if (par && s->buf) {
		if (s->len) {
			memmove(s->buf, s->buf + s->len, strlen(*(char**) (par + 0x3c)) - (s->buf - *(char**) (par + 0x3c)) + 1);
		}
		n = strlen(text);
		s->len = n;
		memmove(s->buf + n, s->buf, strlen(*(char**) (par + 0x3c)) - (s->buf - *(char**) (par + 0x3c)) + 1);
		memcpy(s->buf, text, n);
		s->w = d2_MeasureTextWidth(text, s->font);
		strcpy(s->copy, text);
	}
}
#endif
