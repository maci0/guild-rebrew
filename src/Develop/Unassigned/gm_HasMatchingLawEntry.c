

int __cdecl gm_FindMatchingLawEntry(int);

int __cdecl gm_HasMatchingLawEntry(int a)
{
	return gm_FindMatchingLawEntry(a) >= 0;
}
