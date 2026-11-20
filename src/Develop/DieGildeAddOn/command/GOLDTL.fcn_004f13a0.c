


int __cdecl cm_GetBuildingStatCount(char*);

int __cdecl cm_CountOccupiedBuildingStats(char* building)
{
	int n;
	int c;
	char* p;

	n = cm_GetBuildingStatCount(building);
	c = 0;
	if (n == 0) {
		return 0;
	}
	if (n > 0) {
		p = *(char**) (*(char**) (building + 0x65) + 0x20);
		do {
			if (*(int*) p != -1) {
				c++;
			}
			p += 0x44;
		} while (--n != 0);
	}
	return c;
}
