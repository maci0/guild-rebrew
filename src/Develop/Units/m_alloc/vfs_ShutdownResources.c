extern char d2_WindowActiveView[];
extern char g_102ce50[];
#include <stdio.h>

typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern char* d2_FileObjTable;
extern int g_772508;
extern int d2_ScreenSurface;
extern int d2_CurrentFontBank;
extern int d2_BlackTexture;
extern int d2_ZOrderStack;
extern FILE* g_772564;
#include "Develop/Units/d2.v1/d2_surface.h"
extern int d2_DirtyRectBuffers;
extern int d2_RedrawInfo1;
extern int d2_RedrawInfo2;
extern int d2_DirtyRects;
extern int d2_ExcludedShapeNames;
extern int d2_Controls;
extern int d3_LastReleaseRefCount;

void __cdecl d2_FreeAllSprites(void);
void __cdecl d2_CloseWindow(int a1);
void __cdecl d2_DestroyElement(int id);
void __cdecl d2_FreeAnimTrackList(void* p);
void __cdecl m_FreeTracked(void* p);
void __cdecl d2_ReleaseSurface(void* o);
void __cdecl fcn_00477550(void);
void __cdecl d3_SafeReleaseSceneResource(int a1);
void __cdecl d2_DestroyQuadVertexBuffer(void);
void __cdecl d2_ReleaseRenderToSurface(void);

/* Shuts the resource system down: drops the animation tracks, every entry of
 * the file table, the open archive handles and the tracked allocations. */
/* ADDRESS: GOLDTL 0x00465c60 */
/* ADDRESS: GOLDDE 0x00459890 */
void __cdecl vfs_ShutdownResources(void)
{
	int* track;

	int i;
	int off;
	VfsEntry* entry;
	void* object;

	d2_FreeAllSprites();
	i = 0;
	track = (int*) &d2_WindowActiveView;
	do {
		if (*track == 1) {
			d2_CloseWindow(i);
		}
		track = (int*) ((char*) track + 0x3cc);
		i++;
	} while ((int) track < (int) &g_102ce50);
	i = 0;
	do {
		d2_DestroyElement(i);
		i++;
	} while (i < 0x3ff);
	for (i = 0; i < 0x800; i++) {
		entry = (VfsEntry*) (d2_FileObjTable + i * 0x54);
		if (entry->data != 0 && entry->size != 0) {
			if (entry->kind < 0x10) {
				d2_FreeAnimTrackList(entry->data);
			} else {
				m_FreeTracked(entry->data);
				entry->data = 0;
			}
			g_772508 -= entry->size;
			entry->data = 0;
		}
	}
	if (d2_ScreenSurface != 0) {
		object = *(void**) (d2_ScreenSurface + 0x24);
		d3_LastReleaseRefCount = (*(int (__stdcall**) (void*)) (*(int*) object + 8))(object);
		*(int*) (d2_ScreenSurface + 0x24) = 0;
		d2_ReleaseSurface((void*) d2_ScreenSurface);
		d2_ScreenSurface = 0;
	}
	if (d2_WhiteSurface != 0) {
		d2_ReleaseSurface(d2_WhiteSurface);
		d2_WhiteSurface = 0;
	}
	fcn_00477550();
	if (d2_BlackTexture != 0) {
		d3_SafeReleaseSceneResource(d2_BlackTexture);
		d2_BlackTexture = 0;
	}
	if (g_772564 != 0) {
		fclose(g_772564);
	}
	d2_CurrentFontBank = 0;
	g_772564 = 0;
	if (d2_ZOrderStack != 0) {
		m_FreeTracked((void*) d2_ZOrderStack);
		d2_ZOrderStack = 0;
	}
	if (d2_Controls != 0) {
		m_FreeTracked((void*) d2_Controls);
		d2_Controls = 0;
	}
	if (d2_FileObjTable != 0) {
		m_FreeTracked(d2_FileObjTable);
		d2_FileObjTable = 0;
	}
	if (d2_DirtyRectBuffers != 0) {
		m_FreeTracked((void*) d2_DirtyRectBuffers);
		d2_DirtyRectBuffers = 0;
	}
	if (d2_RedrawInfo1 != 0) {
		m_FreeTracked((void*) d2_RedrawInfo1);
		d2_RedrawInfo1 = 0;
	}
	if (d2_RedrawInfo2 != 0) {
		m_FreeTracked((void*) d2_RedrawInfo2);
		d2_RedrawInfo2 = 0;
	}
	if (d2_DirtyRects != 0) {
		m_FreeTracked((void*) d2_DirtyRects);
		d2_DirtyRects = 0;
	}
	if (d2_ExcludedShapeNames != 0) {
		m_FreeTracked((void*) d2_ExcludedShapeNames);
		d2_ExcludedShapeNames = 0;
	}
	d2_DestroyQuadVertexBuffer();
	d2_ReleaseRenderToSurface();
}
