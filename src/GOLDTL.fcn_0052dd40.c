// FUNCTION: GOLDTL 0x0052dd40
// SIZE: 52

int __cdecl fcn_0064d470(const char*, const char*);

char __cdecl fcn_0052dd40(char* name, int* list)
{
	if (fcn_0064d470(name, "sp_WIMPEL")) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x20;
}
