

int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* fcn_0042a880_f)(int);

int __cdecl msx_EndSample(int a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			(*(fcn_0042a880_f*) 0x6623d0)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
