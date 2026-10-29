#include <stdio.h>
#include <string.h>

extern char g_1052f00[];

int __cdecl fcn_0042b370(const char* name);

/* ADDRESS: GOLDTL 0x0042b3c0 */
void __cdecl fcn_0042b3c0(void)
{
	char* p;
	char* q;
	int len;
	int value;
	FILE* out;
	FILE* in;
	int i;
	char c;
	char name[128];
	char line[128];
	char path[256];
	char tmp[128];

	i = 0;
	do {
		c = g_1052f00[i];
		path[i] = c;
		i++;
	} while (c != 0);
	strcat(path, "f3_textindex.h");
	out = fopen(path, "wt");
	i = 0;
	do {
		c = g_1052f00[i];
		path[i] = c;
		i++;
	} while (c != 0);
	strcat(path, "a_obj.h");
	in = fopen(path, "rt");
	if (in == 0)
		return;
	while (!feof(in)) {
		memset(line, 0, sizeof(line));
		memset(name, 0, sizeof(name));
		fgets(line, 127, in);
		line[strlen(line) - 1] = 0;
		p = strstr(line, "ob_");
		if (p != 0) {
			q = strchr(line, ',');
			if (q == 0)
				q = line + strlen(line);
			len = q - p;
			memcpy(name, p + 2, len - 2);
			name[len] = 0;
			if (strcmp(name, "_NULL") == 0)
				strcpy(name, "_OB_NULL");
			value = fcn_0042b370(name);
			if (value == -1)
				printf("Textlabel nicht gefunden: %s", name);
			sprintf(tmp, "#define %s %i", name, value);
			fputs(tmp, out);
		}
	}
	fclose(in);
	i = 0;
	do {
		c = g_1052f00[i];
		path[i] = c;
		i++;
	} while (c != 0);
	strcat(path, "a_geb.h");
	in = fopen(path, "rt");
	if (in == 0)
		return;
	while (!feof(in)) {
		memset(line, 0, sizeof(line));
		memset(name, 0, sizeof(name));
		fgets(line, 127, in);
		line[strlen(line) - 1] = 0;
		p = strstr(line, "gb_");
		if (p != 0) {
			q = strchr(line, ',');
			if (q == 0)
				q = line + strlen(line);
			len = q - p;
			memcpy(name, p + 2, len - 2);
			name[len] = 0;
			if (strcmp(name, "_NULL") == 0)
				strcpy(name, "_GB_NULL");
			value = fcn_0042b370(name);
			if (value == -1)
				printf("Textlabel nicht gefunden: %s", name);
			sprintf(tmp, "#define %s %i", name, value);
			fputs(tmp, out);
		}
	}
	fclose(in);
	fclose(out);
}
