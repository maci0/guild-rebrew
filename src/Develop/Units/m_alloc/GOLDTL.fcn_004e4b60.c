// SIZE 0x4
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} D3_SKY_COLOR;

extern int g_772f3c;
extern int g_772f68;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_772f64;

int __cdecl d3_CreateSky(float a, float b, float c);
int __cdecl d3_CreateSkyLayer(int h, int a, int b, D3_SKY_COLOR c, float d, int e, float f, float g);
void __cdecl d3_SetSkyLayerScrollSpeed(int h, int s, int a);
void __cdecl d3_SetSkyLayerTransition(int h, int s, int a, float b);

/* ADDRESS: GOLDTL 0x004e4b60 */
void __cdecl d3_InitSkyLayer(int textureName)
{
	D3_SKY_COLOR c;

	if (g_772f3c == 0) {
		g_6b89c0 = g_772f68 = d3_CreateSky(-2.25f, -0.2f, 600.0f);
		*(int*) &c = 0;
		c.b = 0;
		g_772f64 = d3_CreateSkyLayer(g_772f68, 0, textureName, c, 3.0f, 0, 0.8f, -0.25f);
		d3_SetSkyLayerScrollSpeed(g_772f68, g_772f64, 0);
		d3_SetSkyLayerTransition(g_772f68, g_772f64, 0xff, 10.0f);
	}
}
