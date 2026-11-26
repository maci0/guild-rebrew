


void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);

void* __cdecl gm_GetGuildHall(int building_slot)
{
	void* building;

	building = 0;
	switch (building_slot) {
	case 1:
		building = gm_StartFilteredEntitySearch(1, 5, 0xf);
		break;
	case 6:
	case 7:
		building = 0;
		break;
	case 2:
		building = gm_StartFilteredEntitySearch(1, 5, 0x17);
		break;
	case 3:
		building = gm_StartFilteredEntitySearch(1, 5, 0x18);
		break;
	case 4:
		building = gm_StartFilteredEntitySearch(1, 5, 0x19);
		break;
	case 5:
		building = gm_StartFilteredEntitySearch(1, 5, 0x1a);
		break;
	}
	return building;
}
