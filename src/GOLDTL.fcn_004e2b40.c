char* __cdecl fcn_00508e40(int);
float __cdecl fcn_004fef80(char*);

// FUNCTION: GOLDTL 0x004e2b40
// SIZE: 46

int __cdecl fcn_004e2b40(char* m)
{
	if (fcn_004fef80(fcn_00508e40(*(int*) (m + 0x34))) > 0.0f)
		return 0;
	return 1;
}
