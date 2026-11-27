

void* __cdecl sbs_FindSet(int);
int __cdecl sbs_CountSetEntries(int);

int __cdecl sbs_CalcSetDataSize(int set_id)
{
	int* entry;
	int result;

	result = 0;
	entry = (int*) sbs_FindSet(set_id);
	if (entry != 0) {
		result = entry[0xd] + sbs_CountSetEntries(set_id) * 12;
	}
	return result;
}
