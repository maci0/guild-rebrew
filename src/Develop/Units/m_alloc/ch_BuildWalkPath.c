#include <string.h>

extern int __cdecl fcn_0064d41a(char* buf, const char* fmt, ...);
extern int __cdecl d3_RemoveObjectAnimation();
extern int __cdecl d3_ReleaseAnim();
extern int __cdecl d3_FindAnimByName();
extern int __cdecl d3_RemoveObjectAnim();
extern int __cdecl d3_GetContextIndex();
#include "Develop/DieGildeAddOn/game/ch_queue.h"
extern int __cdecl ch_FindCharacterByName();
extern char __cdecl d3sm_3D2SuperMap();
extern void __cdecl m_FreeTracked(void* ptr);
extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern int __cdecl ch_FindWalkableCell();
extern short __cdecl FindPath();
extern int __cdecl ch_DownsamplePath();
extern int __cdecl d3_GridPointToWorld();
extern int __cdecl CompareVector3WithinTolerance();

struct path_421350 {
	int n;
	int max;
	unsigned char* cells;
};
/* Path start offset vector, 0x6b5c38..0x6b5c44. */
float g_6b5c38[3];
extern char ch_SceneDebugSwitch;
/* Path scratch header at 0x14d0c20..0x14d0c2c. */
struct path_421350 g_14d0c20;

typedef struct {
	unsigned int x;
	unsigned int z;
	int flags;
} GRID_CELL;

/* Rebuilds one object's render state from its definition record. Native
 * extent 1056 bytes. */
