extern int g_6772bc;
extern int g_6772c0;
extern int g_6b5c80;
extern int g_6b5c84;
extern int g_774688;
extern int g_77468c;
extern int g_774734;
extern short g_14ce8c0;
extern short g_14ce8c2;
extern char* g_6b8014;
extern int g_7e3a40;
extern int g_7e3a44;
extern int g_7e3a48;
extern int g_7e3a50;
extern int g_7e3a54;
extern int g_7e3a58;
extern int g_6b5cbc;
extern int g_6b5cc0;
extern int g_6a256c;

int __cdecl fcn_00451840(float*, float*, float);
void __cdecl fcn_00433780(char*);
void __cdecl fcn_00412cf0(char*, int*, int*, int, int);

/* ADDRESS: GOLDTL 0x0052ae80 */
void __cdecl fcn_0052ae80(void)
{
	int minx;
	int maxx;
	int miny;
	int maxy;
	int idx;
	float ref[4];
	int next[4];
	int cur[4];

	minx = g_6b5c80 + 1;
	maxx = g_6772bc - 1;
	miny = g_6b5c84 + 1;
	maxy = g_6772c0 - 1;
	ref[0] = 0.0f;
	ref[1] = 0.0f;
	ref[2] = 0.0f;
	ref[3] = 0.0f;

	if (g_774734) {
		if ((short) g_14ce8c0 < minx) {
			return;
		}
		if ((short) g_14ce8c0 > maxx) {
			return;
		}
		if ((short) g_14ce8c2 < miny) {
			return;
		}
		if ((short) g_14ce8c2 > maxy) {
			return;
		}
		g_774734 = 0;
		return;
	}

	if ((short) g_14ce8c2 > miny && (short) g_14ce8c2 < maxy) {
		if ((short) g_14ce8c0 < minx) {
			if (g_774688 <= -1) {
				return;
			}
			g_774688--;
		} else if ((short) g_14ce8c0 > maxx) {
			if (g_774688 >= 1) {
				return;
			}
			g_774688++;
		} else {
			return;
		}
		idx = g_774688;
		g_77468c = 0;
		if (idx == -1) {
			if (fcn_00451840((float*) (g_6b8014 + 0xe4), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (g_6b8014 + 0xe4);
			cur[1] = *(int*) (g_6b8014 + 0xe8);
			cur[2] = *(int*) (g_6b8014 + 0xec);
			next[0] = *(int*) (g_6b8014 + 0xf0);
			next[1] = *(int*) (g_6b8014 + 0xf4);
			next[2] = *(int*) (g_6b8014 + 0xf8);
		} else if (idx == 0) {
			cur[0] = *(int*) (g_6b8014 + 0x5c);
			cur[1] = *(int*) (g_6b8014 + 0x60);
			cur[2] = *(int*) (g_6b8014 + 0x64);
			next[0] = *(int*) (g_6b8014 + 0x90);
			next[1] = *(int*) (g_6b8014 + 0x94);
			next[2] = *(int*) (g_6b8014 + 0x98);
		} else if (idx == 1) {
			if (fcn_00451840((float*) (g_6b8014 + 0xfc), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (g_6b8014 + 0xfc);
			cur[1] = *(int*) (g_6b8014 + 0x100);
			cur[2] = *(int*) (g_6b8014 + 0x104);
			next[0] = *(int*) (g_6b8014 + 0x108);
			next[1] = *(int*) (g_6b8014 + 0x10c);
			next[2] = *(int*) (g_6b8014 + 0x110);
		}
	} else {
		idx = g_77468c;
		if ((short) g_14ce8c2 < idx) {
			if (idx <= -1) {
				return;
			}
			idx--;
			g_77468c = idx;
		} else if ((short) g_14ce8c2 > maxy) {
			if (idx >= 1) {
				return;
			}
			idx++;
			g_77468c = idx;
		}
		g_774688 = 0;
		if (idx == -1) {
			if (fcn_00451840((float*) (g_6b8014 + 0xb4), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (g_6b8014 + 0xb4);
			cur[1] = *(int*) (g_6b8014 + 0xb8);
			cur[2] = *(int*) (g_6b8014 + 0xbc);
			next[0] = *(int*) (g_6b8014 + 0xc0);
			next[1] = *(int*) (g_6b8014 + 0xc4);
			next[2] = *(int*) (g_6b8014 + 0xc8);
		} else if (idx == 0) {
			cur[0] = *(int*) (g_6b8014 + 0x5c);
			cur[1] = *(int*) (g_6b8014 + 0x60);
			cur[2] = *(int*) (g_6b8014 + 0x64);
			next[0] = *(int*) (g_6b8014 + 0x90);
			next[1] = *(int*) (g_6b8014 + 0x94);
			next[2] = *(int*) (g_6b8014 + 0x98);
		} else if (idx == 1) {
			if (fcn_00451840((float*) (g_6b8014 + 0xcc), ref, 0.2f)) {
				return;
			}
			cur[0] = *(int*) (g_6b8014 + 0xcc);
			cur[1] = *(int*) (g_6b8014 + 0xd0);
			cur[2] = *(int*) (g_6b8014 + 0xd4);
			next[0] = *(int*) (g_6b8014 + 0xd8);
			next[1] = *(int*) (g_6b8014 + 0xdc);
			next[2] = *(int*) (g_6b8014 + 0xe0);
		}
	}

	g_7e3a40 = cur[0];
	g_7e3a44 = cur[1];
	g_7e3a48 = cur[2];
	g_7e3a50 = next[0];
	g_7e3a54 = next[1];
	g_7e3a58 = next[2];
	fcn_00433780(g_6b8014);
	g_6b5cbc = 0;
	g_6b5cc0 = 0;
	fcn_00412cf0(g_6b8014, cur, next, g_6a256c, 8);
	g_774734 = 1;
}
