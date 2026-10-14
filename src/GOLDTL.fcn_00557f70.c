struct rgba_00557f70;


// SIZE 0x4
struct rgba_00557f70 {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void __cdecl fcn_00417180(int, char*, int, struct rgba_00557f70, float*, int, int, float, float,
                          float, float, float);

/* ADDRESS: GOLD 0x0054fec0 */
/* ADDRESS: GOLDTL 0x00557f70 */

void __cdecl fcn_00557f70(char* o)
{
	struct rgba_00557f70 c;
	float v[4];

	c.b = 0x50;
	c.g = 0x1e;
	c.r = 0x32;
	v[0] = 0.0f;
	v[1] = 50.0f;
	v[2] = 0.0f;
	fcn_00417180(*(int*) (o + 0x61), "punkte_nm_2", 1, c, v, 0x12c, 1, 50.0f, 1.0f, 2.0f, 0.5f, 0.5f);
}
