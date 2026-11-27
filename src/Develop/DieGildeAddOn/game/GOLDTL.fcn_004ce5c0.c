


unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_LookupWeaponSpec(int);

int __cdecl gm_GetUnitWeaponSpec(char* obj)
{
	unsigned short* p;
	int r;

	for (p = fcn_00502cd0(*(int*) (obj + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		r = gm_LookupWeaponSpec(*p);
		if (r != 0) {
			return r;
		}
	}
	return gm_LookupWeaponSpec(0);
}
