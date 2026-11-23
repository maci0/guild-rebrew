#include "Develop/DieGildeAddOn/game/game_data.h"
#include <string.h>

extern void __cdecl fcn_00443030(void*);
extern void __cdecl fcn_00438b40(int, void*);
extern void __cdecl d3_SetObjectRotation(int, void*);
extern void __cdecl fcn_00439c60(int);
extern void __cdecl fcn_0045b290(int, int);
extern int __cdecl fcn_0045b700(int, int, int);
extern void __cdecl d3_TraverseSceneObjects(int, int, int, int);
extern void __cdecl gv_Free3Fields(int);
extern int __cdecl fcn_00438920(int, int, int);

extern char g_10432c0[];
extern char g_1041d80[];
extern char g_1041d20[];
extern int g_6b8484;
extern int g_1041d0c;
extern int g_67a37c;
extern int g_67a380;
extern float g_67bbdc[3];
extern float g_6b86c4;
extern float g_6b86c8;
extern float g_6b86cc;
extern char* d3_ActiveCamera;

typedef struct {
	char pad0[0x80];
	char* f80;
	char* f84;
	int f88;
	int f8c;
	int f90;
	int f94;
	int f98;
	int f9c;
	int fa0;
	char* fa4;
	char* fa8;
	int fac;
	char padb0[8];
	int fb8;
	float fbc;
	float fc0;
	float fc4;
	float fc8;
	float fcc;
	float fd0;
	int fd4;
	int fd8;
	int fdc;
	char fe0[0x48];
	char f128[0x2a0];
	char pad3c8[4];
	int f3cc;
	int f3d0;
	char pad3d4[4];
	int f3d8;
} SceneCtx4432d0;

