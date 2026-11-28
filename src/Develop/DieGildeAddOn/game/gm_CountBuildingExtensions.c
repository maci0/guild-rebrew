


void* __cdecl gm_QueryEntities(int, int, int, int, int);

int __cdecl gm_CountBuildingExtensions(char* p)
{
	int r;

	r = 1;
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x27a) != 0) {
		r = 2;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x27b) != 0) {
		r++;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x292) != 0) {
		r++;
	}
	return r;
}
