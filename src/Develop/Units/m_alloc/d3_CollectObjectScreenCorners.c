extern char* d3_ActiveCamera;
extern float flt_1_0;
extern int g_14ce860;
extern int g_14ce864;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float d3_ProjectionDist;
extern float g_1052c00[];

extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern void __cdecl d3_UpdateObjectCameraTransform(int scene, char* data, int flag);
extern void __cdecl d3_BlendMeshVertices(int device, unsigned int* flags, void* bbox, int mode);
extern void __stdcall fcn_005eb225(float* dst, unsigned int* src, void* ctx);
extern void __stdcall fcn_005eb2e4(float* dst, unsigned int* src, char* a, float* b,
	float* c, void* ctx);

/* ADDRESS: GOLDTL 0x00444ff0 */
unsigned char __cdecl d3_CollectObjectScreenCorners(int sceneObject, int* selectionBounds)
{
	char* holder;
	char* model;
	float* verts;
	float* bbox;
	unsigned int* flags;
	unsigned int src[3];
	float view[16];
	float* f;
	int count;
	int total;
	int index;
	int i;
	int m;
	int j;
	int px;
	int py;

	if (*(int*) (sceneObject + 0x1ec) == 0)
		return 1;
	holder = *(char**) (sceneObject + 0x1cc);
	if (holder == 0)
		return 1;
	model = *(char**) (holder + 0x318);
	if (model == 0)
		return 1;
	count = *(int*) (model + 0x1e4);
	index = 0;
	if (count > 0) {
		int* ids;
		ids = *(int**) (model + 0x284);
		do {
			if (*ids == *selectionBounds)
				break;
			index++;
			ids++;
		} while (index < count);
	}
	if (index >= count)
		return 1;
	view[14] = 0.0f;
	view[13] = 0.0f;
	view[12] = 0.0f;
	view[11] = 0.0f;
	view[9] = 0.0f;
	view[8] = 0.0f;
	view[7] = 0.0f;
	view[6] = 0.0f;
	view[4] = 0.0f;
	view[3] = 0.0f;
	view[2] = 0.0f;
	view[1] = 0.0f;
	view[15] = 1.0f;
	view[10] = 1.0f;
	view[5] = 1.0f;
	view[0] = 1.0f;
	d3_UpdateObjectCameraTransform(sceneObject, d3_ActiveCamera, 0);
	total = *(int*) (model + 0x44);
	verts = (float*) m_alloc(total * 0x18, "!d3:TransformedPoints");
	if (*(char*) (*(int*) (sceneObject + 0x1cc) + 0x4a0) != 0
		&& (*(unsigned char*) (model + 0x2a1) & 2) != 0) {
		bbox = (float*) m_alloc(total << 5, "!d3int:GetTextureBBoxVertices");
		flags = (unsigned int*) m_alloc(total << 2, "!d3int:GetTextureBBoxRepeat");
		for (i = 0; i < total; i++)
			flags[i] = 1;
		d3_BlendMeshVertices(*(unsigned int*) (sceneObject + 0x1cc), flags, bbox, 0);
		m_FreeTracked(flags);
		if (total > 0) {
			for (i = 0; i < total; i++) {
				src[0] = *(unsigned int*) ((char*) bbox + i * 0x20);
				src[1] = *(unsigned int*) ((char*) bbox + i * 0x20 + 4);
				src[2] = *(unsigned int*) ((char*) bbox + i * 0x20 + 8);
				f = verts + i * 6;
				fcn_005eb225(f + 3, src, (void*) (*(int*) (sceneObject + 0x1ec) + 0x48));
				f[0] = d3_ProjectionDist * (flt_1_0 / f[5]) * f[3] + d3_ViewportCenterX;
				f[1] = d3_ProjectionScaleY * f[4] * (flt_1_0 / f[5]) + g_1052bc8;
			}
		}
		m_FreeTracked(bbox);
	} else {
		if (total > 0) {
			for (i = 0; i < total; i++) {
				src[0] = *(unsigned int*) (*(int*) (model + 0x27c) + i * 0xc);
				src[1] = *(unsigned int*) (*(int*) (model + 0x27c) + i * 0xc + 4);
				src[2] = *(unsigned int*) (*(int*) (model + 0x27c) + i * 0xc + 8);
				f = verts + i * 6;
				fcn_005eb2e4(f, src, g_1052be0, g_1052c00, view,
					(void*) (*(int*) (sceneObject + 0x1ec) + 0x48));
				fcn_005eb225(f + 3, src,
					(void*) (*(int*) (sceneObject + 0x1ec) + 0x48));
			}
		}
	}
	total = *(int*) (model + 0x4c);
	for (i = 0; i < total; i++) {
		if (*(int*) (*(int*) (model + 0x288) + i * 4) != index)
			continue;
		*(char*) (selectionBounds + 0x21) = 1;
		j = 0;
		do {
			int idx;
			idx = *(unsigned short*) (*(int*) (model + 0x280) + (i * 3 + j) * 2);
			f = verts + idx * 6;
			px = (int) f[0];
			py = (int) f[1];
			m = i * 3 + j;
			if (py + px < selectionBounds[0x1a] + selectionBounds[0x19]) {
				selectionBounds[0x19] = px;
				selectionBounds[0x1a] = py;
				selectionBounds[0x11] = *(int*) (*(int*) (model + 0x28c) + m * 8);
				selectionBounds[0x12] = *(int*) (*(int*) (model + 0x28c) + m * 8 + 4);
				selectionBounds[1] = *(int*) (f + 3);
				selectionBounds[2] = *(int*) (f + 4);
				selectionBounds[3] = *(int*) (f + 5);
			}
			if ((unsigned int) ((g_14ce860 - px) - 1 + py)
				< (unsigned int) ((selectionBounds[0x1c] - selectionBounds[0x1b]) - 1 + g_14ce860)) {
				selectionBounds[0x1b] = px;
				selectionBounds[0x1c] = py;
				selectionBounds[0x13] = *(int*) (*(int*) (model + 0x28c) + m * 8);
				selectionBounds[0x14] = *(int*) (*(int*) (model + 0x28c) + m * 8 + 4);
				selectionBounds[5] = *(int*) (f + 3);
				selectionBounds[6] = *(int*) (f + 4);
				selectionBounds[7] = *(int*) (f + 5);
			}
			if ((unsigned int) ((g_14ce864 - py) - 1 + px)
				< (unsigned int) ((selectionBounds[0x1d] - selectionBounds[0x1e]) - 1 + g_14ce864)) {
				selectionBounds[0x1d] = px;
				selectionBounds[0x1e] = py;
				selectionBounds[0x15] = *(int*) (*(int*) (model + 0x28c) + m * 8);
				selectionBounds[0x16] = *(int*) (*(int*) (model + 0x28c) + m * 8 + 4);
				selectionBounds[9] = *(int*) (f + 3);
				selectionBounds[10] = *(int*) (f + 4);
				selectionBounds[0x0b] = *(int*) (f + 5);
			}
			if ((unsigned int) (((g_14ce864 - py) - px) - 2 + g_14ce860)
				< (unsigned int) (((g_14ce864 - selectionBounds[0x20]) - selectionBounds[0x1f]) - 2 + g_14ce860)) {
				selectionBounds[0x1f] = px;
				selectionBounds[0x20] = py;
				selectionBounds[0x17] = *(int*) (*(int*) (model + 0x28c) + m * 8);
				selectionBounds[0x18] = *(int*) (*(int*) (model + 0x28c) + m * 8 + 4);
				selectionBounds[0x0d] = *(int*) (f + 3);
				selectionBounds[0x0e] = *(int*) (f + 4);
				selectionBounds[0x0f] = *(int*) (f + 5);
			}
		} while (++j < 3);
	}
	m_FreeTracked(verts);
	return 1;
}