#define CTX_TABLE ((SceneCtx4432d0*) g_10432c0)

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x004432d0 */
char __cdecl fcn_004432d0(int contextIndex, char a1)
{
	if (contextIndex >= 0x40)
		return 0;
	if (contextIndex != d3_CurrentContextIndex) {
		CTX_TABLE[d3_CurrentContextIndex].f80 = d3_ObjectListHead;
		CTX_TABLE[d3_CurrentContextIndex].f84 = g_1042538;
		if (CTX_TABLE[d3_CurrentContextIndex].f80 == d3_SceneObjectSentinel
			&& CTX_TABLE[d3_CurrentContextIndex].f84 == d3_SceneObjectSentinel) {
			CTX_TABLE[d3_CurrentContextIndex].f84 = 0;
			CTX_TABLE[d3_CurrentContextIndex].f80 = 0;
		}
		CTX_TABLE[d3_CurrentContextIndex].fa4 = d3_SceneRenderListHead;
		CTX_TABLE[d3_CurrentContextIndex].fa8 = g_1040958;
		if (CTX_TABLE[d3_CurrentContextIndex].fa4 == g_1040640
			&& CTX_TABLE[d3_CurrentContextIndex].fa8 == g_1040640) {
			CTX_TABLE[d3_CurrentContextIndex].fa8 = 0;
			CTX_TABLE[d3_CurrentContextIndex].fa4 = 0;
		}
		CTX_TABLE[d3_CurrentContextIndex].fac = g_6b8300;
		CTX_TABLE[d3_CurrentContextIndex].fb8 = g_6b89c0;
		CTX_TABLE[d3_CurrentContextIndex].f3d8 = g_6b8058;
		CTX_TABLE[d3_CurrentContextIndex].fbc = g_67bbdc[0];
		CTX_TABLE[d3_CurrentContextIndex].fc0 = g_67bbdc[1];
		CTX_TABLE[d3_CurrentContextIndex].fc4 = g_67bbdc[2];
		CTX_TABLE[d3_CurrentContextIndex].fc8 = g_6b86c4;
		CTX_TABLE[d3_CurrentContextIndex].fcc = g_6b86c8;
		CTX_TABLE[d3_CurrentContextIndex].fd0 = g_6b86cc;
		{
			char* cp = CTX_TABLE[d3_CurrentContextIndex].f128;
			int cn = 0x2a0;
			__asm {
				mov edi, cp
				mov esi, offset g_1041d80
				mov ebx, cn
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L58
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L58:
				add ecx, ebx
				rep movsb
			}
		}
		CTX_TABLE[d3_CurrentContextIndex].fd4 = *(int*) 0x6b805c;
		CTX_TABLE[d3_CurrentContextIndex].fd8 = *(int*) 0x10425fc;
		CTX_TABLE[d3_CurrentContextIndex].fdc = *(int*) 0x104329c;
		{
			char* cp = CTX_TABLE[d3_CurrentContextIndex].fe0;
			int cn = 0x48;
			__asm {
				mov edi, cp
				mov esi, offset g_1041d20
				mov ebx, cn
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L65
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L65:
				add ecx, ebx
				rep movsb
			}
		}
		CTX_TABLE[d3_CurrentContextIndex].f3cc = g_67a37c;
		CTX_TABLE[d3_CurrentContextIndex].f3d0 = g_67a380;
		CTX_TABLE[d3_CurrentContextIndex].f88 = g_6b8484;
		if (g_6b8484 != 0) {
			CTX_TABLE[d3_CurrentContextIndex].f8c =
				*(int*) (g_6b8484 + 0x4c);
			CTX_TABLE[d3_CurrentContextIndex].f90 =
				*(int*) (g_6b8484 + 0x50);
			CTX_TABLE[d3_CurrentContextIndex].f94 =
				*(int*) (g_6b8484 + 0x54);
			CTX_TABLE[d3_CurrentContextIndex].f98 =
				*(int*) (g_6b8484 + 0x84);
			CTX_TABLE[d3_CurrentContextIndex].f9c =
				*(int*) (g_6b8484 + 0x88);
			CTX_TABLE[d3_CurrentContextIndex].fa0 =
				*(int*) (g_6b8484 + 0x8c);
		}
		if (CTX_TABLE[contextIndex].f80 == 0)
			fcn_00443030(&CTX_TABLE[contextIndex]);
		d3_ObjectListHead = CTX_TABLE[contextIndex].f80;
		g_1042538 = CTX_TABLE[contextIndex].f84;
		d3_SceneRenderListHead = CTX_TABLE[contextIndex].fa4;
		g_1040958 = CTX_TABLE[contextIndex].fa8;
		g_6b8300 = CTX_TABLE[contextIndex].fac;
		g_6b89c0 = CTX_TABLE[contextIndex].fb8;
		g_67a37c = CTX_TABLE[contextIndex].f3cc;
		g_67a380 = CTX_TABLE[contextIndex].f3d0;
		g_6b8058 = CTX_TABLE[contextIndex].f3d8;
		g_67bbdc[0] = CTX_TABLE[contextIndex].fbc;
		g_67bbdc[1] = CTX_TABLE[contextIndex].fc0;
		g_67bbdc[2] = CTX_TABLE[contextIndex].fc4;
		g_6b86c4 = CTX_TABLE[contextIndex].fc8;
		g_6b86c8 = CTX_TABLE[contextIndex].fcc;
		d3_ActiveCamera = 0;
		g_6b86cc = CTX_TABLE[contextIndex].fd0;
		{
			int cn = 0x48;
			char* cp = CTX_TABLE[contextIndex].fe0;
			__asm {
				mov edi, offset g_1041d20
				mov esi, cp
				mov ebx, cn
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L105
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L105:
				add ecx, ebx
				rep movsb
			}
		}
		{
			char* cp = CTX_TABLE[contextIndex].f128;
			int cn = 0x2a0;
			__asm {
				mov edi, offset g_1041d80
				mov esi, cp
				mov ebx, cn
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L108
				rep movsb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep movsd
			L108:
				add ecx, ebx
				rep movsb
			}
		}
		d3_CurrentContextIndex = contextIndex;
		g_67a370 = (int) &CTX_TABLE[contextIndex];
		if (g_1041d0c == g_6b8484)
			g_1041d0c = CTX_TABLE[contextIndex].f88;
		g_6b8484 = CTX_TABLE[contextIndex].f88;
		if (g_6b8484 != 0) {
			fcn_00438b40(g_6b8484, &CTX_TABLE[contextIndex].f8c);
			d3_SetObjectRotation(g_6b8484, &CTX_TABLE[contextIndex].f98);
			fcn_00439c60(g_6b8484);
		}
		if (a1 == 0) {
			if (g_6b8300 == 0) {
				if (*(int*) 0x6b89e4 != 0) {
					fcn_0045b290(*(int*) 0x6b89e4, 0);
				}
				else {
					*(int*) 0x6b89e4 = fcn_0045b700(0, -*(int*) 0x6b89b0, 1);
					d3_TraverseSceneObjects(g_67a370, 0, 0xc0, 0x456df0);
				}
			}
			else if (*(int*) 0x6b89e4 != 0) {
				gv_Free3Fields(*(int*) 0x6b89e4);
				*(int*) 0x6b89e4 = 0;
			}
			g_1042a08 = 0;
			fcn_00438920(CTX_TABLE[contextIndex].fd8,
				CTX_TABLE[contextIndex].fdc, CTX_TABLE[contextIndex].fd4);
			*(char*) 0x6b859b = 1;
		}
		return 1;
	}
	if (a1 == 0)
		*(char*) 0x6b859b = 1;
	return 1;
}
#pragma optimize("", on)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_10432c0[172];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10432c8[120];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10432c8[120];
#endif
