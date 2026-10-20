#include <math.h>

typedef struct {
	float r;
	float g;
	float b;
	float a;
} Color451150;

typedef struct {
	float x;
	float y;
	float z;
} Vec451150;

// SIZE 0x68
typedef struct {
	unsigned int Type;
	Color451150 Diffuse;
	Color451150 Specular;
	Color451150 Ambient;
	Vec451150 Position;
	Vec451150 Direction;
	float Range;
	float Falloff;
	float Attenuation0;
	float Attenuation1;
	float Attenuation2;
	float Theta;
	float Phi;
} Light451150;

typedef struct Device451150 Device451150;

typedef struct {
	char p0[0xb0];
	int (__stdcall* SetLight)(Device451150*, int, Light451150*);
} DeviceVtbl451150;

// SIZE 0x4
struct Device451150 {
	DeviceVtbl451150* vtbl;
};

extern void* g_6b5de0;
extern double g_662d38;
extern float g_662d34;
extern float g_662d30;
extern float g_6628d8;
extern float g_67bbfc;
extern float g_67bc00;
extern float g_67bc04;
extern float g_67bc0c;
extern float g_67bc10;
extern float g_67bc14;
extern float g_67bc1c;
extern float g_67bc20;

void __stdcall fcn_005eb225(Vec451150*, Vec451150*, float*);
void __stdcall fcn_005eb250(Vec451150*, Vec451150*, float*);

/* ADDRESS: GOLDTL 0x00451150 */
char __cdecl fcn_00451150(int index, char* e, float scale, float* m4, float* m7)
{
	Light451150 light;
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
			power *= g_6628d8;
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
		light.Attenuation0 = g_67bc0c * *(float*) (e + 0x98) + g_67bbfc + g_662d30;
		light.Attenuation1 = g_67bc10 * *(float*) (e + 0x98) + g_67bc00 + g_662d30;
		light.Attenuation2 = g_67bc14 * *(float*) (e + 0x98) + g_67bc04 + g_662d30;
	}
	light.Diffuse.r = power * *(float*) (e + 0x5c);
	light.Diffuse.g = power * *(float*) (e + 0x60);
	light.Diffuse.b = power * *(float*) (e + 0x64);
	light.Diffuse.a = 1.0f;
	((Device451150*) g_6b5de0)->vtbl->SetLight(((Device451150*) g_6b5de0), index & 0x7fffffff, &light);
	return 1;
}
