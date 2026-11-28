typedef struct {
	float x;
	float y;
	float z;
	float rhw;
	unsigned int color;
	float u;
	float v;
} D2_QUAD_VERTEX;
// SIZE 0x1c


/* ADDRESS: GOLDTL 0x0047b9f0 */
/* ADDRESS: GOLDDE 0x0046a9e0 */
void __cdecl d2_SetQuadAlpha(D2_QUAD_VERTEX* verts, unsigned char alpha)
{
	int i;

	for (i = 0; i < 6; i++) {
		verts[i].color &= 0xffffff;
		verts[i].color |= alpha << 24;
	}
}
