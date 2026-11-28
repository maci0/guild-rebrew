


extern char gm_MissionJobs[];

/* ADDRESS: GOLDDE 0x004a1eb0 */
char* __cdecl gm_FindMissionByEntityId(int* query)
{
	int i;

	for (i = 0; i < 128; i++) {
		if (*(int*) ((int) gm_MissionJobs + i * 0x24) != 0 && *(int*) ((int) gm_MissionJobs + 4 + i * 0x24) == query[1]) {
			return (char*) ((int) gm_MissionJobs + i * 0x24);
		}
	}
	return 0;
}
