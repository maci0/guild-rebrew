

void __cdecl fcn_00471e30(int);
void __cdecl d2_DestroyElement(int);

void __cdecl fcn_005b18c0(int* obj)
{
	int i;

	fcn_00471e30(*obj);
	for (i = 0; i < 0x300; i++) {
		if (obj[0x637 + i] != -1) {
			d2_DestroyElement(obj[0x637 + i]);
			obj[0x637 + i] = -1;
		}
	}
	*obj = -1;
}
