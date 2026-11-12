extern int g_6b7fb8; extern char g_77250c[];

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

void __cdecl fcn_0047c9c0(int, int, int, int, int, float);
void __cdecl fcn_00473150(Fade*);
void __cdecl fcn_00473190(int, int);

/* ADDRESS: GOLDTL 0x00473190 */
void __cdecl fcn_00473190(Fade* t)
{
	float elapsed;
	float v;

	elapsed = (float) ((*(volatile unsigned int*)&g_6b7fb8) - t->start);
	if ((*(volatile unsigned int*)&g_6b7fb8) - t->last > 3) {
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
		fcn_0047c9c0(t->x44, t->x48, t->x4c, t->x50, t->link->x50, v);
	}
	if ((t->flags & 4) && (t->flags & 8)) {
		fcn_00473150(t);
		return;
	}
	if (((t->flags & 1) && v == 1.0f) || ((t->flags & 2) && v == 0.0f)) {
		t->flags |= 4;
	}
	t->last = (*(volatile unsigned int*)&g_6b7fb8);
}

/* ADDRESS: GOLDTL 0x004732c0 */
void __cdecl fcn_004732c0(void)
{
	int a;
	int v;

	for (a = 0x1015ec0; a < 0x1015f40; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_00473190(v, *(int*) &g_77250c);
		}
	}
}
