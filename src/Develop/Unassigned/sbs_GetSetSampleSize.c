

int* __cdecl sbs_FindSetSample(int, int);

int __cdecl sbs_GetSetSampleSize(int set_id, int name)
{
	int r;
	int* p;

	r = 0;
	p = (int*) sbs_FindSetSample(set_id, name);
	if (p != 0) {
		r = p[0x100 / 4];
	}
	return r;
}
