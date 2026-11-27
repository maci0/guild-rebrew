int __cdecl CompareVector3WithinTolerance(float*, float*, float);
void* __cdecl d2_GetResourceData(int);
int __cdecl fcn_0047cb30(int, int, int, int);
int __cdecl d2_DrawShapeFrame(int, int, int, void*, int);

#define CAM(off)	((float*) (*(char**) 0xfc2dec + (off)))
#define SAME(off)	CompareVector3WithinTolerance(CAM(off), (float*) 0x5ebba4, 0.2f)
#define HALF_W		(*(short*) 0xfb9070 / 2)
#define HALF_H		(*(short*) 0xfb9072 / 2)

/* ADDRESS: GOLD 0x004cf370 */
void __cdecl fcn_004cf370(void)
{
	void* rec;
	int a;
	int b;
	int c;
	int d;
	int mode;

	a = 0;
	b = 0;
	c = 0;
	d = 0;
	rec = d2_GetResourceData(0x52c);
	mode = *(int*) 0x6f22cc;
	if (mode == -1) {
		a = 1;
		if (!SAME(0xfc)) {
			a = 2;
		}
	} else if (mode == 1) {
		b = 1;
		if (!SAME(0xe4)) {
			b = 2;
		}
	} else if (mode == 0) {
		if (!SAME(0xe4)) {
			b = 1;
		}
		if (!SAME(0xfc)) {
			a = 1;
		}
	}
	mode = *(int*) 0x6f22d0;
	if (mode == -1) {
		c = 1;
		if (!SAME(0xb4)) {
			c = 2;
		}
	} else if (mode == 1) {
		d = 1;
		if (!SAME(0xcc)) {
			d = 2;
		}
	} else if (mode == 0) {
		if (!SAME(0xb4)) {
			c = 1;
		}
		if (!SAME(0xcc)) {
			d = 1;
		}
	}
	fcn_0047cb30(0, 0, ((int*) *(int*) 0x6ed924)[1], ((int*) *(int*) 0x6ed924)[2]);
	if (c == 2) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5edc50 - *(float*) 0x5eb81c),
			     *(int*) 0x6ed924, rec, 0);
	} else if (c == 1) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5edc50 - *(float*) 0x5eb81c),
			     *(int*) 0x6ed924, rec, c);
	}
	if (b == 2) {
		d2_DrawShapeFrame(8, HALF_W + 0x14, *(int*) 0x6ed924, rec, b);
	} else if (b == 1) {
		d2_DrawShapeFrame(8, HALF_W + 0x14, *(int*) 0x6ed924, rec, 3);
	}
	if (a == 2) {
		d2_DrawShapeFrame(*(short*) 0xfb9072 - 0x28, HALF_W + 0x14, *(int*) 0x6ed924, rec, 4);
	} else if (a == 1) {
		d2_DrawShapeFrame(*(short*) 0xfb9072 - 0x28, HALF_W + 0x14, *(int*) 0x6ed924, rec, 5);
	}
	if (d == 2) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5eb7fc), *(int*) 0x6ed924, rec, 6);
	} else if (d == 1) {
		d2_DrawShapeFrame(HALF_H - 0x14, (int) (*(float*) 0x5fe708 * *(float*) 0x5eb7fc), *(int*) 0x6ed924, rec, 7);
	}
}
