extern char d2_OverlaySprites[];
extern volatile int tb_TimerTicks; extern char d2_ScreenSurface[];

typedef struct Fade Fade;

struct Fade {
	unsigned int flags;
	char p4[0x40];
	int x44;
	int x48;
	int x4c;
	int x50;
	int duration;
	unsigned int start;
	unsigned int last;
	Fade* link;
};

void __cdecl d2_DrawTexturedQuad(int, int, int, int, int, float);
void __cdecl d2_ReleaseOverlaySprite(Fade*);
void __cdecl d2_UpdateScreenFade(int, int);

/* ADDRESS: GOLDTL 0x00473190 */
/* ADDRESS: GOLDDE 0x004661a0 */
void __cdecl d2_UpdateScreenFade(Fade* t)
{
	float elapsed;
	float v;

	elapsed = (float) (((unsigned int)tb_TimerTicks) - t->start);
	if (((unsigned int)tb_TimerTicks) - t->last > 3) {
		elapsed = (float) (int) (t->last + 3) - (int) t->start;
	}
	if (t->flags & 1) {
		v = elapsed / t->duration;
	} else if (t->flags & 2) {
		v = 1.0f - elapsed / t->duration;
	}
	if (!(v > 0.0f)) {
		v = 0.0f;
	} else if (!(v < 1.0f)) {
		v = 1.0f;
	}
	if (t->link != 0) {
		d2_DrawTexturedQuad(t->x44, t->x48, t->x4c, t->x50, t->link->x50, v);
	}
	if ((t->flags & 4) && (t->flags & 8)) {
		d2_ReleaseOverlaySprite(t);
		return;
	}
	if (((t->flags & 1) && v == 1.0f) || ((t->flags & 2) && v == 0.0f)) {
		t->flags |= 4;
	}
	t->last = ((unsigned int)tb_TimerTicks);
}

/* ADDRESS: GOLDTL 0x004732c0 */
/* ADDRESS: GOLDDE 0x004662d0 */
void __cdecl d2_UpdateAllScreenFades(void)
{
	int a;
	int v;

	for (a = (int) &d2_OverlaySprites; a < ((int) &d2_OverlaySprites + 0x80); a += 4) {
		v = *(int*) a;
		if (v != 0) {
			d2_UpdateScreenFade(v, *(int*) &d2_ScreenSurface);
		}
	}
}
