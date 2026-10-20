#include <math.h>

extern char* g_6b8014;

extern float g_662a34;
extern float g_1042150;
extern float g_1042154;
extern float g_1042158;
extern float g_1042160;
extern float g_1042164;
extern float g_1042168;
extern float g_1042180;
extern float g_1042184;
extern float g_1042188;
extern float g_1042190;
extern float g_1042194;
extern float g_1042198;
extern int g_1052bac;
extern int g_1042a08;
extern int g_10432a8;
extern int g_1042a04;

extern unsigned int __cdecl fcn_00440260(int, int, int, int);
extern unsigned char __cdecl fcn_00437ee0(void*, char*, char*);

typedef int (__cdecl* Fn_441050)(void*);

/* ADDRESS: GOLDTL 0x00441050 */

/* Recomputes the two cached shadow boxes of an entity from the eight
 * surrounding placements and sums the visibility/occupancy callbacks of the
 * 8x8 cell grid. Returns the number of lit cells. */
int __cdecl fcn_00441050(char* e)
{
	float* m;
	float dx;
	float dy;
	float dz;
	float sx;
	float sy;
	float sz;
	float* f;
	float* p;
	char* w;
	char* o;
	void** v10;
	Fn_441050 fn;
	int count;
	int i;
	int j;
	int k;
	unsigned char res;

	m = (float*) g_6b8014;
	dx = *(float*) (e + 0x50) - m[0x13];
	dy = *(float*) (e + 0x54) - m[0x14];
	dz = *(float*) (e + 0x58) - m[0x15];
	count = 0;
	g_1042180 = dy * m[0x67] + dz * m[0x6b] + dx * m[0x63];
	g_1042184 = dx * m[0x64] + dy * m[0x68] + dz * m[0x6c];
	g_1042188 = dy * m[0x69] + dz * m[0x6d] + dx * m[0x65];
	g_1042190 = *(float*) (e + 0x64) * m[0x67] + *(float*) (e + 0x68) * m[0x6b]
		+ m[0x63] * *(float*) (e + 0x60);
	g_1042194 = m[0x64] * *(float*) (e + 0x60) + m[0x68] * *(float*) (e + 0x64)
		+ m[0x6c] * *(float*) (e + 0x68);
	g_1042198 = *(float*) (e + 0x64) * m[0x69] + *(float*) (e + 0x68) * m[0x6d]
		+ m[0x65] * *(float*) (e + 0x60);
	g_1042150 = *(float*) (e + 0x74) * m[0x67] + *(float*) (e + 0x78) * m[0x6b]
		+ m[0x63] * *(float*) (e + 0x70);
	g_1042154 = m[0x64] * *(float*) (e + 0x70) + m[0x68] * *(float*) (e + 0x74)
		+ m[0x6c] * *(float*) (e + 0x78);
	g_1042158 = *(float*) (e + 0x74) * m[0x69] + *(float*) (e + 0x78) * m[0x6d]
		+ m[0x65] * *(float*) (e + 0x70);
	g_1042160 = *(float*) (e + 0x84) * m[0x67] + *(float*) (e + 0x88) * m[0x6b]
		+ m[0x63] * *(float*) (e + 0x80);
	g_1042164 = m[0x64] * *(float*) (e + 0x80) + m[0x68] * *(float*) (e + 0x84)
		+ m[0x6c] * *(float*) (e + 0x88);
	g_1042168 = *(float*) (e + 0x84) * m[0x69] + *(float*) (e + 0x88) * m[0x6d]
		+ m[0x65] * *(float*) (e + 0x80);
	w = e + 0x280;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			p = (float*) fcn_00440260((int) e, (int) (w - 0x1e0), j, i);
			res = fcn_00437ee0(p, w, w + 4);
			*(unsigned char*) (w + 0x11) = res;
			if ((res & 0x40) != 0) {
				*(char*) (w + 0xe) = 0;
			} else {
				*(char*) (w + 0xe) = 1;
				f = p + 0x16;
				sx = p[0];
				sy = p[1];
				sz = p[2];
				k = 7;
				do {
					sx = sx + f[-2];
					sy = sy + f[-1];
					sz = sz + *f;
					f = f + 0x14;
					k -= 1;
				} while (k != 0);
				sx = sx * g_662a34;
				count += 1;
				sy = sy * g_662a34;
				sz = sz * g_662a34;
				*(float*) (w - 0x20) = sx;
				*(float*) (w - 0x1c) = sy;
				*(float*) (w - 0x18) = sz;
				*(float*) (w - 4) = (float) sqrt(sx * sx + sy * sy + sz * sz);
			}
			v10 = (void**) (w - 0x1cc);
			k = 8;
			do {
				o = v10[1];
				if (o != 0) {
					if (*(char*) (w + 0xe) != 0) {
						g_1052bac += (*(Fn_441050*) ((char*) *(void**) o + 0x14))(o);
						g_1042a08 += (*(Fn_441050*) ((char*) *(void**) o + 0x10))(o);
					}
					g_10432a8 += (*(Fn_441050*) ((char*) *(void**) o + 0x10))(o);
					g_1042a04 += (*(Fn_441050*) ((char*) *(void**) o + 0x14))(o);
				}
				o = v10[0];
				if (o != 0) {
					if (*(char*) (w + 0xe) != 0) {
						g_1052bac += (*(Fn_441050*) ((char*) *(void**) o + 0x14))(o);
						g_1042a08 += (*(Fn_441050*) ((char*) *(void**) o + 0x10))(o);
					}
					g_10432a8 += (*(Fn_441050*) ((char*) *(void**) o + 0x10))(o);
					g_1042a04 += (*(Fn_441050*) ((char*) *(void**) o + 0x14))(o);
				}
				v10 = (void**) ((char*) v10 + 0x34);
				k -= 1;
			} while (k != 0);
			w += 0x1f4;
		}
	}
	return count;
}
