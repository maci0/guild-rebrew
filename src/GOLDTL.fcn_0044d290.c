/* fcn_0044d290 — store the current value into the record's 0xd0 slot. */

void* __cdecl fcn_0064f026(int, int);
float __cdecl fcn_0064d62e(void*);

// FUNCTION: GOLDTL 0x44d290
// SIZE: 51
void __cdecl fcn_0044d290(int a1, int a2)
{
	char* base;
	float value;

	value = fcn_0064d62e(fcn_0064f026(0, 0x662d18));
	base = *(char**) (a2 + 0x10);
	*(float*) (base + *(int*) (a2 + 8) * 0xe0 + 0xd0) = value;
}
