// FUNCTION: GOLD 0x00454030
// SIZE: 46
// fcn_00454030 — copy 4x4 matrix (src stride 0x10).

void __cdecl fcn_00454030(int* out, int* src)
{
	int r;
	int c;
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			out[r * 4 + c] = src[r * 4 + c * 4];
		}
	}
}
