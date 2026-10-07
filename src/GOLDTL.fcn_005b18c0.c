// FUNCTION: GOLDTL 0x5b18c0

void __cdecl fcn_00471e30(int);
void __cdecl fcn_0046b2b0(int);

void __cdecl fcn_005b18c0(int* obj)
{
	int i;

	fcn_00471e30(*obj);
	for (i = 0; i < 0x300; i++) {
		if (obj[0x637 + i] != -1) {
			fcn_0046b2b0(obj[0x637 + i]);
			obj[0x637 + i] = -1;
		}
	}
	*obj = -1;
}
