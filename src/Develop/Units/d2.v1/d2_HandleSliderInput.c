

typedef struct Glyph {
	short pad0;
	unsigned short w;
	short pad4;
	unsigned short h;
} Glyph;

typedef struct Owner {
	char pad0[0x198];
	int captured;
} Owner;

typedef struct Slot {
	char pad0[0xc];
	char* font;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x50 - 0x24];
	Owner* owner;
	char pad54[0x74 - 0x54];
	int dirty;
	char pad78[0x8c - 0x78];
	int pos;
	int min;
	int max;
	int flags;
	int page;
	int limit;
	char pada4[0x2ec - 0xa4];
	char up;
	char down;
	char pad2ee[0x2f4 - 0x2ee];
} Slot;
// SIZE 0x2f4

#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern int g_102d028;
extern int g_102d02c;
extern short io_ActiveCursorX;
extern short io_ActiveCursorY;

Glyph* __cdecl d2_GetBankEntry(char* font, int c);

/* ADDRESS: GOLDDE 0x00466d40 */
void __cdecl d2_HandleSliderInput(void)
{
	int flags;
	Glyph* g;
	int my;
	int range;
	int page;
	int min;
	int limit;
	int pos;
	D2_CONTROL_TL* s;
	char* font;
	Glyph* bar;
	int mx;
	int max;

	if (d2_CurrentElementId == -1) {
		return;
	}
	s = &((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId];
	if (s->kind != 0x45 || (s->payload.fields.value_098 & 0x40) != 0) {
		return;
	}
	if ((*(Owner**)&s->value_050) != 0 && (*(Owner**)&s->value_050)->captured != 0) {
		mx = g_102d028;
		my = g_102d02c;
	} else {
		mx = io_ActiveCursorX;
		my = io_ActiveCursorY;
	}
	if (g_14ce8d0 != 0) {
		font = (*(char**)&s->data);
		g = d2_GetBankEntry(font, 0);
		d2_GetBankEntry(font, 1);
		d2_GetBankEntry(font, 3);
		bar = d2_GetBankEntry(font, 6);
		s = &((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId];
		flags = s->payload.fields.value_098;
		max = s->payload.fields.value_094;
		min = s->payload.fields.value_090;
		page = s->payload.fields.value_09c;
		limit = s->payload.fields.value_0a0;
		range = max - min;
		if ((flags & 0x48) == 0 && mx > s->x + bar->w && mx < s->width - bar->w + s->x) {
			if ((flags & 2) != 0) {
				pos = (int)((mx - g->w - s->x) * ((float) range / page) + min + 0.5f);
			} else if ((flags & 1) != 0) {
				pos = (int)((s->height - g->h + s->y - my) * ((float) range / page) + min + 0.5f);
			}
			if (pos < min) {
				pos = min;
			} else if ((flags & 0x10) != 0 && pos > limit) {
				pos = limit;
			} else if (pos > max) {
				pos = max;
			}
			s->value_074 = 1;
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId].payload.fields.value_08c) = pos;
		}
	}
	if (g_14ce8d8 != 0 || (g_14ce8d4 != 0 && (*(int*)&((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId].payload.fields.value_094) >= 100)) {
		s = &((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId];
		pos = s->payload.fields.value_08c;
		max = s->payload.fields.value_094;
		min = s->payload.fields.value_090;
		if ((*(char*)&s->value_2ec) != 0) {
			pos--;
		} else if ((*(char*)&s->value_2ed) != 0) {
			pos++;
		}
		if (pos < min) {
			pos = min;
		} else if ((flags & 0x10) != 0 && pos > limit) {
			pos = limit;
		} else if (pos > max) {
			pos = max;
		}
		s->value_074 = 1;
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId].payload.fields.value_08c) = pos;
	}
}
