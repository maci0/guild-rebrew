// FUNCTION: GOLDTL 0x418d70
// SIZE: 79

void __cdecl fcn_004237f0(char*, int);
void __cdecl fcn_004225e0(char*, int);

void __cdecl fcn_00418d70(char* p)
{
	if (*(char**) (p + 0x34) != 0) {
		fcn_004237f0(*(char**) (p + 0x34), 0);
		*(int*) (*(char**) (p + 0x34) + 0x14) |= 8;
		fcn_004225e0(*(char**) (p + 0x34), 0);
		*(char**) (p + 0x34) = 0;
	}
	if (*(char**) (p + 0x38) != 0) {
		*(int*) (*(char**) (p + 0x38) + 0x210) = 0;
		*(char**) (p + 0x38) = 0;
	}
}
