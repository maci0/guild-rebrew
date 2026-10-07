// FUNCTION: GOLD 0x00459f80
// fcn_00459f80 — fill stride-0x1c slots with val.

void __cdecl fcn_00459f80(int val, int n, int* out)
{
	int i;
	for (i = 0; i < n; i++) {
		*out = val;
		out += 0x1c / 4;
	}
}
