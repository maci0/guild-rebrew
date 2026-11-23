typedef struct {
	float px, py, pz;
	char p0c[4];
	float vx, vy, vz;
	char p1c[0x30 - 0x1c];
	int t;
	char p34[4];
	float nx, ny, nz;
	char p44[4];
	float w;
	char p4c[3];
	unsigned char c4f;
	char p50;
	unsigned char fl;
	char p52[2];
} Rec;

extern int __cdecl _ftol(void);
extern int __cdecl fcn_0064d3f8(void);
extern float g_6628cc;
extern float g_6628d8;
extern float g_662948;
extern float g_662a18;
extern float g_662a2c;
extern float g_662a40;


/* Update the animated particle records of an emitter.  Each active record
 * integrates its position, ages the elapsed timer and re-seeds itself when it
 * expires; the live records are counted and, once the emitter is enabled, the
 * free records up to half its capacity are seeded and the dirty flag cleared. */
/* ADDRESS: GOLDTL 0x00417870 */
char __cdecl fcn_00417870(char* a0, int timeNow)
{
	Rec* rec;
	char* base;
	int count;
	int half;
	int i;
	unsigned int t;
	float v;
	float f;

	half = (int) (*(unsigned int*) (a0 + 0x20) >> 1);
	count = 0;
	base = *(char**) (a0 + 0x28);
	for (i = 0; i < *(int*) (a0 + 0xd8); i++) {
		rec = (Rec*) base + i;
		if (rec->fl & 1) {
			t = (unsigned int) (timeNow - ((Rec*) *(char**) (a0 + 0x28) + i)->t);
			v = (float) t * 0.001f;
			((Rec*) *(char**) (a0 + 0x28) + i)->nx = ((Rec*) *(char**) (a0 + 0x28) + i)->vx + ((Rec*) *(char**) (a0 + 0x28) + i)->px;
			((Rec*) *(char**) (a0 + 0x28) + i)->ny = ((Rec*) *(char**) (a0 + 0x28) + i)->vy + ((Rec*) *(char**) (a0 + 0x28) + i)->py;
			((Rec*) *(char**) (a0 + 0x28) + i)->nz = ((Rec*) *(char**) (a0 + 0x28) + i)->vz + *(float*) (*(char**) (a0 + 0x28) + i * 0x54 + 8);
			((Rec*) *(char**) (a0 + 0x28) + i)->w = g_662948 * v + ((Rec*) *(char**) (a0 + 0x28) + i)->w;
			((Rec*) *(char**) (a0 + 0x28) + i)->py = ((Rec*) *(char**) (a0 + 0x28) + i)->py - v;
			if (((Rec*) *(char**) (a0 + 0x28) + i)->ny < -10.0)
				rec->fl &= 0xfe;
			rec->vx = rec->nx;
			rec->vy = rec->ny;
			rec->vz = rec->nz;
			f = rec->ny * 1.5f + 50.0f;
			if (0.0f > f)
				f = 0.0f;
			rec->c4f = (unsigned char) (int) f;
		}
		if (!(rec->fl & 1))
			count++;
	}
	if (!(*(int*) (a0 + 0x20) & 1) && count >= *(int*) (a0 + 0xd8))
		return 0;
	if ((*(int*) (a0 + 0x20) & 1) != 0 && count > half) {
		rec = (Rec*) *(char**) (a0 + 0x28);
		for (i = 0; i < *(int*) (a0 + 0xd8); i++, rec++) {
			if (i >= half)
				break;
			if (!(rec->fl & 1)) {
				rec->fl |= 1;
				rec->nx = (float) fcn_0064d3f8() * 3.0518509447574615e-05f - g_6628cc;
				rec->ny = (*(float*) (a0 + 4) + 1.0f) *
				                            (float) fcn_0064d3f8() * 3.0518509447574615e-05f +
				                        *(float*) (a0 + 0xc);
				rec->nz = (float) fcn_0064d3f8() * 3.0518509447574615e-05f - g_6628cc;
				rec->px = (float) fcn_0064d3f8() * *(float*) (a0 + 4) * 6.10370189e-05f -
				                *(float*) (a0 + 4);
				v = (rec->ny - 55.0f) * *(float*) (a0 + 8);
				rec->py = v - ((float) fcn_0064d3f8() * 3.05185108e-06f +
				                           0.2f);
				rec->pz = ((rec->ny - 55.0f) +
				                          rec->py) *
				                         *(float*) a0 +
				                     (float) fcn_0064d3f8() * g_662a40 +
				                     0.4f;
				rec->t = timeNow;
				rec->w = *(float*) (a0 + 0xe4);
				rec->vx = rec->nx;
				rec->vy = rec->ny;
				rec->vz = rec->nz;
				f = rec->ny * 1.5f + 50.0f;
				if (0.0f > f)
					f = 0.0f;
				rec->c4f = (unsigned char) (int) f;
			}
		}
		*(int*) (a0 + 0x20) &= ~1;
	}
	return 1;
}
