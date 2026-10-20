extern char s_67a1ec[];
extern char s_67a218[];
extern char s_67a238[];
extern char s_67a260[];
extern float g_6628a0;
extern double g_662c70;

void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
float __cdecl fcn_004353b0(float* v, int n);
void __cdecl fcn_004518a0(float* v);
void __cdecl fcn_00451d70(float* a, float* b, float* c, float* n);

/* ADDRESS: GOLDTL 0x00434ba0 */
void __cdecl fcn_00434ba0(char* anim, char* mesh)
{
	float* points;
	float* normals;
	float* bbox;
	char* frame;
	float pmin[3];
	float pmax[3];
	float sum[3];
	float v;
	int i;
	int j;
	int k;

	points = (float*) m_alloc(*(int*) (mesh + 0x44) << 4, s_67a260);
	normals = (float*) m_alloc(*(int*) (mesh + 0x4c) << 4, s_67a238);
	for (i = 0; i < *(int*) (anim + 0x148); i++) {
		frame = *(char**) (anim + 0x15c) + i * 0xc0;
		*(int*) (frame + 0xb8) = (int) m_alloc(*(int*) (mesh + 0x44) * 3, s_67a218);
		if (*(int*) (frame + 0xbc) != 0) {
			for (j = 0; j < *(int*) (anim + 0x140); j++) {
				points[j * 4 + 0] = *(float*) (*(int*) (mesh + 0x27c) + j * 12)
					+ *(float*) (*(int*) (frame + 0xbc) + j * 12);
				points[j * 4 + 1] = *(float*) (*(int*) (mesh + 0x27c) + j * 12 + 4)
					+ *(float*) (*(int*) (frame + 0xbc) + j * 12 + 4);
				points[j * 4 + 2] = *(float*) (*(int*) (mesh + 0x27c) + j * 12 + 8)
					+ *(float*) (*(int*) (frame + 0xbc) + j * 12 + 8);
			}
		}
		else {
			for (j = 0; j < *(int*) (anim + 0x140); j++) {
				v = (float) *(unsigned char*) (*(int*) (frame + 0xb4) + j * 3)
					* *(float*) (frame + 0x14) + *(float*) (frame + 0x08);
				points[j * 4 + 0] = v + *(float*) (*(int*) (mesh + 0x27c) + j * 12);
				v = (float) *(unsigned char*) (*(int*) (frame + 0xb4) + j * 3 + 1)
					* *(float*) (frame + 0x18) + *(float*) (frame + 0x0c);
				points[j * 4 + 1] = v + *(float*) (*(int*) (mesh + 0x27c) + j * 12 + 4);
				v = (float) *(unsigned char*) (*(int*) (frame + 0xb4) + j * 3 + 2)
					* *(float*) (frame + 0x1c) + *(float*) (frame + 0x10);
				points[j * 4 + 2] = v + *(float*) (*(int*) (mesh + 0x27c) + j * 12 + 8);
			}
		}
		*(float*) (frame + 0x38) = *(float*) (mesh + 0x1d4)
			- fcn_004353b0(points, *(int*) (mesh + 0x44));
		for (j = 0; j < *(int*) (mesh + 0x4c); j++) {
			unsigned short* tri = (unsigned short*) (*(int*) (mesh + 0x280) + j * 6);

			fcn_00451d70(points + tri[0] * 4, points + tri[1] * 4,
				points + tri[2] * 4, normals + j * 4);
		}
		pmin[0] = 1e+10f;
		pmin[1] = 1e+10f;
		pmin[2] = 1e+10f;
		pmax[0] = -1e+10f;
		pmax[1] = -1e+10f;
		pmax[2] = -1e+10f;
		for (j = 0; j < *(int*) (anim + 0x140); j++) {
			if (points[j * 4 + 0] <= pmin[0]) {
				pmin[0] = points[j * 4 + 0];
			}
			if (points[j * 4 + 1] <= pmin[1]) {
				pmin[1] = points[j * 4 + 1];
			}
			if (points[j * 4 + 2] <= pmin[2]) {
				pmin[2] = points[j * 4 + 2];
			}
			if (pmax[0] <= points[j * 4 + 0]) {
				pmax[0] = points[j * 4 + 0];
			}
			if (pmax[1] <= points[j * 4 + 1]) {
				pmax[1] = points[j * 4 + 1];
			}
			if (pmax[2] <= points[j * 4 + 2]) {
				pmax[2] = points[j * 4 + 2];
			}
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;
			for (k = 0; k < *(int*) (mesh + 0x4c); k++) {
				unsigned short* tri = (unsigned short*) (*(int*) (mesh + 0x280) + k * 6);

				if (tri[0] == j || tri[1] == j || tri[2] == j) {
					sum[0] = sum[0] + normals[k * 4 + 0];
					sum[1] = sum[1] + normals[k * 4 + 1];
					sum[2] = sum[2] + normals[k * 4 + 2];
				}
			}
			fcn_004518a0(sum);
			sum[0] = sum[0] + g_6628a0;
			sum[1] = sum[1] + g_6628a0;
			sum[2] = sum[2] + g_6628a0;
			*(char*) (*(int*) (frame + 0xb8) + j * 3 + 0) = (char) (sum[0] * g_662c70);
			*(char*) (*(int*) (frame + 0xb8) + j * 3 + 1) = (char) (sum[1] * g_662c70);
			*(char*) (*(int*) (frame + 0xb8) + j * 3 + 2) = (char) (sum[2] * g_662c70);
		}
		*(float*) (frame + 0x3c) = pmin[0];
		*(float*) (frame + 0x40) = pmin[1];
		*(float*) (frame + 0x44) = pmin[2];
		*(float*) (frame + 0x48) = pmax[0];
		*(float*) (frame + 0x4c) = pmax[1];
		*(float*) (frame + 0x50) = pmax[2];
	}
	m_FreeTracked(normals);
	m_FreeTracked(points);
	bbox = (float*) m_alloc(*(int*) (anim + 0x148) << 5, s_67a1ec);
	for (i = 0; i < *(int*) (anim + 0x148); i++) {
		frame = *(char**) (anim + 0x15c) + i * 0xc0;
		bbox[i * 8 + 0] = *(float*) (frame + 0x3c);
		bbox[i * 8 + 1] = *(float*) (frame + 0x40);
		bbox[i * 8 + 2] = *(float*) (frame + 0x44);
		bbox[i * 8 + 4] = *(float*) (frame + 0x48);
		bbox[i * 8 + 5] = *(float*) (frame + 0x4c);
		bbox[i * 8 + 6] = *(float*) (frame + 0x50);
	}
	for (i = 0; i < *(int*) (anim + 0x148); i++) {
		frame = *(char**) (anim + 0x15c) + i * 0xc0;
		if (i > 0) {
			if (*(float*) (frame - 0x84) <= bbox[i * 8 + 0]) {
				bbox[i * 8 + 0] = *(float*) (frame - 0x84);
			}
			if (*(float*) (frame - 0x80) <= bbox[i * 8 + 1]) {
				bbox[i * 8 + 1] = *(float*) (frame - 0x80);
			}
			if (*(float*) (frame - 0x7c) <= bbox[i * 8 + 2]) {
				bbox[i * 8 + 2] = *(float*) (frame - 0x7c);
			}
			if (bbox[i * 8 + 4] <= *(float*) (frame - 0x78)) {
				bbox[i * 8 + 4] = *(float*) (frame - 0x78);
			}
			if (bbox[i * 8 + 5] <= *(float*) (frame - 0x74)) {
				bbox[i * 8 + 5] = *(float*) (frame - 0x74);
			}
			if (bbox[i * 8 + 6] <= *(float*) (frame - 0x70)) {
				bbox[i * 8 + 6] = *(float*) (frame - 0x70);
			}
		}
		if (i < *(int*) (anim + 0x148) - 1) {
			if (*(float*) (frame + 0xfc) <= bbox[i * 8 + 0]) {
				bbox[i * 8 + 0] = *(float*) (frame + 0xfc);
			}
			if (*(float*) (frame + 0x100) <= bbox[i * 8 + 1]) {
				bbox[i * 8 + 1] = *(float*) (frame + 0x100);
			}
			if (*(float*) (frame + 0x104) <= bbox[i * 8 + 2]) {
				bbox[i * 8 + 2] = *(float*) (frame + 0x104);
			}
			if (bbox[i * 8 + 4] <= *(float*) (frame + 0x108)) {
				bbox[i * 8 + 4] = *(float*) (frame + 0x108);
			}
			if (bbox[i * 8 + 5] <= *(float*) (frame + 0x10c)) {
				bbox[i * 8 + 5] = *(float*) (frame + 0x10c);
			}
			if (bbox[i * 8 + 6] <= *(float*) (frame + 0x110)) {
				bbox[i * 8 + 6] = *(float*) (frame + 0x110);
			}
		}
	}
	for (i = 0; i < *(int*) (anim + 0x148); i++) {
		frame = *(char**) (anim + 0x15c) + i * 0xc0;
		*(float*) (frame + 0x3c) = bbox[i * 8 + 0];
		*(float*) (frame + 0x40) = bbox[i * 8 + 1];
		*(float*) (frame + 0x44) = bbox[i * 8 + 2];
		*(float*) (frame + 0x48) = bbox[i * 8 + 4];
		*(float*) (frame + 0x4c) = bbox[i * 8 + 5];
		*(float*) (frame + 0x50) = bbox[i * 8 + 6];
	}
	m_FreeTracked(bbox);
}
