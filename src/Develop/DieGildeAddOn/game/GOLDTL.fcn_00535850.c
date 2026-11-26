extern char g_6b5c60[];




#include <string.h>

int __cdecl fcn_004c5790(int, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00533a40(char*);
void __cdecl main_RunFrameLoop(int, int);

void __cdecl cm_SaveGameAndWait(int flags, char* name)
{
	char buf[0x7c];
	int s;

	memset(buf, 0, sizeof(buf));
	strcpy(buf, name);
	s = fcn_004c5790(0xe, buf);
	flags |= 0x300000;
	while (fcn_004c4450(s) == 0) {
		fcn_00533a40(name);
		main_RunFrameLoop(0, flags);
	}
	fcn_00533a40(g_6b5c60);
}
