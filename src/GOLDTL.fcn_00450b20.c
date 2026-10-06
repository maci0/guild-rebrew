extern float g_67bbec;

// SIZE 0x44
typedef struct {
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float power;
} Material;

typedef struct Device Device;

typedef struct {
	char p0[0xa8];
	int (__stdcall* SetMaterial)(Device*, Material*);
} DeviceVtbl;

struct Device {
	DeviceVtbl* vtbl;
};

extern float g_67bbf0;
extern float g_67bbf4;
extern void* g_6b5de0;

// FUNCTION: GOLDTL 0x00450b20

void __cdecl fcn_00450b20(float scale, float* v, unsigned int color, char tint)
{
	Material m;

	m.diffuse[0] = g_67bbec;
	m.diffuse[1] = g_67bbf0;
	m.diffuse[2] = g_67bbf4;
	m.diffuse[3] = scale;
	m.ambient[0] = scale * v[0] * (1.0f / 255.0f);
	m.ambient[1] = scale * v[1] * (1.0f / 255.0f);
	m.ambient[2] = scale * v[2] * (1.0f / 255.0f);
	if (tint) {
		m.diffuse[0] *= scale;
		m.diffuse[1] *= scale;
		m.diffuse[2] *= scale;
	}
	m.ambient[3] = 1.0f;
	m.emissive[0] = (float) ((color >> 16) & 0xff) * scale * (1.0f / 255.0f);
	m.emissive[1] = (float) ((color >> 8) & 0xff) * scale * (1.0f / 255.0f);
	m.emissive[2] = (float) (color & 0xff) * scale * (1.0f / 255.0f);
	m.emissive[3] = 0.0f;
	m.specular[3] = 0.0f;
	m.specular[2] = 0.0f;
	m.specular[1] = 0.0f;
	m.specular[0] = 0.0f;
	m.power = 0.0f;
	((Device*)g_6b5de0)->vtbl->SetMaterial(((Device*)g_6b5de0), &m);
}
