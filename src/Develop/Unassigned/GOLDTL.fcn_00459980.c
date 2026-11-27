extern float g_6628a8;
/* ADDRESS: GOLDTL 0x00459980 */
void __cdecl d3_SetSkyLayerTransition(void *skyCtx, void *layer, char value, float scale)
{
	unsigned char *p;
	int zero;
	zero = 0;
	if ((int)skyCtx == zero || (int)layer == zero) {
		return;
	}
	p = (unsigned char *)layer;
	if (scale != g_6628a8) {
		p[0x28] = p[0x2a];
		p[0x29] = value;
		*(int *) (p + 0xc) = zero;
		*(float *) (p + 0x10) = 1.0f / scale;
	} else {
		*(float *) (p + 0xc) = 1.0f;
		*(int *) (p + 0x10) = zero;
		p[0x28] = p[0x2a];
		p[0x29] = p[0x2a];
	}
}
