


void* __cdecl gm_StartFilteredEntitySearch(int, int, int);

int __cdecl cm_ChkSetGebBesitzer(int* args)
{
	char* p;

	p = (char*) gm_StartFilteredEntitySearch(1, 1, args[4]);
	if (p != 0 && (p[0x5a] & 2) != 0) {
		return 0;
	}
	return 1;
}
