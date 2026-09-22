// FUNCTION: GOLD 0x00449d80
// SIZE: 23
// fcn_00449d80 — *(float*)(a+0x94) *= *(float*)b; return 1.

int __cdecl fcn_00449d80(char* a, float* b)
{
	*(float*) (a + 0x94) *= *b;
	return 1;
}
