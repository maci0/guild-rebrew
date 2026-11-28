typedef struct {
	int f0;
	int f4;
	char st[0xe];
	char pad16[2];
	int f18;
	int f1c;
	char f20;
	char pad21[3];
} rec24;
// SIZE 0x24

extern signed char gm_SelectedMissionIndex;
extern char gm_MissionJobs[];

unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

/* ADDRESS: GOLDTL 0x004b64b0 */
/* ADDRESS: GOLDDE 0x004a4740 */
int __cdecl ls_SaveMissionJobs(char* file)
{
	int i;

	if (!file)
		return 0;
	if (vfs_fwrite(&gm_SelectedMissionIndex, 1, 1, file) == -1)
		return 0;
	for (i = 0; i < 128; i++) {
		if (vfs_fwrite(&((rec24*)gm_MissionJobs)[i].f0, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)gm_MissionJobs)[i].f4, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(((rec24*)gm_MissionJobs)[i].st, 0xe, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)gm_MissionJobs)[i].f18, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)gm_MissionJobs)[i].f1c, 4, 1, file) == -1)
			return 0;
		if (vfs_fwrite(&((rec24*)gm_MissionJobs)[i].f20, 1, 1, file) == -1)
			return 0;
	}
	return 1;
}
