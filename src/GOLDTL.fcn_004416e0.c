void __cdecl fcn_0043c2c0(char* a);

// FUNCTION: GOLDTL 0x4416e0
// SIZE: 32
void __cdecl fcn_004416e0(char* a, float v)
{
	if (a != 0) {
		*(float*) (a + 0x78) = -v;
		*(float*) (a + 0x60) = v;
		fcn_0043c2c0(a);
	}
}
