struct RGBA_COLOR;


// SIZE 0x4
struct RGBA_COLOR {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void __cdecl d3_CreateObjectParticleEffect(int, char*, int, struct RGBA_COLOR, float*, int, int, float, float,
                          float, float, float);


/* ADDRESS: GOLDTL 0x00557f00 */
void __cdecl he_SpawnTimedRauchEffect(char* o)
{
	struct RGBA_COLOR c;
	float v[4];

	c.b = 0xa0;
	c.g = 0xff;
	c.r = 0x64;
	v[0] = 0.0f;
	v[1] = 200.0f;
	v[2] = 0.0f;
	d3_CreateObjectParticleEffect(*(int*) (o + 0x61), "Rauch", 1, c, v, 0x12c, 1, 30.0f, 2.0f, 7.5f, 0.4f, 1.0f);
}
