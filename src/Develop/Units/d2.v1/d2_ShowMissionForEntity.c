


// SIZE 0x24
typedef struct {
	int handle;
	int key;
	char pad[0x1c];
} Entry24;

extern int main_LoopFlags;
extern char gm_MissionJobs[];

void __cdecl d2_ShowMissionSpecDialog(int handle, int flags);

void __cdecl d2_ShowMissionForEntity(int key)
{
	int i;
	int flags;

	flags = main_LoopFlags | 0x80;
	for (i = 0; i < 128; i++) {
		if (((Entry24*)gm_MissionJobs)[i].handle != 0 && ((Entry24*)gm_MissionJobs)[i].key == key) {
			d2_ShowMissionSpecDialog(((Entry24*)gm_MissionJobs)[i].handle, flags | 0x80);
		}
	}
}
