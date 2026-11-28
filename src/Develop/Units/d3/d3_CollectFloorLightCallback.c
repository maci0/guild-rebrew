#include <math.h>
extern const double g_6629c8;

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

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_TransformPoint(char* object, float* in, float* out);
int __cdecl d3_GetFloorHeight(int* a0, float* a1, unsigned int a2, unsigned int* a3,
                         unsigned int* a4, float* a5);

/* ADDRESS: GOLDTL 0x0043ed30 */
/* ADDRESS: GOLDDE 0x00437900 */
char __cdecl d3_CollectFloorLightCallback(char* node, LightIter* it)
{
	float pt[4];
	float val;
	float f90;
	float t;
	float scale;
	int centerX;
	int centerY;
	int r;
	int r2;
	int w;
	int offset;
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
	if (!(*(float*) (node + 0x94) > 0.0)) {
		return 1;
	}
	if (!(*(float*) (node + 0x90) > 0.0)) {
		return 1;
	}
	sc = (Scene*) it->obj;
	f90 = *(float*) (node + 0x90);
	d3_TransformPoint(node, (float*) (node + 0x4c), pt);
	if (!(unsigned char) d3_GetFloorHeight(&sc->width, pt, 0, (unsigned int*) &centerX, (unsigned int*) &centerY, &val)) {
		return 1;
	}
	t = f90 * f90 - (pt[1] - val) * (pt[1] - val);
	if (!(t > 0.0)) {
		return 1;
	}
	scale = sqrt(t) / (*(float*) 0x6b8308 + sc->f60);
	w = sc->width;
	offset = w * centerY + centerX;
	if (!(scale > g_6629c8)) {
		sc->data[offset] |= 0x80;
		return 1;
	}
	r = (int) scale;
	r2 = (int) (scale * scale + g_6628cc);
	y0 = centerY - r;
	if (y0 < 0) {
		y0 = 0;
	}
	y1 = centerY + r;
	if (y1 > w - 1) {
		y1 = w - 1;
	}
	if (y0 > y1) {
		return 1;
	}
	for (y = y0; y <= y1; y++) {
		x0 = centerX - r;
		if (x0 < 0) {
			x0 = 0;
		}
		x1 = centerX + r;
		if (x1 > sc->width - 1) {
			x1 = sc->width - 1;
		}
		for (x = x0; x <= x1; x++) {
			if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) < r2) {
				sc->data[y * sc->width + x] |= 0x80;
			}
		}
	}
	return 1;
}
