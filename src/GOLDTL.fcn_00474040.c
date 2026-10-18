

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

extern int g_67d370;
extern char* g_1015ea0;
extern int g_102d028;
extern int g_102d02c;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern int g_14ce8d0;
extern int g_14ce8d4;
extern int g_14ce8d8;

Glyph* __cdecl fcn_0047b620(char* font, int c);

void __cdecl fcn_00474040(void)
{
	int flags;
	Glyph* g;
	int my;
	int range;
	int page;
	int min;
	int limit;
	int pos;
	Slot* s;
	char* font;
	Glyph* bar;
	int mx;
	int max;

	if (g_67d370 == -1) {
		return;
	}
	s = &((Slot*)g_1015ea0)[g_67d370];
	if (s->type != 0x45 || (s->flags & 0x40) != 0) {
		return;
	}
	if (s->owner != 0 && s->owner->captured != 0) {
		mx = g_102d028;
		my = g_102d02c;
	} else {
		mx = g_14ce8c0;
		my = g_14ce8c2;
	}
	if (g_14ce8d0 != 0) {
		font = s->font;
		g = fcn_0047b620(font, 0);
		fcn_0047b620(font, 1);
		fcn_0047b620(font, 3);
		bar = fcn_0047b620(font, 6);
		s = &((Slot*)g_1015ea0)[g_67d370];
		flags = s->flags;
		max = s->max;
		min = s->min;
		page = s->page;
		limit = s->limit;
		range = max - min;
		if ((flags & 0x48) == 0 && mx > s->x + bar->w && mx < s->w - bar->w + s->x) {
			if ((flags & 2) != 0) {
				pos = (int)((mx - g->w - s->x) * ((float) range / page) + min + 0.5f);
			} else if ((flags & 1) != 0) {
				pos = (int)((s->h - g->h + s->y - my) * ((float) range / page) + min + 0.5f);
			}
			if (pos < min) {
				pos = min;
			} else if ((flags & 0x10) != 0 && pos > limit) {
				pos = limit;
			} else if (pos > max) {
				pos = max;
			}
			s->dirty = 1;
			((Slot*)g_1015ea0)[g_67d370].pos = pos;
		}
	}
	if (g_14ce8d8 != 0 || (g_14ce8d4 != 0 && ((Slot*)g_1015ea0)[g_67d370].max >= 100)) {
		s = &((Slot*)g_1015ea0)[g_67d370];
		pos = s->pos;
		max = s->max;
		min = s->min;
		if (s->up != 0) {
			pos--;
		} else if (s->down != 0) {
			pos++;
		}
		if (pos < min) {
			pos = min;
		} else if ((flags & 0x10) != 0 && pos > limit) {
			pos = limit;
		} else if (pos > max) {
			pos = max;
		}
		s->dirty = 1;
		((Slot*)g_1015ea0)[g_67d370].pos = pos;
	}
}
