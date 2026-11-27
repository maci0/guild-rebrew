


// SIZE 0x24
typedef struct {
	int handle;
	int key;
	char pad[0x1c];
} Entry24;

extern int main_LoopFlags;
extern char g_10069a0[];

void __cdecl d2_ShowMissionSpecDialog(int handle, int flags);

void __cdecl d2_ShowMissionForEntity(int key)
{
	int i;
	int flags;

	flags = main_LoopFlags | 0x80;
	for (i = 0; i < 128; i++) {
		if (((Entry24*)g_10069a0)[i].handle != 0 && ((Entry24*)g_10069a0)[i].key == key) {
			d2_ShowMissionSpecDialog(((Entry24*)g_10069a0)[i].handle, flags | 0x80);
		}
	}
}
