#include <math.h>

typedef struct {
	float r;
	float g;
	float b;
	float a;
} D3_D3DLIGHT_COLOR;

typedef struct {
	float x;
	float y;
	float z;
} D3_D3DLIGHT_VEC3;

// SIZE 0x68
typedef struct {
	unsigned int Type;
	D3_D3DLIGHT_COLOR Diffuse;
	D3_D3DLIGHT_COLOR Specular;
	D3_D3DLIGHT_COLOR Ambient;
	D3_D3DLIGHT_VEC3 Position;
	D3_D3DLIGHT_VEC3 Direction;
	float Range;
	float Falloff;
	float Attenuation0;
	float Attenuation1;
	float Attenuation2;
	float Theta;
	float Phi;
} D3_D3DLIGHT8;

#include "Develop/Units/d8_vesa/d3d_device_view.h"
typedef int (__stdcall* D3D8_SET_LIGHT_FN)(D3D_DEVICE_VIEW*, int, D3_D3DLIGHT8*);












extern double g_662d38;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_662d30;
extern float g_67bbfc;
extern float g_67bc00;
extern float g_67bc04;
extern float g_67bc0c;
extern float g_67bc10;
extern float g_67bc14;
extern float g_67bc1c;
extern float g_67bc20;

void __stdcall fcn_005eb225(D3_D3DLIGHT_VEC3*, D3_D3DLIGHT_VEC3*, float*);
void __stdcall fcn_005eb250(D3_D3DLIGHT_VEC3*, D3_D3DLIGHT_VEC3*, float*);

/* ADDRESS: GOLDTL 0x00451150 */
char __cdecl d3_SetupD3DLight(int index, char* e, float scale, float* m4, float* m7)
{
	D3_D3DLIGHT8 light;
	float power;

	light.Ambient.b = 0.0f;
	light.Ambient.g = 0.0f;
	light.Ambient.r = 0.0f;
	light.Ambient.a = 1.0f;
	if (*(int*) (e + 0x218) == 7) {
		light.Type = 3;
		light.Direction.x = *(float*) (e + 0x1d8);
		light.Direction.y = *(float*) (e + 0x1dc);
		light.Direction.z = *(float*) (e + 0x1e0);
		if (m7 != 0) {
			fcn_005eb250(&light.Direction, &light.Direction, m7);
		}
		light.Range = (float) sqrt(g_662d38);
		power = g_67bc1c * *(float*) (e + 0x94) * scale;
		if (index & 0x80000000) {
			light.Ambient.r = (power * *(float*) (e + 0x5c)) * g_662d34;
			light.Ambient.g = (power * *(float*) (e + 0x60)) * g_662d34;
			light.Ambient.b = (power * *(float*) (e + 0x64)) * g_662d34;
			power *= 0.4f;
		}
	} else {
		light.Type = 1;
		light.Position.x = *(float*) (e + 0x1d8);
		light.Position.y = *(float*) (e + 0x1dc);
		light.Position.z = *(float*) (e + 0x1e0);
		if (m4 != 0) {
			fcn_005eb225(&light.Position, &light.Position, m4);
		}
		light.Range = *(float*) (e + 0x90);
		if (*(void**) (e + 0x1e8) != 0) {
			power = *(float*) (*(char**) (e + 0x1e8) + 0x1a0) * *(float*) (e + 0x94) * g_67bc20;
		} else {
			power = g_67bc20 * *(float*) (e + 0x94);
		}
		power *= scale;
		light.Attenuation0 = g_67bc0c * *(float*) (e + 0x98) + g_662d30 + g_67bbfc;
		light.Attenuation1 = g_67bc10 * *(float*) (e + 0x98) + g_67bc00 + g_662d30;
		light.Attenuation2 = g_67bc14 * *(float*) (e + 0x98) + g_67bc04 + g_662d30;
	}
	light.Diffuse.r = power * *(float*) (e + 0x5c);
	light.Diffuse.g = power * *(float*) (e + 0x60);
	light.Diffuse.b = power * *(float*) (e + 0x64);
	light.Diffuse.a = 1.0f;
	((D3D8_SET_LIGHT_FN) ((D3D_DEVICE_VIEW*)g_6b5de0)->vtbl->unk_98[6])(((D3D_DEVICE_VIEW*)g_6b5de0), index & 0x7fffffff, &light);
	return 1;
}
