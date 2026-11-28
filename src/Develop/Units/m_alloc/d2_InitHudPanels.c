

#include <string.h>

// SIZE 0x5c
typedef struct {
	int flags;
	int width;
	int height;
	char padc[0x1c];
	int format;
	char pad2c[0x30];
} SurfaceDesc;

// SIZE 0xc
typedef struct {
	int handle;
	int width;
	int height;
} Surface;

// SIZE 0x10
typedef struct {
	int left;
	int top;
	int right;
	int bottom;
} Rect;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int visible;
	char pad60[0x2f4 - 0x60];
} Control;

extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_6a25a8;
extern int d2_HudTopBarWindowId;
extern int g_14ce860;
extern int g_14ce864;
extern int g_774674;
extern int g_774678;
extern int g_77467c;
extern unsigned char g_77534c;
extern int g_6a24d8[];
extern int g_7ea380[15];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int tp_d2_GroundplanSurface;
#include "Develop/Units/d2.v1/d2_gui.h"

void __cdecl d2_SetClipRect(int, int, int, int);
int __cdecl d2_AllocHudRectSlot(int, int, int, int, int);
int __cdecl d2_CreateWindow(int, int, int, int, int);
void __cdecl d2_CenterWindow(int, unsigned char);
char* __cdecl d2_LoadObj(char*, int);
Surface* __cdecl d2_CreateSurface(SurfaceDesc*, int);
int __cdecl d2_LockSurface(Surface*);
void __cdecl d2_DrawShapeToArgbSurface(int, int, char*, Surface*);
void __cdecl d2_UnlockSurface(Surface*);
int __cdecl d2_CreateTiledSurface(int, int, int, int, Surface*, int);
void __cdecl d2_ReleaseSurface(Surface*);
void __cdecl m_FreeTracked(char*);
void __cdecl d2_ClearSurface(Surface*);
int __cdecl d2_CreateElement(int, int, int);
void __cdecl d2_SetSlotVisibility(int, int);

/* ADDRESS: GOLDDE 0x00510060 */
void __cdecl d2_InitHudPanels(char* name)
{
	SurfaceDesc desc2;
	SurfaceDesc desc;
	int n;
	SurfaceDesc* p;
	char* data;
	Surface* s;

	d2_SetClipRect(0, 0, g_1040494, d2_ScreenHeight);
	g_6a25a8 = d2_AllocHudRectSlot(g_1040494 - 0x50, 0x11, 0x30, 0x30, 0);
	d2_HudTopBarWindowId = d2_CreateWindow(4, 0xa, 0x288, 0x30, 0);
	d2_CenterWindow(d2_HudTopBarWindowId, 1);
	data = d2_LoadObj(name, 0);
	n = sizeof(desc);
	p = &desc;
	/*
	 * The reference zero-fills with the hand-written block-fill prelude no
	 * msvc6 C spelling emits (archived docs/codegen-walls.md 6b).
	 */
	__asm {
		mov edi, p
		mov ebx, n
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
	desc.width = g_14ce860;
	desc.height = g_14ce864;
	desc.format = 0x15;
	s = d2_CreateSurface(&desc, 0x20);
	if (s != 0) {
		if (d2_LockSurface(s) != 0) {
			d2_DrawShapeToArgbSurface(0, 0, data + *(int*) (data + 0x45), s);
			d2_UnlockSurface(s);
		}
		g_774674 = d2_CreateTiledSurface(s->width - 0x80, 0, 0x80, s->height - 0x80, s, 0);
		g_774678 = d2_CreateTiledSurface(s->width - 0x100, s->height - 0x80, 0x100, 0x80, s, 0);
		g_77467c = d2_CreateTiledSurface(g_6a24d8[g_77534c], 0, 0x288, 0x40, s, 0);
		d2_ReleaseSurface(s);
	}
	m_FreeTracked(data);
	memset(g_7ea380, 0xff, sizeof(g_7ea380));
	(*(char**)&g_6a25ac) = name;
	((Rect*)&g_1040480)->right = ((Rect*)&g_6a3764)->right;
	((Rect*)&g_1040480)->left = ((Rect*)&g_6a3764)->left;
	((Rect*)&g_1040480)->top = ((Rect*)&g_6a3764)->top;
	((Rect*)&g_1040480)->bottom = ((Rect*)&g_6a3764)->bottom;
	memset(&desc2, 0, sizeof(desc2));
	desc2.width = 0x68;
	desc2.height = 0x6e;
	desc2.format = 0x15;
	(*(Surface**)&tp_d2_GroundplanSurface) = d2_CreateSurface(&desc2, 3);
	d2_ClearSurface((*(Surface**)&tp_d2_GroundplanSurface));
	g_6a25fc = d2_CreateElement(0x286, 0x23c, 0x544);
	((D2_CONTROL_TL*)d2_Controls)[g_6a25fc].value_05c = 1;
	d2_SetSlotVisibility(g_6a25fc, 0);
}
