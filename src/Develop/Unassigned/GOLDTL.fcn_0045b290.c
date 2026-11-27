#include <string.h>

extern char* d3_ActiveCamera;
extern int g_67a370;

typedef struct {
	float mn[4];
	float mx[4];
} D3SM_BBOX;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, void*);
void __cdecl d3sm_AccumulateObjectBounds(void);
void __cdecl d3sm_DrawMeshTriangles(void);
void __cdecl d3sm_BuildFromTerrain(int*, int*);
void __cdecl d3_RelabelMatchingCells(int*, int, int);

/* ADDRESS: GOLDTL 0x0045b290 */
void __cdecl d3sm_Rebuild(int* m, unsigned char* t)
{
	D3SM_BBOX box;
	float pts[8][4];
	float* f;
	int* cells;
	unsigned char* bytes;
	unsigned char* p;
	int n;
	int fn;
	int i;
	int j;
	int minb;
	int maxb;
	float n0;
	float mn[4];
	float org[4];
	double base_x;
	float side_x;
	float side_y;
	float side_z;
	float range;
	float maxz;

	if (!m || m[8] <= 0)
		return;
	if (m[10] == 0)
		return;
	if (!d3_ActiveCamera)
		return;
	box.mn[0] = 1e10f;
	box.mn[1] = 1e10f;
	box.mn[2] = 1e10f;
	box.mx[0] = -1e10f;
	box.mx[1] = -1e10f;
	box.mx[2] = -1e10f;
	d3_VisitSceneObjects(g_67a370, 0, 0x40, d3sm_AccumulateObjectBounds, &box);
	cells = (int*) m[9];
	if (cells) {
		fn = m[8] * m[8] * 0x1c;
		/* Reviewed original operand-homed fill (inline fill/copy block). */
		__asm {
			mov edi, cells
			mov ebx, fn
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		for (i = 0; i < m[8] * m[8]; i++)
			cells[i * 7] = 1;
	}
	if (t) {
		f = (float*) t;
		maxb = 0;
		minb = 0xff;
		p = t + 0x28c;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (maxb <= p[1])
					maxb = p[1];
				if (minb >= p[0])
					minb = p[0];
				p += 500;
			}
		}
		base_x = (float) minb * f[0x20] + f[0x14];
		org[1] = (float) minb * f[0x21] + f[0x15];
		org[2] = (float) minb * f[0x22] + f[0x16];
		pts[0][0] = (float) base_x;
		pts[0][1] = org[1];
		pts[0][2] = org[2];
		n0 = (float) *(int*) t;
		side_x = n0 * f[0x18];
		pts[1][0] = side_x + base_x;
		side_y = n0 * f[0x19];
		pts[1][1] = side_y + org[1];
		side_z = n0 * f[0x1a];
		pts[1][2] = side_z + org[2];
		pts[2][0] = n0 * f[0x1c] + base_x;
		pts[2][1] = n0 * f[0x1d] + org[1];
		pts[2][2] = n0 * f[0x1e] + org[2];
		pts[3][0] = (float) side_x + pts[2][0];
		pts[3][1] = (float) side_y + pts[2][1];
		pts[3][2] = (float) side_z + pts[2][2];
		range = (float) (maxb - minb);
		org[0] = range * f[0x20];
		org[1] = range * f[0x21];
		for (i = 0; i < 4; i++) {
			pts[4 + i][0] = pts[i][0] + org[0];
			pts[4 + i][1] = pts[i][1] + org[1];
			pts[4 + i][2] = pts[i][2] + range * f[0x22];
		}
		mn[0] = 1e10f;
		mn[1] = 1e10f;
		mn[2] = 1e10f;
		org[0] = -1e10f;
		org[1] = -1e10f;
		maxz = -1e10f;
		for (i = 0; i < 8; i++) {
			if (!(pts[i][0] > mn[0]))
				mn[0] = pts[i][0];
			if (!(pts[i][1] > mn[1]))
				mn[1] = pts[i][1];
			if (!(pts[i][2] > mn[2]))
				mn[2] = pts[i][2];
			if (!(pts[i][0] < org[0]))
				org[0] = pts[i][0];
			if (!(pts[i][1] < org[1]))
				org[1] = pts[i][1];
			if (!(maxz > pts[i][2]))
				maxz = pts[i][2];
		}
		if (!(box.mn[1] < mn[1]))
			box.mn[1] = mn[1];
		if (!(box.mx[1] > org[1]))
			box.mx[1] = org[1];
		box.mn[0] = mn[0];
		box.mx[0] = org[0];
		box.mn[2] = mn[2];
		box.mx[2] = maxz;
	}
	n = m[8];
	m[2] = *(int*) &box.mx[2];
	*(float*) (m + 1) = box.mn[1] + 1.0f;
	*(float*) m = box.mn[0];
	*(float*) (m + 4) = (box.mx[0] - box.mn[0]) / ((float) n - 1.75f);
	*(float*) (m + 5) = (box.mx[1] - box.mn[1]) * 0.0039525693f;
	*(float*) (m + 6) = (box.mn[2] - box.mx[2]) / ((float) n - 1.75f);
	if (t) {
		d3sm_BuildFromTerrain((int*) t, m);
	} else {
		bytes = (unsigned char*) m[10];
		fn = n * n;
		/* Reviewed original operand-homed fill (inline fill/copy block). */
		__asm {
			mov edi, bytes
			mov ebx, fn
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	d3_VisitSceneObjects(g_67a370, 0, 0x40, d3sm_DrawMeshTriangles, m);
	if (m[9]) {
		d3_RelabelMatchingCells(m, 0xb, 0xc);
		for (i = 0; i < m[8]; i++) {
			((int*) m[9])[i * 7] = 0xd;
			((int*) m[9])[((m[8] - 1) * m[8] + i) * 7] = 0xd;
			((int*) m[9])[(m[8] * i) * 7] = 0xd;
			((int*) m[9])[(m[8] * (i + 1) - 1) * 7] = 0xd;
		}
	}
}
