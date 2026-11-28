

int __cdecl fcn_0064d530(int, int, int);

int __cdecl sbs_GetRootSetName(int nameBuf, int bufSize)
{
	int r = 0;

	if (*(int*) 0x6b7d68 != 0) {
		fcn_0064d530(nameBuf, *(int*) 0x6b7d68, bufSize);
	} else {
		r = -1;
	}
	return r;
}
