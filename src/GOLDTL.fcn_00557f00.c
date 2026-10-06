struct rgba_00557f00;


// SIZE 0x4
struct rgba_00557f00 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void __cdecl fcn_00417180(int, char*, int, struct rgba_00557f00, float*, int, int, float, float,
                          float, float, float);

// FUNCTION: GOLD 0x0054fe50
// FUNCTION: GOLDTL 0x557f00

void __cdecl fcn_00557f00(char* o)
{
	struct rgba_00557f00 c;
	float v[4];

	c.b = 0xa0;
	c.g = 0xff;
	c.r = 0x64;
	v[0] = 0.0f;
	v[1] = 200.0f;
	v[2] = 0.0f;
	fcn_00417180(*(int*) (o + 0x61), "Rauch", 1, c, v, 0x12c, 1, 30.0f, 2.0f, 7.5f, 0.4f, 1.0f);
}
