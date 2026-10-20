#include <math.h>

typedef struct LightIter {
	char* obj;
	char* item;
} LightIter;

typedef struct Scene {
	int width;
	int pad4;
	char pad8[0x14];
	unsigned char* data;
	char pad20[0x40];
	float f60;
} Scene;

extern float g_6628cc;

void __cdecl fcn_00455350(char* object, float* in, float* out);
int __cdecl fcn_00441720(int* a0, float* a1, unsigned int a2, unsigned int* a3,
                         unsigned int* a4, float* a5);

/* ADDRESS: GOLDTL 0x0043ed30 */
char __cdecl fcn_0043ed30(char* node, LightIter* it)
{
	float pt[3];
	float val;
	float f90;
	float t;
	float scale;
	int v4;
	int v3;
	int r;
	int r2;
	int w;
	int y0;
	int y1;
	int x0;
	int x1;
	int x;
	int y;
	Scene* sc;

	if (*(int*) (node + 0x218) == 7) {
		if ((*(unsigned char*) (node + 0x215) & 4) != 0 && it->item == 0) {
			it->item = node;
		}
		return 1;
	}
	if (*(float*) (node + 0x94) <= 0.0) {
		return 1;
	}
	if (*(float*) (node + 0x90) <= 0.0) {
		return 1;
	}
	f90 = *(float*) (node + 0x90);
	fcn_00455350(node, (float*) (node + 0x4c), pt);
	sc = (Scene*) it->obj;
	if (!fcn_00441720(&sc->width, pt, 0, (unsigned int*) &v4, (unsigned int*) &v3, &val)) {
		return 1;
	}
	t = f90 * f90 - (pt[1] - val) * (pt[1] - val);
	if (!(t > 0.0)) {
		return 1;
	}
	scale = (*(float*) 0x6b8308 + sc->f60) / (float) sqrt(t);
	w = sc->width;
	if (!(scale > *(double*) 0x6629c8)) {
		sc->data[w * v3 + v4] |= 0x80;
		return 1;
	}
	r = (int) scale;
	r2 = (int) (scale * scale + g_6628cc);
	y0 = v3 - r;
	if (y0 < 0) {
		y0 = 0;
	}
	y1 = v3 + r;
	if (y1 > w - 1) {
		y1 = w - 1;
	}
	if (y0 > y1) {
		return 1;
	}
	for (y = y0; y <= y1; y++) {
		x0 = v4 - r;
		if (x0 < 0) {
			x0 = 0;
		}
		x1 = v4 + r;
		if (x1 > w - 1) {
			x1 = w - 1;
		}
		for (x = x0; x <= x1; x++) {
			if ((x - v4) * (x - v4) + (y - v3) * (y - v3) < r2) {
				sc->data[y * w + x] |= 0x80;
			}
		}
	}
	return 1;
}
