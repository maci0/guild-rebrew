// FUNCTION: GOLDTL 0x00420210

typedef struct Chan Chan;
// SIZE 0x128
struct Chan {
	char name[0x100];
	int handle;
	unsigned char active;
	unsigned char b105;
	unsigned char b106;
	unsigned char b107;
	int f108;
	int f10c;
	int f110;
	int mode;
	unsigned int f118;
	int f11c;
	int f120;
	Chan* link;
};

extern int g_6b71a4;
extern Chan g_6b71b0[10];
extern int g_678168;
extern float g_678150;
extern float g_678154;
extern float g_678158;
extern unsigned int g_67815c;
extern int g_678160;
extern int g_6b7190;
extern volatile int g_6b7fac;

void __cdecl fcn_0042ad90(int h, int f);
void __cdecl fcn_0042ac40(int h);
void __cdecl fcn_0042b040(int h, int* out);
int __cdecl fcn_0042af10(int h);
int __cdecl fcn_0042ae10(int h, int v);
void __cdecl fcn_0041fc80(int vol);

void __cdecl fcn_00420210(void)
{
	int i;
	Chan* c;
	int n;
	unsigned int v;
	unsigned int t;

	if (g_6b71a4 != 0) {
		for (i = 0; i < 10; i++) {
			c = &g_6b71b0[i];
			if (c->active == 0) {
				continue;
			}
			if (c->handle == 0) {
				c->active = 0;
				if (c->link != 0) {
					if (c->link->handle != 0) {
						fcn_0042ad90(c->link->handle, 0);
						c->link->active = 1;
					}
					c->link->b105 = 0;
					c->link = 0;
				}
				continue;
			}
			fcn_0042b040(c->handle, &c->f10c);
			if (c->b106 != 0) {
				continue;
			}
			if (fcn_0042af10(c->handle) != 4 && fcn_0042af10(c->handle) != 0x10) {
				c->active = 0;
				c->mode = 0;
				fcn_0042ac40(c->handle);
				c->handle = 0;
				if (c->link != 0 && c->link->handle != 0) {
					fcn_0042ad90(c->link->handle, 0);
					c->link->active = 1;
					c->link->b105 = 0;
					c->link = 0;
				}
			}
			if (c->mode == 1) {
				if (c->f10c < c->f110) {
					c->f10c = c->f110;
				}
				if (c->f120 != 0) {
					n = c->f120 * g_678168 / c->f118;
				} else {
					n = g_678168;
				}
				if (n != 0 && n > c->f10c - c->f110) {
					c->f11c = (c->f10c - c->f110) * c->f118 / n;
					if (abs(c->f118 - c->f11c) < 2) {
						c->mode = 0;
						c->f11c = c->f118;
					}
				} else {
					c->mode = 0;
					c->f11c = c->f118;
				}
				fcn_0042ae10(c->handle, c->f11c);
			} else if (c->mode == 2) {
				if (c->f10c < c->f110) {
					c->f10c = c->f110;
				}
				n = c->f120 * g_678168 / c->f118;
				v = 0;
				if (n != 0 && n > c->f10c - c->f110) {
					v = (c->f110 - c->f10c + n) * c->f118 / n;
					c->f11c = v;
					if (v > 2) {
						fcn_0042ae10(c->handle, v);
					} else {
						c->mode = 0;
						c->f11c = 0;
						fcn_0042ae10(c->handle, 0);
						fcn_0042ac40(c->handle);
						c->handle = 0;
						c->active = 0;
						if (c->link != 0) {
							fcn_0042ad90(c->link->handle, 0);
							c->link->active = 1;
							c->link->b105 = 0;
							c->link = 0;
						}
					}
				} else {
					c->mode = v;
					c->f11c = v;
					fcn_0042ae10(c->handle, v);
					fcn_0042ac40(c->handle);
					c->handle = 0;
					c->active = 0;
					if (c->link != 0) {
						fcn_0042ad90(c->link->handle, 0);
						c->link->active = 1;
						c->link->b105 = 0;
						c->link = 0;
					}
				}
			}
		}
		if (g_678158 >= 0.0f) {
			t = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
			t -= g_6b7190;
			if (t < g_67815c) {
				g_678150 = (g_678158 - g_678154) / (float) g_67815c * (float) t + g_678154;
			} else {
				g_678150 = g_678158;
				g_678158 = -1.0f;
			}
			fcn_0041fc80(g_678160);
		}
	}
}
