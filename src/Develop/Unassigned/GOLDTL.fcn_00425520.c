

int __cdecl msx_GetSampleStatus(int);

int __cdecl fcn_00425520(void)
{
	int r;

	r = 0;
	if (*(int*) 0x6b7d80 != 0) {
		if (msx_GetSampleStatus(*(int*) 0x6b7d80) == 4) {
			r = 1;
		}
	}
	return r;
}
