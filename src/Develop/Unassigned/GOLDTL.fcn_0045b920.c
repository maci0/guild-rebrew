


typedef struct S0045b920 {
	float ox;
	float oy;
	float oz;
	int pad0c;
	float sx;
	float sy;
	float sz;
	int pad1c;
	int n;
	int pad24;
	unsigned char* data;
} S0045b920;
// SIZE 0x2c

char __cdecl fcn_0045b920(S0045b920* g, int x, int z, float* out)
{
	if (g != 0 && x >= 0 && x < g->n && z >= 0 && z < g->n) {
		out[0] = x * g->sx + g->ox;
		out[1] = g->data[g->n * z + x] * g->sy + g->oy;
		out[2] = z * g->sz + g->oz;
		return 1;
	}
	return 0;
}
