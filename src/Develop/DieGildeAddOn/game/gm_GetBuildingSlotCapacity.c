


void* __cdecl gm_QueryEntities(int, int, int, int, int);

int __cdecl gm_GetBuildingSlotCapacity(char* p)
{
	int r;

	r = 2;
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x274) != 0) {
		r = 3;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x27e) != 0) {
		r++;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x28e) != 0) {
		r++;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x291) != 0) {
		r++;
	}
	return r;
}
