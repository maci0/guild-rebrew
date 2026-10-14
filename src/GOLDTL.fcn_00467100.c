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
	int fixed;
} fcn_00467100_Fld;
// SIZE 0x160

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00467100_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Fld_102d140 g_102d140[];
extern char* g_1015ea0;

int __cdecl fcn_0046b520(char* s, int font);

/* ADDRESS: GOLDTL 0x00467100 */
void __cdecl fcn_00467100(int fld, char* text)
{
	fcn_00467100_Fld* f;
	char* e;
	char* cur;
	int len;

	f = &((fcn_00467100_Fld*)g_102d140)[fld];
	e = (char*) ((fcn_00467100_Ent*)g_1015ea0)[f->ent].i[0x40 / 4];
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
	len = strlen(text);
	f->len = len;
	memmove(f->cur + len, f->cur, strlen(*(char**) (e + 0x3c)) - (f->cur - *(char**) (e + 0x3c)) + 1);
	memcpy(f->cur, text, f->len);
	f->w = fcn_0046b520(text, f->font);
	if (f->fixed != 0) {
		((fcn_00467100_Ent*)g_1015ea0)[f->ent].i[0x18 / 4] = f->w;
	} else {
		((fcn_00467100_Ent*)g_1015ea0)[f->ent].i[0x18 / 4] = f->w >= 0 ? 0 : f->w;
	}
}
