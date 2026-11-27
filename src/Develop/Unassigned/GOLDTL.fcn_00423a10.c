

char* __cdecl sbs_FindSet(int);

char* __cdecl sbs_GetLastSetSample(int set_id)
{
	char* p;
	char* q;

	q = 0;
	p = sbs_FindSet(set_id);
	if (p != 0) {
		q = *(char**) (p + 0x38);
		if (q != 0) {
			while (*(char**) (q + 0x104) != 0) {
				q = *(char**) (q + 0x104);
			}
		}
	}
	return q;
}
