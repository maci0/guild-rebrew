extern int g_14a5508;
extern int main_LoopFlags;




#include <string.h>

__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
int __cdecl cm_RequestSysMessage(int, char*);
int __cdecl d2_OpenMessageBox(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);

void __cdecl sv_WaitForNetworkSync(int flags)
{
	char buf[0x7c];
	unsigned int start;
	int s;
	int h;

	start = timeGetTime();
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "sv_NetworkSync");
	s = cm_RequestSysMessage(0xe, buf);
	main_LoopFlags = flags;
	flags |= 0x300000;
	h = d2_OpenMessageBox(g_14a5508, 0);
	fcn_00471af0(h, 0);
	while (cm_GetCommandStatus(s) == 0) {
		if (timeGetTime() > start + 0x5dc) {
			fcn_00471af0(h, 1);
		}
		main_RunFrameLoop(0, flags);
	}
	d2_DestroyForm(h);
}
