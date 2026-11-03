/* per-node lighting/shadow vertex build: 8-vertex loop, fcn_00455350/fcn_00455140/fcn_00457140, IDev vtable slot 0x1f0, world matrix at [0x6b8014]+0x18c. */

typedef struct V456ef0 {
	float x;
	float y;
	float z;
} V456ef0;

typedef struct Cam456ef0 {
	char pad0[0x4c];
	float x;
	float y;
	float z;
	char pad58[0x18c - 0x58];
	float m00;
	float m01;
	float m02;
	char pad98[0x19c - 0x198];
	float m10;
	float m11;
	float m12;
	char padd8[0x1ac - 0x1a8];
	float m20;
	float m21;
	float m22;
	char padb8[0x1bc - 0x1b8];
	float tx;
	float ty;
	float tz;
} Cam456ef0;

typedef struct Api456ef0 {
	char pad0[0x1f0];
	float* (__cdecl* query)(char*, char*, char*);
} Api456ef0;

void __cdecl fcn_00438100(char*, char*, int);
void __cdecl fcn_00455350(char*, char*, V456ef0*);
void __cdecl fcn_00455140(char*, float*, V456ef0*);
float __cdecl fcn_00457140(char*, char*, char*);
unsigned char __cdecl fcn_00437ee0(float*, int, int);
void __cdecl fcn_00457290(char*, char*, int, float);

/* ADDRESS: GOLDTL 0x00456ef0 */
void __cdecl fcn_00456ef0(char* o)
{
	V456ef0 v1;
	V456ef0 v2;
	V456ef0 r;
	float h;
	float dx;
	float dy;
	float dz;
	float t;
	Cam456ef0* cam;
	float* base;
	float* q;
	char* s;
	char* ctx;
	int i;

	*(unsigned char*) (o + 0x216) &= 0x7f;
	if (!(*(unsigned char*) (o + 0x215) & 1)) {
		return;
	}
	if (*(char**) (o + 0x1ec) == 0) {
		return;
	}
	if (!(*(unsigned char*) (o + 0x216) & 0x20)) {
		fcn_00438100(o, (*(unsigned char*) (o + 0x214) & 0x20) ? 0 : (char*) 0x6b8014, 0);
	}
	for (s = *(char**) 0x6b86e0; s != 0; s = *(char**) (s + 0x1f0)) {
		ctx = *(char**) (o + 0x1cc);
		if (ctx == 0) {
			break;
		}
		fcn_00455350(s, s + 0x4c, &v1);
		fcn_00455140(s, (float*) 0x662d40, &v2);
		h = fcn_00457140(o, ctx, s);
		base = ((Api456ef0*) *(char**) (ctx + 0x318))->query(
		    o, ctx, *(char**) (o + 0x1ec) + 8);
		q = base;
		i = 8;
		do {
			if (*(unsigned char*) (s + 0x215) & 4) {
				t = -(q[1] - h) / v2.y;
				r.x = v2.x * t + q[0];
				r.y = v2.y * t + q[1];
				r.z = v2.z * t + q[2];
			} else {
				dy = v1.y - q[1];
				dz = v1.z - q[2];
				t = -(v1.y - h) / dy;
				r.x = (v1.x - q[0]) * t + v1.x;
				r.y = dy * t + v1.y;
				r.z = dz * t + v1.z;
			}
			cam = (Cam456ef0*) *(int*) 0x6b8014;
			dx = r.x - cam->x;
			dy = r.y - cam->y;
			dz = r.z - cam->z;
			q[0] = dz * cam->m20 + dy * cam->m10 + dx * cam->m00 + cam->tx;
			q[1] = dz * cam->m21 + dy * cam->m11 + dx * cam->m01 + cam->ty;
			q[2] = dz * cam->m22 + dy * cam->m12 + dx * cam->m02 + cam->tz;
			q += 0x14;
			i--;
		} while (i != 0);
		if (!(fcn_00437ee0(base, 0, 0) & 0x40)) {
			*(unsigned char*) (o + 0x216) |= 0x80;
			fcn_00457290(o, s, *(int*) 0x6b8300, h);
		}
	}
}
