#include <string.h>

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

extern Slot* g_1015ea0;

int __cdecl fcn_0046b520(const char* text, int font);

// FUNCTION: GOLDTL 0x46ff90
// SIZE: 233
void __cdecl fcn_0046ff90(int slot, char* text)
{
	Slot* s;
	char* par;
	int n;

	s = &g_1015ea0[slot];
	par = s->link;
	if (par && s->buf) {
		if (s->len) {
			memmove(s->buf, s->buf + s->len, strlen(*(char**) (par + 0x3c)) - (s->buf - *(char**) (par + 0x3c)) + 1);
		}
		n = strlen(text);
		s->len = n;
		memmove(s->buf + n, s->buf, strlen(*(char**) (par + 0x3c)) - (s->buf - *(char**) (par + 0x3c)) + 1);
		memcpy(s->buf, text, n);
		s->w = fcn_0046b520(text, s->font);
		strcpy(s->copy, text);
	}
}
