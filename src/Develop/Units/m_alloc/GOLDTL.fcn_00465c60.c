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

extern char* g_772500;
extern int g_772508;
extern int g_77250c;
extern int g_772524;
extern int g_77253c;
extern int g_772540;
extern FILE* g_772564;
#include "Develop/Units/d2.v1/d2_surface.h"
extern int g_77257c;
extern int g_772580;
extern int g_772584;
extern int g_772588;
extern int g_7725ac;
extern int g_1015ea0;
extern int g_14ce728;

void __cdecl d2_FreeAllSprites(void);
void __cdecl d2_CloseWindow(int a1);
void __cdecl d2_DestroyElement(int id);
void __cdecl fcn_0047b5d0(void* p);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_00475f80(void* o);
void __cdecl fcn_00477550(void);
void __cdecl fcn_0047ce50(int a1);
void __cdecl fcn_0047c4b0(void);
void __cdecl d2_ReleaseRenderToSurface(void);

/* Shuts the resource system down: drops the animation tracks, every entry of
 * the file table, the open archive handles and the tracked allocations. */
/* ADDRESS: GOLDTL 0x00465c60 */
void __cdecl fcn_00465c60(void)
{
	int* track;

	int i;
	int off;
	VfsEntry* entry;
	void* object;

	d2_FreeAllSprites();
	i = 0;
	track = (int*) 0x10161d0;
	do {
		if (*track == 1) {
			d2_CloseWindow(i);
		}
		track = (int*) ((char*) track + 0x3cc);
		i++;
	} while ((int) track < 0x102ce50);
	i = 0;
	do {
		d2_DestroyElement(i);
		i++;
	} while (i < 0x3ff);
	for (i = 0; i < 0x800; i++) {
		entry = (VfsEntry*) (g_772500 + i * 0x54);
		if (entry->data != 0 && entry->size != 0) {
			if (entry->kind < 0x10) {
				fcn_0047b5d0(entry->data);
			} else {
				m_FreeTracked(entry->data);
				entry->data = 0;
			}
			g_772508 -= entry->size;
			entry->data = 0;
		}
	}
	if (g_77250c != 0) {
		object = *(void**) (g_77250c + 0x24);
		g_14ce728 = (*(int (__stdcall**) (void*)) (*(int*) object + 8))(object);
		*(int*) (g_77250c + 0x24) = 0;
		fcn_00475f80((void*) g_77250c);
		g_77250c = 0;
	}
	if (g_77256c != 0) {
		fcn_00475f80(g_77256c);
		g_77256c = 0;
	}
	fcn_00477550();
	if (g_77253c != 0) {
		fcn_0047ce50(g_77253c);
		g_77253c = 0;
	}
	if (g_772564 != 0) {
		fclose(g_772564);
	}
	g_772524 = 0;
	g_772564 = 0;
	if (g_772540 != 0) {
		m_FreeTracked((void*) g_772540);
		g_772540 = 0;
	}
	if (g_1015ea0 != 0) {
		m_FreeTracked((void*) g_1015ea0);
		g_1015ea0 = 0;
	}
	if (g_772500 != 0) {
		m_FreeTracked(g_772500);
		g_772500 = 0;
	}
	if (g_77257c != 0) {
		m_FreeTracked((void*) g_77257c);
		g_77257c = 0;
	}
	if (g_772580 != 0) {
		m_FreeTracked((void*) g_772580);
		g_772580 = 0;
	}
	if (g_772584 != 0) {
		m_FreeTracked((void*) g_772584);
		g_772584 = 0;
	}
	if (g_772588 != 0) {
		m_FreeTracked((void*) g_772588);
		g_772588 = 0;
	}
	if (g_7725ac != 0) {
		m_FreeTracked((void*) g_7725ac);
		g_7725ac = 0;
	}
	fcn_0047c4b0();
	d2_ReleaseRenderToSurface();
}
