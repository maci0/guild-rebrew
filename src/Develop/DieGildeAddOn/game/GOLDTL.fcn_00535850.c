extern char g_6b5c60[];




#include <string.h>

int __cdecl cm_RequestSysMessage(int, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00533a40(char*);
void __cdecl main_RunFrameLoop(int, int);

void __cdecl cm_SaveGameAndWait(int flags, char* name)
{
	char buf[0x7c];
	int cmd_slot;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	cmd_slot = cm_RequestSysMessage(0xe, buf);
	flags |= 0x300000;
	while (cm_GetCommandStatus(cmd_slot) == 0) {
		fcn_00533a40(name);
		main_RunFrameLoop(0, flags);
	}
	fcn_00533a40(g_6b5c60);
}
