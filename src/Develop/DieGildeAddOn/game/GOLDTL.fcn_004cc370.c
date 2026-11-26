


char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_CheckEntityType(char*);
void __cdecl fcn_0052db70(char*);

int __cdecl cm_ExUpdateBuildingSmoke(char* packet, char* reply)
{
	char* building;

	building = gm_StartFilteredEntitySearch(1, 1, *(int*) (packet + 0x10));
	if (building != 0 && *(int*) (building + 0x61) != 0 && gm_CheckEntityType(building) == 0) {
		fcn_0052db70(building);
	}
	if (reply != 0) {
		reply[0] = 1;
		reply[1] = 0;
		*(int*) (reply + 6) = 0;
	}
	return 0;
}
