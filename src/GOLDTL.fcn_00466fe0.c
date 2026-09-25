#include <string.h>

typedef struct
{
	char pad000[0x10];
	int w;
	char pad014[0x134 - 0x14];
	int ent;
	int font;
	char pad13c[0x154 - 0x13c];
	char* cur;
	int len;
	char pad15c[0x160 - 0x15c];
} fcn_00466fe0_Fld;
// SIZE 0x160

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466fe0_Ent;
// SIZE 0x2f4

extern fcn_00466fe0_Fld g_102d140[];
extern fcn_00466fe0_Ent* g_1015ea0;
extern char* g_14a5320[];

int __cdecl fcn_0046b520(char* s, int font);

// FUNCTION: GOLDTL 0x466fe0
// SIZE: 280
void __cdecl fcn_00466fe0(int fld, int str)
{
	fcn_00466fe0_Fld* f;
	char* e;
	char* cur;
	int len;

	f = &g_102d140[fld];
	e = (char*) g_1015ea0[f->ent].i[0x40 / 4];
	if (e == 0) {
		return;
	}
	cur = f->cur;
	if (cur == 0) {
		return;
	}
	if (f->len != 0) {
		memmove(cur, cur + f->len, strlen(*(char**) (e + 0x3c)) - (cur - *(char**) (e + 0x3c)) + 1);
	}
	len = strlen(g_14a5320[str]);
	f->len = len;
	memmove(f->cur + len, f->cur, strlen(*(char**) (e + 0x3c)) - (f->cur - *(char**) (e + 0x3c)) + 1);
	memcpy(f->cur, g_14a5320[str], f->len);
	f->w = fcn_0046b520(g_14a5320[str], f->font);
	g_1015ea0[f->ent].i[0x18 / 4] = f->w;
}
