/* fcn_0044d310 — store the current value into the record's 0xd8 slot. */

void* __cdecl fcn_0064f026(int, int);
float __cdecl fcn_0064d62e(void*);

/* ADDRESS: GOLDTL 0x0044d310 */
void __cdecl fcn_0044d310(int a1, int a2)
{
	char* base;
	float value;

	value = fcn_0064d62e(fcn_0064f026(0, 0x662d18));
	base = *(char**) (a2 + 0x10);
	*(float*) (base + *(int*) (a2 + 8) * 0xe0 + 0xd8) = value;
}
