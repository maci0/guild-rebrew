// FUNCTION: GOLDTL 0x507ed0
// SIZE: 57

float __cdecl fcn_00507ed0(float a, float b)
{
	return (((a - b * b) * *(float*) 0x662d34 + *(float*) 0x6628d8)
	      + ((a * a - b) * *(float*) 0x6628d8 + *(float*) 0x662d34)) * *(float*) 0x6628cc;
}
