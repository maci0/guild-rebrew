/*
 * Transport/goods position builder.
 *
 * Resolves the entity's layout block, walks the three 0x7c-byte route layers
 * and accumulates the eight corner positions of every visible layer, then
 * emits four vertex streams plus the depth values.
 *
 * Reconstructed range 0x435910..0x435971: the entity lookup, the layout block
 * fetch and the layer walk guard. The per-layer x87 matrix accumulation from
 * 0x435977 and the four emit loops through 0x43692e are not reconstructed
 * here; the decompiler only recovers them via the FPU stack, which no C
 * statement order reproduces.
 */

extern float g_6628a8;			/* 0x006628a8 */

int* __cdecl fcn_004356c0(int);

/* ADDRESS: GOLDTL 0x00435910 */
void __cdecl fcn_00435910(int a0, int* a1, float* a2, float* a3)
{
	int* v2;
	int layout;
	float* v20;
	int* layer;
	int count;
	int layers;

	v2 = fcn_004356c0(a0);
	layout = *(int*) (a0 + 0x318);
	v20 = *(float**) (layout + 0x294);
	count = 1;
	layer = (int*) (a0 + 0x32c);
	layers = 3;
	do {
		if (layer[0x19] && (*(float*) ((char*) layer + 0x3c) != g_6628a8)) {
			/* 0x435977..0x435d89: corner transform of this layer */
		}
		layer = (int*) ((char*) layer + 0x7c);
	} while (--layers);
}
