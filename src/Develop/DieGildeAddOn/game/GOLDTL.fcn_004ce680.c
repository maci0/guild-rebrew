


unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_LookupWeaponSpec(int);

unsigned short* __cdecl gm_FindEntityActiveItem(char* entity)
{
	unsigned short* p;
	char* r;

	for (p = fcn_00502cd0(*(int*) (entity + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		r = gm_LookupWeaponSpec(*p);
		if (r != 0) {
			if ((*(int*) (r + 0x58) == 1 || *(int*) (r + 0x58) == 2) && *(int*) ((char*) p + 0x20) <= 0) {
				return 0;
			}
			return p;
		}
	}
	return 0;
}
