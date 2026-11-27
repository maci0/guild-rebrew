void __cdecl d3_UpdateViewFrustum(void);
void __cdecl d3_InvalidateSceneRenderCache(int a);

/* ADDRESS: GOLDTL 0x00438fc0 */
void __cdecl d3_SetProjectionDistance(float v)
{
	register float t;

	if (!(v > *(double*) 0x662950)) {
		return;
	}
	if (v == *(float*) 0x10432a4) {
		return;
	}
	t = *(float*) 0x1042a18;
	*(float*) 0x10432a4 = v;
	t *= v;
	*(float*) 0x1042584 = t * *(float*) 0x662a94;
	d3_UpdateViewFrustum();
	d3_InvalidateSceneRenderCache(0);
}
