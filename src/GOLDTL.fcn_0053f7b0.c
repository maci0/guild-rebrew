


#include <windows.h>
#include <stdio.h>
#include <string.h>

extern int g_7e1d60[0x80];

int __cdecl fcn_004c3100(char*, int);
int __cdecl fcn_00422dc0(char*, int);

int __cdecl fcn_0053f7b0(char* path)
{
	char line[0x100];
	FILE* f;
	int* slot;
	char* s;
	char* e;

	memset(g_7e1d60, 0, sizeof(g_7e1d60));
	f = fopen(path, "rt");
	if (f == 0) {
		MessageBoxA(0, "main_PreloadSound(): Could not open sound-definition!", "Error", 0x30);
		return 0;
	}
	slot = g_7e1d60;
	do {
		memset(line, 0, sizeof(line));
		fgets(line, 0x100, f);
		if (strstr(line, "//") == 0) {
			s = strstr(line, "#include");
			if (s != 0) {
				s = strchr(s, '"');
				if (s == 0) {
					return 0;
				}
				s++;
				e = strchr(s, '"');
				if (e == 0) {
					return 0;
				}
				*e = 0;
				if (_strnicmp(s, "sprache\\", 8) == 0) {
					e = strchr(s, '\\');
					*slot = fcn_004c3100(e + 1, 0);
				} else {
					*slot = fcn_00422dc0(s, 0);
				}
				slot++;
				if ((int) slot > (int) &g_7e1d60[0x80]) {
					return 0;
				}
			}
		}
	} while (!feof(f));
	fclose(f);
	return 1;
}
