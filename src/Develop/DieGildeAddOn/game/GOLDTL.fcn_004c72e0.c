


void* __cdecl gm_StartFilteredEntitySearch(int, int, int);

int __cdecl fcn_004c72e0(int* args)
{
	char* p;

	p = (char*) gm_StartFilteredEntitySearch(1, 1, args[4]);
	if (p != 0 && (p[0x5a] & 2) != 0) {
		return 0;
	}
	return 1;
}
