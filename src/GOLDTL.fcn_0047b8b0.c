typedef struct Vtx {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} Vtx;
// SIZE 0x1c

// FUNCTION: GOLDTL 0x47b8b0
// SIZE: 227
int __cdecl fcn_0047b8b0(int x, int y, int w, int h, Vtx* v)
{
	v[0].x = (x - 0.5f);
	v[0].y = (y - 0.5f);
	v[0].z = 0.0f;
	v[0].rhw = 1.0f;
	v[0].color = 0xffffffff;
	v[0].u = 0.0f;
	v[0].v = 0.0f;
	v[1].x = (w + (x - 0.5f));
	v[1].y = (y - 0.5f);
	v[1].z = 0.0f;
	v[1].rhw = 1.0f;
	v[1].color = 0xffffffff;
	v[1].u = 1.0f;
	v[1].v = 0.0f;
	v[2].x = (x - 0.5f);
	v[2].y = (h + (y - 0.5f));
	v[2].z = 0.0f;
	v[2].rhw = 1.0f;
	v[2].color = 0xffffffff;
	v[2].u = 0.0f;
	v[2].v = 1.0f;
	v[3].x = (w + (x - 0.5f));
	v[3].y = (y - 0.5f);
	v[3].z = 0.0f;
	v[3].rhw = 1.0f;
	v[3].color = 0xffffffff;
	v[3].u = 1.0f;
	v[3].v = 0.0f;
	v[4].x = (w + (x - 0.5f));
	v[4].y = (h + (y - 0.5f));
	v[4].z = 0.0f;
	v[4].rhw = 1.0f;
	v[4].color = 0xffffffff;
	v[4].u = 1.0f;
	v[4].v = 1.0f;
	v[5].x = (x - 0.5f);
	v[5].y = (h + (y - 0.5f));
	v[5].z = 0.0f;
	v[5].rhw = 1.0f;
	v[5].color = 0xffffffff;
	v[5].u = 0.0f;
	v[5].v = 1.0f;
	return 1;
}
