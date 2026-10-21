#include <stdlib.h>
#include <string.h>

/* SIZE 0x28 */
typedef struct {
	float x;
	float y;
	float z;
	float size;
	float drift_a;
	float drift_b;
	char pad18[0x28 - 0x18];
} Drop;

/* SIZE 0x40 */
typedef struct {
	int count;
	int cap;
	int f08;
	int f0c;
	Drop* drops;
	int f14;
	int f18;
	int f1c;
	int f20;
	float size24;
	float size28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
} Rain;

/* ADDRESS: GOLDTL 0x0067756c */
extern char g_67756c[];
/* ADDRESS: GOLDTL 0x00662a18 */
extern float g_662a18;
/* ADDRESS: GOLDTL 0x006628bc */
extern float g_6628bc;
/* ADDRESS: GOLDTL 0x006628cc */
extern float g_6628cc;
/* ADDRESS: GOLDTL 0x00662a2c */
extern float g_662a2c;
/* ADDRESS: GOLDTL 0x00662a40 */
extern float g_662a40;
/* ADDRESS: GOLDTL 0x00662a44 */
extern float g_662a44;

void* __cdecl m_alloc(int size, char* tag);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLDTL 0x00415510 */
void __cdecl fcn_00415510(Rain* r, int n, ...)
{
	Drop* d;
	Drop* buf;
	int* p;
	int i;
	int k;

	i = 0;
	if (n <= 0) {
		return;
	}
	p = &n;
	do {
		int t;

		t = *++p;
		if (t >= 0) {
			if (t > 1) {
				if (t == 2) {
					r->f14 = r->f1c;
					r->f18 = r->f20;
					r->size24 = (float) *++p * g_662a2c;
					r->size28 = (float) *++p * g_662a2c;
					r->f38 = r->f2c;
					r->f3c = *++p + r->f2c;
				}
			}
			else {
				if (*++p >= r->cap) {
					k = *p + 100;
					buf = (Drop*) m_alloc(k * sizeof(Drop), g_67756c);
					if (buf == 0) {
						return;
					}
					memcpy(buf, r->drops, r->cap * sizeof(Drop));
					m_FreeTracked(r->drops);
					r->drops = buf;
					r->cap = k;
					d = (Drop*) ((char*) r->drops + r->count * sizeof(Drop));
					if (r->count < k) {
						k -= r->count;
						do {
							d->x = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
							d->y = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
							d->z = ((float) rand() * g_662a18 - g_6628cc) * 2.0f;
							d->size = (float) rand() * g_662a44 + g_6628bc;
							d->drift_a = (float) rand() * g_662a40 + g_6628bc;
							d->drift_b = (float) rand() * g_662a40 + g_6628bc;
							d++;
						} while (--k);
					}
				}
				if (t == 0) {
					r->count = *p;
				}
				else {
					r->f08 = r->count;
					r->f0c = *p;
					r->f30 = r->f2c;
					r->f34 = *++p + r->f2c;
				}
			}
		}
		i++;
	} while (i < n);
}
