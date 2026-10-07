// FUNCTION: GOLDTL 0x44a290

// SIZE 0xc
typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

// SIZE 0x18
typedef struct Vert {
	Vec3 pos;
	Vec3 n;
} Vert;

// SIZE 0x38
typedef struct Face {
	int pad[6];
	int idx[3];
	int pad2[2];
	Vec3 n;
} Face;

void __cdecl fcn_00451d70(Vert*, Vert*, Vert*, Vec3*);
void __cdecl fcn_004518a0(Vec3*);

void __cdecl fcn_0044a290(char* m)
{
	float n[4];
	Face* f;
	Vert* v;
	int i;
	int j;

	f = *(Face**) (m + 0x48);
	for (i = 0; i < *(int*) (m + 0x4c); i++) {
		fcn_00451d70(&(*(Vert**) (m + 0x40))[f[i].idx[0]], &(*(Vert**) (m + 0x40))[f[i].idx[1]], &(*(Vert**) (m + 0x40))[f[i].idx[2]], &f[i].n);
	}
	v = *(Vert**) (m + 0x40);
	for (j = 0; j < *(int*) (m + 0x44); j++) {
		f = *(Face**) (m + 0x48);
		n[0] = 0.0f;
		n[1] = 0.0f;
		n[2] = 0.0f;
		for (i = 0; i < *(int*) (m + 0x4c); i++) {
			if (f[i].idx[0] == j || f[i].idx[1] == j || f[i].idx[2] == j) {
				n[0] += f[i].n.x;
				n[1] += f[i].n.y;
				n[2] += f[i].n.z;
			}
		}
		fcn_004518a0((Vec3*) n);
		v[j].n.x = n[0];
		v[j].n.y = n[1];
		v[j].n.z = n[2];
	}
}
