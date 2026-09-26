// FUNCTION: GOLDTL 0x00454c90
// SIZE: 743

typedef struct Box {
	char pad0[0x10];
	float min[3];
	float pad1c;
	float max[3];
} Box;

typedef struct Corner {
	float x;
	float y;
	float z;
	char padc[0x50 - 0xc];
} Corner;
// SIZE 0x50

extern Corner g_6b8720[8];

Corner* __cdecl fcn_00454c90(Box* b, float* o, float* m)
{
	float x0;
	float y0;
	float z0;
	float d[4];

	x0 = b->min[0] - o[0];
	y0 = b->min[1] - o[1];
	z0 = b->min[2] - o[2];
	d[0] = b->max[0] - o[0];
	d[1] = b->max[1] - o[1];
	d[2] = b->max[2] - o[2];
	g_6b8720[0].x = x0 * m[0] + y0 * m[4] + z0 * m[8] + m[12];
	g_6b8720[0].y = x0 * m[1] + y0 * m[5] + z0 * m[9] + m[13];
	g_6b8720[0].z = x0 * m[2] + y0 * m[6] + z0 * m[10] + m[14];
	g_6b8720[1].x = d[0] * m[0] + y0 * m[4] + z0 * m[8];
	g_6b8720[1].y = d[0] * m[1] + y0 * m[5] + z0 * m[9];
	g_6b8720[1].z = d[0] * m[2] + y0 * m[6] + z0 * m[10];
	g_6b8720[2].x = x0 * m[0] + d[1] * m[4] + z0 * m[8];
	g_6b8720[2].y = x0 * m[1] + d[1] * m[5] + z0 * m[9];
	g_6b8720[2].z = x0 * m[2] + d[1] * m[6] + z0 * m[10];
	g_6b8720[3].x = d[0] * m[0] + d[1] * m[4] + z0 * m[8];
	g_6b8720[3].y = d[0] * m[1] + d[1] * m[5] + z0 * m[9];
	g_6b8720[3].z = d[0] * m[2] + d[1] * m[6] + z0 * m[10];
	g_6b8720[4].x = x0 * m[0] + y0 * m[4] + d[2] * m[8];
	g_6b8720[4].y = x0 * m[1] + y0 * m[5] + d[2] * m[9];
	g_6b8720[4].z = x0 * m[2] + y0 * m[6] + d[2] * m[10];
	g_6b8720[5].x = d[0] * m[0] + y0 * m[4] + d[2] * m[8];
	g_6b8720[5].y = d[0] * m[1] + y0 * m[5] + d[2] * m[9];
	g_6b8720[5].z = d[0] * m[2] + y0 * m[6] + d[2] * m[10];
	g_6b8720[6].x = x0 * m[0] + d[1] * m[4] + d[2] * m[8];
	g_6b8720[6].y = x0 * m[1] + d[1] * m[5] + d[2] * m[9];
	g_6b8720[6].z = x0 * m[2] + d[1] * m[6] + d[2] * m[10];
	g_6b8720[7].x = d[0] * m[0] + d[1] * m[4] + d[2] * m[8];
	g_6b8720[7].y = d[0] * m[1] + d[1] * m[5] + d[2] * m[9];
	g_6b8720[7].z = d[0] * m[2] + d[1] * m[6] + d[2] * m[10];
	return g_6b8720;
}
