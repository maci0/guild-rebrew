typedef struct Slot {
	int id;
	int used;
	int value;
	int pad0c;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x28 - 0x24];
	int left;
	int right;
	int top;
	int bottom;
	char pad38[0x40 - 0x38];
	int* link;
	int pad44;
	int hidden48;
	int hidden4c;
	char* owner;
	char pad54[0x58 - 0x54];
	int f58;
	int f5c;
	int pad60;
	int f64;
	char pad68[0x88 - 0x68];
	int result;
	char pad8c[0x1d0 - 0x8c];
	unsigned char flags1d0;
	char pad1d1[0x2f4 - 0x1d1];
} Slot;
// SIZE 0x2f4

typedef struct Win {
	char pad0[0x274];
	int active;
	char pad278[0x3cc - 0x278];
} Win;
// SIZE 0x3cc

extern Slot* g_1015ea0;
extern Win g_1015f40[];
extern Slot** g_772540;
extern int g_67d38c;
extern int g_67d388;
extern int g_67d374;
extern int g_67d370;

void __cdecl fcn_0046ac40(int x, int y);
int __cdecl fcn_0046acf0(int x, int y);

// FUNCTION: GOLDTL 0x46aee0
// SIZE: 605
int __cdecl fcn_0046aee0(int x, int y)
{
	int i;
	int hidden;
	Slot* s;
	Slot* w;
	int* lk;
	int left;
	int right;
	int top;
	int bottom;
	int r;

	fcn_0046ac40(x, y);
	g_67d38c = -1;
	g_67d374 = -1;
	for (i = 0x3ff; i >= 0; i--) {
		hidden = 0;
		s = g_772540[i];
		if (s) {
			if (s->owner) {
				hidden = *(int*) (s->owner + 0x198);
			}
			if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && !hidden
				&& y >= s->top && y <= s->bottom && !s->hidden4c && !s->hidden48 && g_1015ea0[s->id].type == 0x40 && g_1015f40[s->result].active) {
				g_67d38c = s->result;
				break;
			}
		}
	}
	for (i = 0x3ff; i >= 0; i--) {
		hidden = 0;
		s = g_772540[i];
		if (s) {
			if (s->owner) {
				hidden = *(int*) (s->owner + 0x198);
			}
			if (x >= s->x && x <= s->x + s->w && y >= s->y && y <= s->y + s->h && !hidden) {
				lk = s->link;
				if (lk) {
					w = &g_1015ea0[lk[0x27c / 4]];
					left = lk[1] > w->left ? lk[1] : w->left;
					right = lk[1] + lk[3] < w->right ? lk[1] + lk[3] : w->right;
					top = lk[2] > w->top ? lk[2] : w->top;
					bottom = lk[2] + lk[4] < w->bottom ? lk[2] + lk[4] : w->bottom;
				} else {
					left = s->left;
					right = s->right;
					top = s->top;
					bottom = s->bottom;
				}
				if (y >= top && y <= bottom && x >= left && x <= right && !s->hidden48 && (s->f5c || s->f58 || s->type == 0x41 || s->f64)) {
					if (!s->hidden4c) {
						g_67d374 = g_67d370 = s->id;
						if (s->link) {
							g_67d388 = *s->link;
						}
						if (s->type == 9) {
							return (s->flags1d0 & 0x10) ? 1 : 2;
						}
						return s->value;
					}
					if (g_67d374 == -1) {
						g_67d374 = s->id;
					}
					g_67d370 = -1;
				}
			}
		}
	}
	r = fcn_0046acf0(x, y);
	if (r == -1) {
		g_67d370 = -1;
		r = -1;
	}
	return r;
}
