/* ADDRESS: GOLD 0x00454030 */
// fcn_00454030 — transpose a 4x4 matrix, src stride 0x10.

void __cdecl fcn_00454030(int* src, int* dst)
{
	int i;
	int j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			dst[i * 4 + j] = src[j * 4 + i];
		}
	}
}
