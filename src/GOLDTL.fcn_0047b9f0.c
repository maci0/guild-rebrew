typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} fcn_0047b9f0_vertex;
// SIZE 0x1c

// FUNCTION: GOLDTL 0x47b9f0

void __cdecl fcn_0047b9f0(fcn_0047b9f0_vertex* v, unsigned char a)
{
	int i;

	for (i = 0; i < 6; i++) {
		v[i].color &= 0xffffff;
		v[i].color |= a << 24;
	}
}
