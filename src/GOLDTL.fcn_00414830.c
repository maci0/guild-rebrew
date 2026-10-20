typedef struct {
	float x;
	float y;
	float z;
	char pad[0x44];
} P414830;

typedef P414830* (__cdecl* Corners414830)(char* obj, char* m, char* p);

typedef struct {
	char pad[0x1f0];
	Corners414830 get;
} Vtbl414830;

void __cdecl fcn_00438100(char* obj, char* cam, int force);
void __cdecl fcn_00414830(float* lo, float* hi, char* entity);

/* ADDRESS: GOLDTL 0x00414830 */
void __cdecl fcn_00414830(float* lo, float* hi, char* entity)
{
	P414830* p;
	Vtbl414830* vt;
	char* child;
	float v;
	int i;

	if (*(char**) (entity + 0x1cc) == 0) {
		return;
	}
	if ((*(unsigned char*) (entity + 0x216) & 0x20) == 0) {
		fcn_00438100(entity, *(char**) 0x6b8014, 0);
	}
	vt = (Vtbl414830*) (*(char**) (*(char**) (entity + 0x1cc) + 0x318));
	p = vt->get(entity, *(char**) (entity + 0x1cc), *(char**) (entity + 0x1ec) + 8);
	if (p != 0) {
		for (i = 0; i < 8; i++) {
			if (*lo < p[i].x) {
				v = *lo;
			}
			else {
				v = p[i].x;
			}
			*lo = v;
			if (lo[1] < p[i].y) {
				v = lo[1];
			}
			else {
				v = p[i].y;
			}
			lo[1] = v;
			if (lo[2] < p[i].z) {
				v = lo[2];
			}
			else {
				v = p[i].z;
			}
			lo[2] = v;
			if (*hi > p[i].x) {
				v = *hi;
			}
			else {
				v = p[i].x;
			}
			*hi = v;
			if (hi[1] > p[i].y) {
				v = hi[1];
			}
			else {
				v = p[i].y;
			}
			hi[1] = v;
			if (hi[2] > p[i].z) {
				v = hi[2];
			}
			else {
				v = p[i].z;
			}
			hi[2] = v;
		}
	}
	for (child = *(char**) (entity + 0x200); child != 0; child = *(char**) (child + 0x1f4)) {
		fcn_00414830(lo, hi, child);
	}
}
