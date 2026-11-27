

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetStreamPan(int a1, int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(a1) >= 0) {
			*out = (*(f*) 0x00662434)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
