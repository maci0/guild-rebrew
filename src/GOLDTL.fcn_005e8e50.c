// FUNCTION: GOLDTL 0x5e8e50
// SIZE: 40

void __cdecl fcn_005e8e50(float x, float y, char* s, float* out)
{
	out[0] = x / *(float*) (s + 0x10) * *(float*) 0x6660fc;
	out[1] = y / *(float*) (s + 0x10) * *(float*) 0x6660fc;
}
