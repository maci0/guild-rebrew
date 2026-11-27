#define MIN(a, b) ((b) > (a) ? (a) : (b))
#define MAX(a, b) ((b) < (a) ? (a) : (b))

extern char* d3_ActiveCamera;

void __cdecl d3_UpdateObjectCameraTransform(char*, char*, int);
void __cdecl d3_TransformToObjectSpace(char*, float*, float*);

/* ADDRESS: GOLDTL 0x00413480 */
int __cdecl d3_ComputeObjectFootprintCorners(char* obj, float a1, float* a2, float* a3, float* a4, float* a5)
{
	float lo[4];
	float hi[4];
	float t[4];
	char* m;
	float* p;
	float* q;
	char* e;
	int n;
	int i;
	int j;

	if (*(int*) (obj + 0x218) != 4)
		return 1;
	if ((*(unsigned char*) (obj + 0x216) & 0x20) == 0)
		d3_UpdateObjectCameraTransform(obj, d3_ActiveCamera, 0);
	m = *(char**) (*(char**) (obj + 0x1cc) + 0x318);
	n = *(int*) (m + 0x44);
	i = 0;
	if (n > 0) {
		p = (float*) *(char**) (m + 0x27c);
		e = *(char**) (obj + 0x1ec);
		do {
			if (p[1] * *(float*) (e + 0x1c) + p[2] * *(float*) (e + 0x2c) + p[0] * *(float*) (e + 0xc) + *(float*) (e + 0x3c) <= a1) {
				q = p;
				lo[0] = q[0];
				hi[0] = q[0];
				lo[1] = q[1];
				hi[1] = q[1];
				lo[2] = q[2];
				hi[2] = q[2];
				break;
			}
			i++;
			p += 3;
		} while (i < n);
	}
	if (i < n) {
		p = (float*) *(char**) (m + 0x27c) + i * 3;
		e = *(char**) (obj + 0x1ec);
		n -= i;
		do {
			if (p[1] * *(float*) (e + 0x1c) + p[2] * *(float*) (e + 0x2c) + p[0] * *(float*) (e + 0xc) + *(float*) (e + 0x3c) <= a1) {
				for (j = 0, q = p; j < 3; j++, q++) {
					lo[j] = MIN(lo[j], *q);
					hi[j] = MAX(hi[j], *q);
				}
			}
			p += 3;
			n--;
		} while (n);
	}
	t[0] = lo[0];
	t[1] = lo[1];
	t[2] = lo[2];
	d3_TransformToObjectSpace(obj, t, a2);
	t[0] = hi[0];
	t[1] = lo[1];
	t[2] = lo[2];
	d3_TransformToObjectSpace(obj, t, a3);
	t[0] = hi[0];
	t[1] = lo[1];
	t[2] = hi[2];
	d3_TransformToObjectSpace(obj, t, a4);
	t[0] = lo[0];
	t[1] = lo[1];
	t[2] = hi[2];
	d3_TransformToObjectSpace(obj, t, a5);
	return 0;
}
