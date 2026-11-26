#include "client_types.h"
typedef Slot_1043340 Slot_4392c0;
// SIZE 0x3dc

typedef void (__cdecl* node_fn_4392c0)(char* node);

extern char g_6b8018;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern Slot_1043340 g_1043340[64];
extern int g_6b8484;
extern int g_6b8300;
extern int g_67a370;

void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl d3_DisposeObject(char* p);
void __cdecl fcn_00452420(char* p);
void __cdecl fcn_0043bcf0(int a);
void __cdecl fcn_00459b40(int a);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_00452300(void);
void __cdecl d3_InitRenderVertexBuffer(void);
#include "Develop/Units/d3/d3_animation.h"
void __cdecl fcn_0045c110(void);

/* ADDRESS: GOLDTL 0x004392c0 */
void __cdecl fcn_004392c0(void)
{
	int saved;
	int i;

	if (g_6b8018 == 0) {
		return;
	}
	saved = d3_CurrentContextIndex;
	for (i = 0; i < 64; i++) {
		if (i != saved && g_1043340[i].used != 0) {
			d3_SelectSceneContext(i, 1);
			while (d3_ObjectListHead != d3_SceneObjectSentinel) {
				d3_DisposeObject(d3_ObjectListHead);
			}
			g_6b8484 = 0;
			while (d3_SceneRenderListHead != g_1040640) {
				fcn_00452420(d3_SceneRenderListHead);
			}
			if (g_6b8300 != 0) {
				fcn_0043bcf0(g_6b8300);
				g_6b8300 = 0;
			}
			if (g_6b89c0 != 0) {
				fcn_00459b40(g_6b89c0);
				g_6b89c0 = 0;
			}
			if (*(void**) (((char*)g_67a370) + 0x3c8) != 0) {
				m_FreeTracked(*(void**) (((char*)g_67a370) + 0x3c8));
				*(void**) (((char*)g_67a370) + 0x3c8) = 0;
			}
		}
	}
	if (saved != d3_CurrentContextIndex) {
		d3_SelectSceneContext(saved, 1);
	}
	while (d3_ObjectListHead != d3_SceneObjectSentinel) {
		d3_DisposeObject(d3_ObjectListHead);
	}
	if (g_6b8300 != 0) {
		fcn_0043bcf0(g_6b8300);
		g_6b8300 = 0;
	}
	if (g_6b89c0 != 0) {
		fcn_00459b40(g_6b89c0);
		g_6b89c0 = 0;
	}
	if (*(void**) (((char*)g_67a370) + 0x3c8) != 0) {
		m_FreeTracked(*(void**) (((char*)g_67a370) + 0x3c8));
		*(void**) (((char*)g_67a370) + 0x3c8) = 0;
	}
	fcn_00452300();
	d3_InitRenderVertexBuffer();
	while (g_1042c38 != g_1042d00) {
		(*(node_fn_4392c0*) (g_1042c38 + 0x1ec))(g_1042c38);
	}
	while (g_1042320 != g_1052a40) {
		d3_ReleaseAnim(g_1042320, 1);
	}
	fcn_0045c110();
}
