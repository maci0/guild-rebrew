

typedef int (__stdcall* fcn_004117f0_m)(int*);

int __cdecl fcn_004117f0(int enable)
{
	int* obj;

#ifdef REBREW_GOLD
	obj = *(int**) 0x14673cc;
#else
	obj = *(int**) 0x14ce90c;
#endif
	if (obj == 0) {
		return 0;
	}
	if (enable != 0) {
		if (((fcn_004117f0_m) ((int*) *obj)[7])(obj) < 0) {
			return 0;
		}
	} else {
		((fcn_004117f0_m) ((int*) *obj)[8])(obj);
	}
	return 1;
}
