extern char str_space[];
/* fcn_0044d2d0 — store the current value into the record's 0xd4 slot. */

void* __cdecl fcn_0064f026(int, int);
float __cdecl fcn_0064d62e(void*);

/* ADDRESS: GOLDTL 0x0044d2d0 */
/* ADDRESS: GOLDDE 0x00443080 */
void __cdecl d3_ParseMatUOffset(int unused, int ctx)
{
	char* base;
	float value;

	value = fcn_0064d62e(fcn_0064f026(0, (int) &str_space));
	base = *(char**) (ctx + 0x10);
	*(float*) (base + *(int*) (ctx + 8) * 0xe0 + 0xd4) = value;
}
