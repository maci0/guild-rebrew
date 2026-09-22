// FUNCTION: GOLD 0x005dc360
// SIZE: 40
// fcn_005dc360 — *out = (a / [e+0x10]) * scale; *(out+4) = (b / [e+0x10]) * scale.

void __cdecl fcn_005dc360(float a, float b, char* e, float* out)
{
	*(float*) out = (a / *(float*) (e + 0x10)) * *(float*) 0x5eee10;
	*(float*) (out + 4) = (b / *(float*) (e + 0x10)) * *(float*) 0x5eee10;
}
