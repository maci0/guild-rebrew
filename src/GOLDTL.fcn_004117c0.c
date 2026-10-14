

typedef int (__stdcall* fcn_004117c0_m)(int*);

int __cdecl fcn_004117c0(int a1)
{
	int* obj;

	obj = *(int**) 0x14ce8a0;
	if (obj == 0) {
		return 0;
	}
	if (a1 != 0) {
		if (((fcn_004117c0_m) ((int*) *obj)[7])(obj) < 0) {
			return 0;
		}
	} else {
		((fcn_004117c0_m) ((int*) *obj)[8])(obj);
	}
	return 1;
}
