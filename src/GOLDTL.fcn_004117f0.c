// FUNCTION: GOLDTL 0x4117f0

typedef int (__stdcall* fcn_004117f0_m)(int*);

int __cdecl fcn_004117f0(int a1)
{
	int* obj;

	obj = *(int**) 0x14ce90c;
	if (obj == 0) {
		return 0;
	}
	if (a1 != 0) {
		if (((fcn_004117f0_m) ((int*) *obj)[7])(obj) < 0) {
			return 0;
		}
	} else {
		((fcn_004117f0_m) ((int*) *obj)[8])(obj);
	}
	return 1;
}
