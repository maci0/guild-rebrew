


#include <string.h>

extern char g_6b7d88[];

void __cdecl sb_SetSampleBasePath(char* path)
{
	if (path != 0) {
		strcpy(g_6b7d88, path);
		if (path[strlen(path) - 1] != '\\') {
			strcat(g_6b7d88, "\\");
		}
	}
}
