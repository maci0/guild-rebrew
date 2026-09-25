// FUNCTION: GOLD 0x00473b20
// SIZE: 224

#include <string.h>

typedef struct Slot00473b20 {
	char pad0[0x14];
	short w;
	char pad16[0x30 - 0x16];
	char* link;
	char pad34[0x74 - 0x34];
	short font;
	char pad76[0x7c - 0x76];
	char* buf;
	char copy[0x40];
	int len;
	char padc4[0x2ec - 0xc4];
} Slot00473b20;
// SIZE 0x2ec

extern Slot00473b20* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_0046ea00(const char* text, int font);

void __cdecl fcn_00473b20(int slot, char* text)
{
	Slot00473b20* s;
	char* par;
	int n;

	s = &g_00f8f080[slot];
	par = s->link;
	if (par && s->buf) {
		if (s->len) {
			memmove(s->buf, s->buf + s->len, strlen(*(char**) (par + 0x2c)) - (s->buf - *(char**) (par + 0x2c)) + 1);
		}
		n = strlen(text);
		s->len = n;
		memmove(s->buf + n, s->buf, strlen(*(char**) (par + 0x2c)) - (s->buf - *(char**) (par + 0x2c)) + 1);
		memcpy(s->buf, text, n);
		s->w = fcn_0046ea00(text, s->font);
		strcpy(s->copy, text);
	}
}
