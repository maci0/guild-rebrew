#include <string.h>

typedef struct {
	unsigned char kind;
	unsigned char pad1[0x23];
	int (__cdecl* rate)(float*, float*, int, unsigned char*, int, int*, int*);
	int (__cdecl* pick)(int, unsigned char*, int, int*, int*);
	char pad2c[0x64];
	unsigned int flags : 8;
} Plan495180;

extern char g_1008540[];
#include "GOLDTL.fcn_00495180_gconf.h"

/* ADDRESS: GOLDTL 0x00495180 */
int __cdecl fcn_00495180(int a0)
{
	int posA[6];
	int posB[6];
	int bestX[6];
	int bestYx[6];
	int bestY[6];
	int bestYy[6];
	float x;
	float y;
	float bx;
	float by;
	int kindX;
	int valX;
	int kindY;
	int valY;
	unsigned char* p;
	Plan495180* plan;
	int res2;
	int i;

	p = g_slot_table + a0 * 0x21c;
	bx = -1.0e30f;
	by = -1.0e30f;
	kindX = 0;
	kindY = 0;
	valX = 0;
	valY = 0;
	*(unsigned char*) bestX = 0;
	*(unsigned char*) bestY = 0;
	*(unsigned char*) bestYx = 0;
	*(unsigned char*) bestYy = 0;
	i = 0;
	plan = (Plan495180*) g_1008540;
	do {
		if (plan->kind == 0) {
			continue;
		}
		if (plan->kind == (unsigned char) p[0x132]) {
			continue;
		}
		if (!(p[0x218] & plan->flags)) {
			continue;
		}
		*(unsigned char*) posA = 0;
		*(int*) (posA + 1) = 0;
		*(int*) (posA + 2) = 0;
		*(unsigned char*) posB = 0;
		*(int*) (posB + 1) = 0;
		*(int*) (posB + 2) = 0;
		if (plan->rate == 0) {
			continue;
		}
		if ((res2 = plan->rate(&x, &y, i, p, 0, posA, posB)) == 0) {
			continue;
		}
		if (x >= bx || y >= by) {
			if (plan->pick == 0) {
				continue;
			}
			res2 = plan->pick(0, p, 0, posA, posB);
			if (res2 == 0) {
				continue;
			}
			if (x >= bx) {
				bx = x;
				memcpy(bestX, posA, 0x18);
				kindX = plan->kind;
				valX = res2;
				memcpy(bestYx, posB, 0x18);
			}
			if (y >= by) {
				by = y;
				memcpy(bestY, posA, 0x18);
				valY = res2;
				kindY = plan->kind;
				memcpy(bestYy, posB, 0x18);
			}
		}
	} while (++i, (int) ((char*) ++plan + 0x28) < 0x100af9c);
	if (bx != 0.0f && bx >= by) {
		p[0x131] = (char) kindX;
		memcpy(p + 0x134, bestX, 0x18);
		p[0x132] = (char) valX;
		memcpy(p + 0x14c, bestYx, 0x18);
	} else {
		p[0x131] = (char) kindY;
		memcpy(p + 0x134, bestY, 0x18);
		p[0x132] = (char) valY;
		memcpy(p + 0x14c, bestYy, 0x18);
	}
	return (unsigned char) p[0x132];
}
