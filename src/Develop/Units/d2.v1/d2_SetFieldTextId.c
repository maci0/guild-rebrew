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
} D2_TEXTID_FIELD;
// SIZE 0x160

typedef struct
{
	int i[0x2f4 / 4];
} D2_TEXTID_FIELD_ENT;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern UI_FIELD g_102d140[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern char* txt_TextEntries[];

int __cdecl d2_MeasureTextWidth(char* s, int font);

/* ADDRESS: GOLDTL 0x00466fe0 */
void __cdecl d2_SetFieldTextId(int fld, int str)
{
	D2_TEXTID_FIELD* f;
	char* e;
	char* cur;
	int len;

	f = &((D2_TEXTID_FIELD*)g_102d140)[fld];
	e = (char*) (*(int*)&((D2_CONTROL_TL*)d2_Controls)[f->ent].parent);
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
	len = strlen(txt_TextEntries[str]);
	f->len = len;
	memmove(f->cur + len, f->cur, strlen(*(char**) (e + 0x3c)) - (f->cur - *(char**) (e + 0x3c)) + 1);
	memcpy(f->cur, txt_TextEntries[str], f->len);
	f->w = d2_MeasureTextWidth(txt_TextEntries[str], f->font);
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[f->ent].width) = f->w;
}
