


extern char gm_MissionJobs[];

int __cdecl gm_HasActiveMission(int key)
{
	int p;

	for (p = (int) gm_MissionJobs + 4; p < (int) gm_MissionJobs + 0x1204; p += 0x24) {
		if (*(int*) (p - 4) != 0) {
			if (*(int*) p == key) {
				return 1;
			}
		}
	}
	return 0;
}