/* ADDRESS: GOLDTL 0x004094c0 */
unsigned int __cdecl ch_BuildWalkPath(int rec, int gridContext)
{
	char buf[0x60];
	int v14;
	int v15;
	int obj;
	int r;
	void (__cdecl* fn)(int);

	obj = *(int*) (rec + 0x14);
	if (*(int*) (obj + 0x7c) != 0) {
		fcn_0064d41a(buf, (char*) 0x67553c, obj);
		d3_RemoveObjectAnimation(*(int*) (*(int*) (obj + 0x34) + 0x1ec) + 0xf4, buf);
		r = d3_FindAnimByName(buf);
		d3_ReleaseAnim(r, 1);
		*(int*) (obj + 0x7c) = 0;
	}
	d3_RemoveObjectAnim(*(int*) (obj + 0x34));
	*(int*) (obj + 0x80) = 0;
	*(int*) (obj + 0x7c) = 0;
	*(int*) (obj + 0x70) = 0;
	*(float*) (obj + 0x1a4) = 1.0f;
	*(unsigned short*) (*(int*) (rec + 0x14) + 0x8c) &= 0xfff7;
	*(int*) (rec + 0xf4) = 0;
	*(int*) (rec + 0x104) = 0;
	*(int*) (rec + 0x154) = -1;
	memset((void*) (obj + 0x90), 0, 0x80);
	{
		GRID_CELL cell;
		cell.x = *(unsigned int*) (rec + 0x30);
		cell.z = *(unsigned int*) (rec + 0x34);
		if (d3_GetContextIndex(*(int*) (obj + 0x88)) != *(int*) (rec + 0x38)) {
			ch_RemoveQueueEntry((char*) rec);
			return 0;
		}
		if (*(unsigned char*) (rec + 0x160) & 8)
			*(int*) (rec + 0x110) = ch_FindCharacterByName(rec + 0x114);
		r = d3sm_3D2SuperMap(gridContext, *(int*) (*(int*) (rec + 0x14) + 0x34) + 0x4c,
		    &v15, &v14, &cell.flags);
		if (r == 0) {
			if (ch_SceneDebugSwitch != 0)
				*(unsigned char*) (*(int*) (rec + 0x14) + 0x8c) |= 8;
			if (*(int*) (rec + 0xf4) != 0) {
				m_FreeTracked((void*) *(int*) (rec + 0xf4));
				*(int*) (rec + 0xf4) = 0;
			}
			ch_RemoveQueueEntry((char*) rec);
			return 0;
		}
		if (v15 < 1) {
			v15 = 1;
		}
		else {
			if (v15 > *(int*) (gridContext + 0x20) - 2)
				v15 = *(int*) (gridContext + 0x20) - 2;
		}
		if (v14 < 1) {
			v14 = 1;
		}
		else {
			if (v14 > *(int*) (gridContext + 0x20) - 2)
				v14 = *(int*) (gridContext + 0x20) - 2;
		}
		if (*(unsigned char*) (obj + 4) & 4)
			*(unsigned int*) (rec + 0x160) &= 0xffffffef;
		if (*(unsigned int*) (rec + 0x160) & 0x10)
			ch_FindWalkableCell(gridContext, *(int*) (obj + 0x34) + 0x4c, rec + 0x144, cell.x, cell.z,
			    &cell.z, &cell.x, 8, *(unsigned int*) (rec + 0x160));
		else
			ch_FindWalkableCell(gridContext, *(int*) (obj + 0x34) + 0x4c,
			    *(int*) (obj + 0x34) + 0x4c, cell.x, cell.z,
			    &cell.z, &cell.x, 8, *(unsigned int*) (rec + 0x160));
		g_14d0c20.cells = (unsigned char*) 0x14cfc20;
		g_14d0c20.max = 0x200;
		if (FindPath((void*) &g_14d0c20, gridContext, v15, v14, cell.z, cell.x,
		    *(unsigned char*) (obj + 0x240)) == -1) {
			*(char*) (*(int*) (rec + 0x14) + 0x110) = 0;
			if (ch_SceneDebugSwitch != 0)
				*(unsigned char*) (*(int*) (rec + 0x14) + 0x8c) |= 8;
			if (*(int*) (rec + 0xf4) != 0) {
				m_FreeTracked((void*) *(int*) (rec + 0xf4));
				*(int*) (rec + 0xf4) = 0;
			}
			fn = (void (__cdecl*) (int)) *(int*) (rec + 0x15c);
			if (fn != 0)
				fn(rec);
			ch_RemoveQueueEntry((char*) rec);
			return 0;
		}
		*(int*) (rec + 0xf4) = (int) m_alloc(g_14d0c20.n * 2,
		    (char*) 0x675ad8);
		*(int*) (rec + 0xf0) = ch_DownsamplePath(obj, (void*) &g_14d0c20,
		    (void*) *(int*) (rec + 0xf4), gridContext);
		*(int*) (rec + 0xf8) = 0;
		*(int*) (rec + 0xfc) = -1;
		d3_GridPointToWorld(gridContext, *(unsigned char*) *(int*) (rec + 0xf4),
		    ((unsigned char*) *(int*) (rec + 0xf4))[1], (float*) (rec + 0x124));
		*(float*) (rec + 0x124) = g_6b5c38[0] + *(float*) (rec + 0x124);
		*(float*) (rec + 0x128) = g_6b5c38[1] + *(float*) (rec + 0x128);
		*(float*) (rec + 0x12c) = g_6b5c38[2] + *(float*) (rec + 0x12c);
		if (*(unsigned char*) (rec + 0x160) & 8) {
			obj = *(int*) (rec + 0x110);
			*(int*) (rec + 0x134) = *(int*) (obj + 0x38);
			*(int*) (rec + 0x138) = *(int*) (obj + 0x3c);
			*(int*) (rec + 0x13c) = *(int*) (obj + 0x40);
		}
		else {
			d3_GridPointToWorld(gridContext, cell.z, cell.x, (float*) (rec + 0x134));
			*(float*) (rec + 0x124) = g_6b5c38[0] + *(float*) (rec + 0x124);
			*(float*) (rec + 0x128) = g_6b5c38[1] + *(float*) (rec + 0x128);
			*(float*) (rec + 0x12c) = g_6b5c38[2] + *(float*) (rec + 0x12c);
			if (*(unsigned char*) (rec + 0x160) & 0x10) {
				if (CompareVector3WithinTolerance((void*) (rec + 0x134), (void*) (rec + 0x144),
					(int) 0x41f00000) == 0) {
					*(int*) (rec + 0x144) = *(int*) (rec + 0x134);
					*(int*) (rec + 0x148) = *(int*) (rec + 0x138);
					*(int*) (rec + 0x14c) = *(int*) (rec + 0x13c);
				}
			}
		}
		*(int*) (rec + 0x104) = 0;
		return 1;
	}
}
