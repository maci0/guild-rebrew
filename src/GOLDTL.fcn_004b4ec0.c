void __cdecl fcn_004b5440(int, float*);

// FUNCTION: GOLD 0x004b4d50
// SIZE: 57
// FUNCTION: GOLDTL 0x4b4ec0
// SIZE: 57

int __cdecl fcn_004b4ec0(int a, char* e)
{
	float v[3];

	fcn_004b5440(0, v);
	if (*(int*) (e + 0x14) * 0.01f <= v[2])
		return 1;
	return 0;
}
