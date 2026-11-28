


unsigned short* __cdecl gm_QueryEntities(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_LookupWeaponSpec(int);

/* ADDRESS: GOLDDE 0x004bbdb0 */
char* __cdecl gm_GetEquippedCombatGear(char* x)
{
	unsigned short* e;
	char* r;

	e = gm_QueryEntities(*(int*) (x + 0x178), 1, 5);
	while (e != 0) {
		r = gm_LookupWeaponSpec(*e);
		if (r != 0) {
			if ((*(int*) (r + 0x58) == 1 || *(int*) (r + 0x58) == 2) && *(int*) ((char*) e + 0x20) <= 0)
				return gm_LookupWeaponSpec(0);
			return r;
		}
		e = gm_NextEntityQueryMatch();
	}
	return gm_LookupWeaponSpec(0);
}
