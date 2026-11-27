#include <math.h>

extern char* d3_ActiveCamera;

extern float g_1042150;
extern float g_1042154;
extern float g_1042158;
extern float g_1042160;
extern float g_1042164;
extern float g_1042168;
extern float g_1042180;
extern float g_1042184;
extern float g_1042188;
extern float g_1042190;
extern float g_1042194;
extern float g_1042198;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_10432a8;
extern int g_1042a04;

extern unsigned int __cdecl d3_ProjectFloorCellBounds(int, int, int, int);
extern unsigned char __cdecl d3_TestBoxAgainstFrustum(void*, char*, char*);

typedef int (__stdcall* D3_MESH_QUERY_FN)(void*);


/* ADDRESS: GOLDTL 0x00441050 */
/* Recomputes the two cached shadow boxes of an entity from the eight
 * surrounding placements and sums the visibility/occupancy callbacks of the
 * 8x8 cell grid. Returns the number of lit cells. */
int __cdecl d3_UpdateFloorVisibility(char* floor)
{
	float* m;
	float dx;
	float dy;
	float dz;



	float* f;
	float* p;
	char* w;
	void** objects;
	D3_MESH_QUERY_FN fn;
	int count;


	float center[4];
	unsigned int i;
	unsigned int j;
	int k;
	unsigned char res;

	m = (float*) d3_ActiveCamera;
	dx = *(float*) (floor + 0x50) - m[0x13];
	dy = *(float*) (floor + 0x54) - m[0x14];
	dz = *(float*) (floor + 0x58) - m[0x15];
	count = 0;
	g_1042180 = dy * m[0x67] + dz * m[0x6b] + dx * m[0x63];
	g_1042184 = dx * m[0x64] + dy * m[0x68] + dz * m[0x6c];
	g_1042188 = dy * m[0x69] + dz * m[0x6d] + dx * m[0x65];
	g_1042190 = *(float*) (floor + 0x64) * m[0x67] + *(float*) (floor + 0x68) * m[0x6b]
		+ m[0x63] * *(float*) (floor + 0x60);
	g_1042194 = m[0x64] * *(float*) (floor + 0x60) + m[0x68] * *(float*) (floor + 0x64)
		+ m[0x6c] * *(float*) (floor + 0x68);
	g_1042198 = *(float*) (floor + 0x64) * m[0x69] + *(float*) (floor + 0x68) * m[0x6d]
		+ m[0x65] * *(float*) (floor + 0x60);
	g_1042150 = *(float*) (floor + 0x74) * m[0x67] + *(float*) (floor + 0x78) * m[0x6b]
		+ m[0x63] * *(float*) (floor + 0x70);
	g_1042154 = m[0x64] * *(float*) (floor + 0x70) + m[0x68] * *(float*) (floor + 0x74)
		+ m[0x6c] * *(float*) (floor + 0x78);
	g_1042158 = *(float*) (floor + 0x74) * m[0x69] + *(float*) (floor + 0x78) * m[0x6d]
		+ m[0x65] * *(float*) (floor + 0x70);
	g_1042160 = *(float*) (floor + 0x84) * m[0x67] + *(float*) (floor + 0x88) * m[0x6b]
		+ m[0x63] * *(float*) (floor + 0x80);
	g_1042164 = m[0x64] * *(float*) (floor + 0x80) + m[0x68] * *(float*) (floor + 0x84)
		+ m[0x6c] * *(float*) (floor + 0x88);
	g_1042168 = *(float*) (floor + 0x84) * m[0x69] + *(float*) (floor + 0x88) * m[0x6d]
		+ m[0x65] * *(float*) (floor + 0x80);
	for (i = 0, w = floor + 0x280; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			p = (float*) d3_ProjectFloorCellBounds((int) floor, (int) (w - 0x1e0), j, i);
			res = d3_TestBoxAgainstFrustum(p, w, w + 4);
			*(unsigned char*) (w + 0x11) = res;
			if ((res & 0x40) != 0) {
				*(char*) (w + 0xe) = 0;
			} else {
				*(char*) (w + 0xe) = 1;
				f = p + 0x16;
				center[0] = p[0];
				center[1] = p[1];
				center[2] = p[2];
				k = 7;
				do {
					center[0] = center[0] + f[-2];
					center[1] = center[1] + f[-1];
					center[2] = center[2] + *f;
					f = f + 0x14;
					k -= 1;
				} while (k != 0);
				center[0] = center[0] * 0.125f;
				count += 1;
				center[1] = center[1] * 0.125f;
				center[2] = center[2] * 0.125f;
				*(float*) (w - 0x20) = center[0];
				*(float*) (w - 0x1c) = center[1];
				*(float*) (w - 0x18) = center[2];
				center[3] = (float) sqrt(center[2] * center[2] + center[1] * center[1] + center[0] * center[0]);
				*(float*) (w - 4) = center[3];
			}
			objects = (void**) (w - 0x1cc);
			k = 8;
			do {
				if (objects[1] != 0) {
					if (*(unsigned char*) (w + 0xe) > 0) {
						d3_RenderedVertexCount += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[1] + 0x14))(objects[1]);
						g_1042a08 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[1] + 0x10))(objects[1]);
					}
					g_10432a8 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[1] + 0x10))(objects[1]);
					g_1042a04 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[1] + 0x14))(objects[1]);
				}
				if (objects[0] != 0) {
					if (*(unsigned char*) (w + 0xe) > 0) {
						d3_RenderedVertexCount += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[0] + 0x14))(objects[0]);
						g_1042a08 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[0] + 0x10))(objects[0]);
					}
					g_10432a8 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[0] + 0x10))(objects[0]);
					g_1042a04 += (*(D3_MESH_QUERY_FN*) ((char*) *(void**) objects[0] + 0x14))(objects[0]);
				}
				objects = (void**) ((char*) objects + 0x34);
				k -= 1;
			} while (k != 0);
			w += 0x1f4;
		}
	}
	return count;
}
