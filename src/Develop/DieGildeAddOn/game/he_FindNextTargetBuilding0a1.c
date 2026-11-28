


int __cdecl gm_StartFilteredEntitySearch(int, int, int);

/* ADDRESS: GOLDDE 0x00563610 */
int __cdecl he_FindNextTargetBuilding0a1(char* e)
{
	int idx;
	int n;
	int r;

	idx = *(int*) (e + 0xbc);
	r = 0;
	n = 3;
	do {
		if (n == 0) {
			break;
		}
		r = gm_StartFilteredEntitySearch(1, 5, *(unsigned short*) (e + idx * 2 + 0xc0));
		n--;
		idx = idx % 4 + 1;
	} while (r == 0);
	return r;
}
