// FUNCTION: GOLD 0x00575800
// FUNCTION: GOLDTL 0x57dd40

int __cdecl fcn_0042e410(int);
int __cdecl fcn_005100f0(int, int);

int __cdecl fcn_0057dd40(void* a1)
{
	return fcn_005100f0(*(int*) ((char*) a1 + 4), (fcn_0042e410(4) & 0xffff) + 3);
}
