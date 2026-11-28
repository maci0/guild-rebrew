double __cdecl atan2(double, double);
#pragma intrinsic(atan2)

typedef struct
{
	unsigned int w;
	unsigned int h;
	char pad8[0x18 - 8];
	int a18;
	int a1c;
	char pad20[0x28 - 0x20];
	unsigned char b28;
	char pad29[0x30 - 0x29];
	unsigned char b30;
	char pad31[3];
	unsigned char b34;
	char pad35[3];
	int bpp;
	float x;
	float y;
	float cw;
	float ch;
	int f4c;
	int f50;
	int f54;
} D3_INIT_CONFIG;
// SIZE 0x58

extern D3_INIT_CONFIG g_10529e0;
extern char g_6b8004;
extern char g_1042fc4;
extern char g_1042fc5;
extern unsigned char g_1042557;
extern unsigned char g_1043277;
extern int g_1042fc0;
extern char g_1043060;
extern unsigned int g_14ce7e0;
#include "Develop/Units/d3/d3_camera.h"
extern int g_1042ef8;
extern int g_1042c3c;
extern char* g_1042efc;
extern char g_1042a40[];
extern int g_1052ba0;
extern int g_1042324;
extern char* g_1052ba4;
extern char g_10421c0[];
extern int g_67a374;
extern unsigned char g_6b7ff8;
extern char g_6b8018;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_1052bbc;
extern float d3_ProjectionDist;
extern float g_1052bc4;
extern float g_1052bb4;
extern float g_1052bb8;
extern char d3_Universes[];

void __cdecl d3_InitSceneObject(char* o);
void __cdecl d3_InitLightBuffers(int nlist, int nactive);
void __cdecl d3_InitTextures(unsigned int n, int a2);
void __cdecl d3_ResetRenderStates(int* a);
void __cdecl d3_SetFogEnabled(char on);
void __cdecl fcn_0043bc00(char a, char b);
void __cdecl d3_SelectShadowTextureFormat(int, int, int, int, int, int, int);
void __cdecl InitColorTable(void);
void __cdecl d3_SetViewport(float, float, float, float, int, int, int, unsigned int, unsigned int);
void __cdecl d3_InitRenderVertexBuffer(void);

/* ADDRESS: GOLDTL 0x00439020 */
/* ADDRESS: GOLDDE 0x00432100 */
char __cdecl d3_Init(D3_INIT_CONFIG* cfg)
{
	unsigned int n;

	g_6b8004 = 0;
	{
		int len;

		len = 0x58;
		__asm {
			mov edi, offset g_10529e0
			mov esi, cfg
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	if (g_10529e0.cw + g_10529e0.x > g_10529e0.w)
		g_10529e0.x = g_10529e0.w - g_10529e0.cw;
	if (g_10529e0.ch + g_10529e0.y > g_10529e0.h)
		g_10529e0.y = g_10529e0.h - g_10529e0.ch;
	g_1042fc4 = 0;
	g_1042fc5 = 0;
	d3_RenderedFaceCount = 0;
	g_1042fc0 = 6;
	g_1042557 |= 2;
	g_1043277 |= 2;
	d3_InitSceneObject(((char*)&g_1043060));
	d3_InitSceneObject(d3_SceneObjectSentinel);
	n = g_14ce7e0;
	d3_ObjectListHead = d3_SceneObjectSentinel;
	g_1042538 = ((char*)&g_1043060);
	d3_ActiveCamera = 0;
	g_1042c38 = g_1042d00;
	g_1042ef8 = 0;
	g_1042c3c = 0;
	g_1042efc = g_1042a40;
	g_1052ba0 = 0;
	g_1042324 = 0;
	g_1042320 = g_1052a40;
	g_1052ba4 = g_10421c0;
	g_1041d08 = 0;
	if (n > 8)
		n = 8;
	d3_InitLightBuffers(0x200, n);
	g_6b8008 = 0;
	d3_InitTextures(g_10529e0.a18, g_10529e0.a1c);
	d3_ResetRenderStates(&g_67a374);
	d3_SetFogEnabled(1);
	d3_FogColor = 0;
	g_6b7ff8 = g_10529e0.b34;
	fcn_0043bc00(g_10529e0.b30, g_10529e0.b28);
	d3_SelectShadowTextureFormat(g_10529e0.bpp, 0x80, 0x100, 0x20, 0, 1, 0x20);
	InitColorTable();
	g_6b8018 = 1;
	d3_SetViewport(g_10529e0.x, g_10529e0.y, g_10529e0.cw, g_10529e0.ch, g_10529e0.f4c, g_10529e0.f50, g_10529e0.f54, g_10529e0.w, g_10529e0.h);
	d3_CurrentContextIndex = 0;
	g_1052bc4 = (float) atan2(g_1052bbc, d3_ProjectionDist);
	g_1052bb8 = (float) atan2(g_1052bb4, d3_ProjectionScaleY);
	{
		int len;

		len = 0xf700;
		__asm {
			mov edi, offset d3_Universes
			mov ebx, len
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
	d3_InitRenderVertexBuffer();
	return 1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_1042a08[2204];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_1042a30[16];
unsigned char _dpad_1042a44[500];
unsigned char _dpad_1042c40[164];
unsigned char _dpad_1042cec[20];
unsigned char _dpad_1042d04[500];
unsigned char _dpad_1042f00[164];
unsigned char _dpad_1042fa8[24];
unsigned char _dpad_1043028[8];
unsigned char _dpad_1043034[12];
unsigned char _dpad_1043044[28];
unsigned char _dpad_1043064[496];
unsigned char _dpad_1043258[31];
unsigned char _dpad_104327b[13];
#endif
