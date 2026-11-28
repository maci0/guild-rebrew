typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} fcn_0047b9a0_vertex;
// SIZE 0x1c


/* ADDRESS: GOLDTL 0x0047b9a0 */
/* ADDRESS: GOLDDE 0x0046a990 */
void __cdecl d2_SetQuadVertexColor(fcn_0047b9a0_vertex* v, unsigned char r, unsigned char g, unsigned char b)
{
	int i;

	for (i = 0; i < 6; i++)
		v[i].color = 0xff000000 | (r << 16) | (g << 8) | b;
}
