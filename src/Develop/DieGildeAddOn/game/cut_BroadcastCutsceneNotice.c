#include <string.h>

void* __cdecl gm_SearchTable67(int id);
void __cdecl io_FormatTextBuffer(char* buf, int id, void* a3, int a4);
char* __cdecl gm_LookupEntityRecordById(int a1);
void __cdecl he_SendCmdMessage(int* a1, char* a2, char* text, char* extra);

extern unsigned char gm_ClientModeFlags;
extern char* g_14a9a1c;
extern char* g_14a9a20;
extern char str_empty[];

/* ADDRESS: GOLDTL 0x004e32c0 */
int __cdecl cut_BroadcastCutsceneNotice(char* cutscene)
{
	char buf[0x200];
	void* info;
	char* player;
	int i;

	info = gm_SearchTable67(*(int*) (cutscene + 0x7c));
	if (info == 0) {
		return 0;
	}
	io_FormatTextBuffer(buf, 0x3fd9, info, *(int*) (cutscene + 0x80));
	if ((gm_ClientModeFlags & 4)) {
        strcat(buf, g_14a9a20);
    } else {
        strcat(buf, g_14a9a1c);
    }
	for (i = 0; i < *(unsigned char*) (cutscene + 0x30); i++) {
		player = gm_LookupEntityRecordById(*(int*) (cutscene + 0x34 + i * 4));
		if (player != 0 && (*(unsigned char*) (player + 2) == 6 || *(unsigned char*) (player + 2) == 7)) {
			he_SendCmdMessage((int*) player, cutscene, buf, str_empty);
		}
	}
	return 1;
}