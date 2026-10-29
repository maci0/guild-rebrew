extern int g_1043030[];
extern int g_1043040[];
extern int g_10425f0[];
extern int g_10529cc;
extern int g_1042580;
extern int g_1040620;
extern int g_1040624;

typedef struct Edge456080 {
	int nxt;
	int prv;
} Edge456080;

extern Edge456080 g_662c7c[];

extern void __cdecl fcn_00456400(int i, int j);
extern void __cdecl fcn_00455c90(int i, int j);
extern void __cdecl fcn_00455d30(int count, int size, unsigned char flags, int arg3, int y);

/* ADDRESS: GOLDTL 0x00456080 */
void __cdecl fcn_00456080(float* v, unsigned char* colors, int base, int size,
	unsigned char flags, int grid, int r)
{
	int top = -1;
	int i = 0;
	int ymin = size << 16;
	int upper1;
	int lower1;
	int upper2;
	int lower2;
	int t1;
	int t2;
	int flip;
	int y1;
	int y2;
	int ymid;
	int count;
	float det;
	float dy1;
	float dy2;

	det = v[3] * v[4] - v[2] * v[5] + v[2] * v[1] - v[0] * v[3] + v[0] * v[5] - v[4] * v[1];
	if (det <= 0.0) {
		do {
			g_1043030[i] = (int) (v[2 * i] * 65536.0f);
			g_1043040[i] = (int) (v[2 * i + 1] * 65536.0f);
			g_10425f0[i] = colors[i] << 16;
			if (g_1043040[i] <= ymin) {
				ymin = g_1043040[i];
				top = i;
			}
			i++;
		} while (i < 3);
	}
	else {
		do {
			g_1043030[i] = (int) (v[4 - 2 * i] * 65536.0f);
			g_1043040[i] = (int) (v[5 - 2 * i] * 65536.0f);
			g_10425f0[i] = colors[2 - i] << 16;
			if (g_1043040[i] <= ymin) {
				ymin = g_1043040[i];
				top = i;
			}
			i++;
		} while (i < 3);
	}
	if (top == -1)
		return;
	if (grid == 0)
		flags &= 2;
	if (base == 0)
		flags &= 5;
	if (flags == 0)
		return;
	t1 = g_662c7c[top].nxt;
	if (g_1043040[t1] == ymin) {
		lower1 = g_662c7c[top].prv;
		upper2 = t1;
		lower2 = g_662c7c[t1].nxt;
		upper1 = top;
	}
	else {
		t2 = g_662c7c[top].prv;
		if (g_1043040[t2] == ymin) {
			lower1 = g_662c7c[t2].prv;
			upper1 = t2;
			upper2 = top;
			lower2 = t1;
		}
		else {
			upper1 = top;
			lower1 = t2;
			upper2 = top;
			lower2 = t1;
		}
	}
	dy1 = v[5] - v[3];
	dy2 = v[1] - v[3];
	det = (v[0] - v[2]) * dy1 - (v[4] - v[2]) * dy2;
	if (det == 0.0f) {
		g_10529cc = 0;
	}
	else {
		g_10529cc = (int) (((colors[0] - colors[1]) * dy1 - (colors[2] - colors[1]) * dy2) *
			(65536.0f / det));
	}
	if (g_1043040[lower1] <= g_1043040[upper1])
		return;
	fcn_00456400(upper1, lower1);
	y2 = g_1043040[lower2];
	if (y2 <= g_1043040[upper2])
		return;
	fcn_00455c90(upper2, lower2);
	ymin = (ymin + 0xffff) >> 16;
	g_1042580 = ymin * size + base;
	g_1040624 = grid;
	g_1040620 = r;
	y1 = g_1043040[lower1];
	flip = y1 < y2;
	count = (((flip ? y1 : y2) + 0xffff) >> 16) - ymin;
	fcn_00455d30(count, size, flags, 1, ymin);
	if (g_1043040[lower1] == g_1043040[lower2])
		return;
	ymid = ymin + count;
	if (flip) {
		fcn_00456400(lower1, lower2);
		count = ((y2 + 0xffff) >> 16) - ((y1 + 0xffff) >> 16);
	}
	else {
		fcn_00455c90(lower2, lower1);
		count = ((y1 + 0xffff) >> 16) - ((y2 + 0xffff) >> 16);
	}
	fcn_00455d30(count, size, flags, 0, ymid);
}
