typedef struct Vec3 {
	float x;
	float y;
	float z;
} Vec3;

void __cdecl fcn_00455450(char*, char*, Vec3*, Vec3*);
void __cdecl fcn_00438100(char*, char*, char);

/* Projects an object's bounds into screen space and fills a left/top/right/
 * bottom rectangle. */
/* ADDRESS: GOLDTL 0x00443e10 */
char __cdecl fcn_00443e10(char* obj, int* rc)
{
	float p[4];
	float t;
	float sx;
	float sy;
	float d;
	char* cam;
	char* sub;
	char* list;
	float* rec;
	unsigned char b;
	int* vt;
	int i;
	int ix;
	int iy;

	if (rc == 0 || obj == 0) {
		return 0;
	}
	if (*(int*) (obj + 0x218) == 0) {
		fcn_00455450(obj, *(char**) 0x6b8014, (Vec3*) (obj + 0x4c), (Vec3*) p);
		t = *(float*) 0x6628a0 / p[2];
		sx = p[0] * *(float*) 0x10432a4 * t + *(float*) 0x1052bc0;
		sy = p[1] * *(float*) 0x1042584 * t + *(float*) 0x1052bc8;
		d = *(float*) (obj + 0x68) * *(float*) 0x10432a4 * t * *(float*) 0x6628cc;
		rc[0] = (int) (sx - d);
		rc[2] = (int) (sx + d);
		rc[1] = (int) (sy - d);
		rc[3] = (int) (sy + d);
		return 1;
	}
	if (*(int*) (obj + 0x1ec) == 0) {
		return 0;
	}
	if (*(unsigned char*) (*(int*) (obj + 0x1ec) + 0x163d) & 0x40) {
		return 0;
	}
	sub = *(char**) (obj + 0x1cc);
	if (sub == 0) {
		return 0;
	}
	if (*(int*) (sub + 0x318) == 0) {
		return 0;
	}
	b = *(unsigned char*) (obj + 0x214) & 0x20;
	cam = (char*) ((int) *(char**) 0x6b8014 & ~-(b != 0));
	fcn_00438100(obj, cam, 0);
	vt = *(int**) (sub + 0x318);
	list = (char*) ((int (__cdecl*) (char*, char*, char*)) vt[0x7c])(obj, sub, *(char**) (obj + 0x1ec) + 0x48);
	rc[0] = 0x10000;
	rc[1] = 0x10000;
	rc[2] = -0x10000;
	rc[3] = -0x10000;
	rec = (float*) (list + 4);
	i = 8;
	do {
		t = *(float*) 0x6628a0 / rec[1];
		ix = (int) (rec[-1] * *(float*) 0x10432a4 * t + *(float*) 0x1052bc0);
		rc[0] = rc[0] < ix ? rc[0] : ix;
		rc[2] = rc[2] > ix ? rc[2] : ix;
		iy = (int) (rec[0] * *(float*) 0x1042584 * t + *(float*) 0x1052bc8);
		rc[1] = rc[1] < iy ? rc[1] : iy;
		rc[3] = rc[3] > iy ? rc[3] : iy;
		rec += 0x14;
	} while (--i != 0);
	rc[0] = rc[0] > *(int*) 0x1042570 ? rc[0] : *(int*) 0x1042570;
	rc[2] = rc[2] < *(int*) 0x1042578 - 1 ? rc[2] : *(int*) 0x1042578 - 1;
	rc[1] = rc[1] > *(int*) 0x1042574 ? rc[1] : *(int*) 0x1042574;
	rc[3] = rc[3] < *(int*) 0x104257c - 1 ? rc[3] : *(int*) 0x104257c - 1;
	return 1;
}
