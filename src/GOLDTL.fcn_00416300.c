#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* SIZE 0x28 */
typedef struct {
	float x;
	float y;
	float z;
	float speed;
	float drift_a;
	float drift_b;
	char pad18[0x28 - 0x18];
} Flake;

/* SIZE 0x70 */
typedef struct {
	int count;
	int cap;
	int f08;
	int f0c;
	int f10;
	int f14;
	int f18;
	int f1c;
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
	Flake* flakes;
	int f3c;
	int f40;
	int f44;
	int f48;
	float size4c;
	float size50;
	float limit54;
	int f58;
	int f5c;
	int f60;
	int f64;
	int f68;
	int f6c;
} Snow;

extern char g_677604[];

void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00416300 */
void __cdecl fcn_00416300(Snow* r, int n, ...)
{
	Flake* d;
	Flake* buf;
	int* p;
	int i;
	int k;
	int rnd;
	float v;

	i = 0;
	if (n <= 0) {
		return;
	}
	p = &n;
	do {
		int t;

		t = *++p;
		switch (t) {
		case 0:
		case 1:
			if (*++p >= r->cap) {
				k = *p + 100;
				buf = (Flake*) m_alloc(k * sizeof(Flake), (char*) 0x677604);
				if (buf == 0) {
					return;
				}
				memcpy(buf, r->flakes, r->cap * sizeof(Flake));
				m_FreeTracked(r->flakes);
				r->flakes = buf;
				r->cap = k;
				if (r->count < k) {
					d = (Flake*) ((char*) buf + r->count * sizeof(Flake));
					k -= r->count;
					do {
						rnd = rand();
						d->x = ((float) rnd * (*(float*)0x662a18) - (*(float*)0x6628cc)) * 2.0f;
						rnd = rand();
						d->y = ((float) rnd * (*(float*)0x662a18) - (*(float*)0x6628cc)) * 2.0f;
						rnd = rand();
						d->z = ((float) rnd * (*(float*)0x662a18) - (*(float*)0x6628cc)) * 2.0f;
						rnd = rand();
						d->speed = (float) rnd * (*(float*)0x662a88) + (*(float*)0x662a6c);
						rnd = rand();
						d->drift_a = (float) rnd * (*(float*)0x662a84) + (*(float*)0x662a74);
						rnd = rand();
						d->drift_b = (float) rnd * (*(float*)0x662a84) + (*(float*)0x662a74);
						d++;
					} while (--k);
				}
			}
			if (t == 0) {
				r->count = *p;
			} else {
				r->f08 = r->count;
				r->f0c = *p;
				r->f60 = r->f5c;
				r->f64 = *++p + r->f5c;
			}
			break;
		case 2:
			r->f40 = r->f48;
			r->f3c = r->f44;
			r->size4c = (float) *++p * (*(float*)0x662a2c);
			r->size50 = (float) *++p * (*(float*)0x662a2c);
			r->f68 = r->f5c;
			r->f6c = *++p + r->f5c;
			break;
		case 3:
			v = (float) *++p * (*(float*)0x662a8c);
			r->limit54 = MAX(r->limit54, v);
			break;
		}
		i++;
	} while (i < n);
}
