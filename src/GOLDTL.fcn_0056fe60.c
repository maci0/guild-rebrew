// FUNCTION: GOLDTL 0x56fe60
// SIZE: 403

#include <windows.h>
#include <stdio.h>
#include <string.h>

// SIZE 0x10
struct helpev {
	int a;
	int b;
	int c;
	int label;
};

extern struct helpev g_77e0a0[0x80];
extern char g_6a3550[];

int __cdecl fcn_0042dc90(char*);
int __cdecl fcn_0064eeec(const char*);

void __cdecl fcn_0056fe60(char* name)
{
	char delim[2] = ":";
	char line[0x100];
	char label[0x100];
	char path[0x104];
	char msg[0x400];
	FILE* f;
	int n;
	char* tok;
	int i;

	sprintf(path, "%s\\tutorial\\%s.ini", g_6a3550, name);
	memset(g_77e0a0, 0, sizeof(g_77e0a0));
	f = fopen(path, "rt");
	if (f == 0) {
		MessageBoxA(0, "he_OpenHelpEvents(): Could not open help-definition!", "Error", 0x30);
		return;
	}
	n = 0;
	do {
		memset(line, 0, sizeof(line));
		fgets(line, 0x100, f);
		if (strstr(line, "//") == 0) {
			i = 0;
			for (tok = strtok(line, delim); tok != 0; tok = strtok(0, delim)) {
				if (i == 0) {
					strcpy(label, tok);
					g_77e0a0[n].label = fcn_0042dc90(label);
					if (g_77e0a0[n].label == -1) {
						sprintf(msg, "he_OpenHelpEvents(): invalid textlabel:%s", label);
					}
				} else if (i == 1) {
					g_77e0a0[n].a = fcn_0064eeec(tok);
				} else if (i == 2) {
					g_77e0a0[n].b = fcn_0064eeec(tok);
				} else if (i == 3) {
					g_77e0a0[n].c = fcn_0064eeec(tok);
				}
				i++;
			}
			n++;
			if (n > 0x80) {
				return;
			}
		}
	} while (!feof(f));
	fclose(f);
}
