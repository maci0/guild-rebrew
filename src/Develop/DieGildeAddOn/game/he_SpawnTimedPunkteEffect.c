struct EFFECT_RGBA;


// SIZE 0x4
struct EFFECT_RGBA {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void __cdecl d3_CreateObjectParticleEffect(int, char*, int, struct EFFECT_RGBA, float*, int, int, float, float,
                          float, float, float);


/* ADDRESS: GOLDTL 0x00557f70 */
/* ADDRESS: GOLDDE 0x0053e2d0 */
void __cdecl he_SpawnTimedPunkteEffect(char* o)
{
	struct EFFECT_RGBA c;
	float v[4];

	c.b = 0x50;
	c.g = 0x1e;
	c.r = 0x32;
	v[0] = 0.0f;
	v[1] = 50.0f;
	v[2] = 0.0f;
	d3_CreateObjectParticleEffect(*(int*) (o + 0x61), "punkte_nm_2", 1, c, v, 0x12c, 1, 50.0f, 1.0f, 2.0f, 0.5f, 0.5f);
}
