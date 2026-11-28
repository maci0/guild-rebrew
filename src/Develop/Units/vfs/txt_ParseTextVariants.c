#include <stdio.h>
extern void* txt_TextBuffer;
extern int g_6b7fa4, txt_EntryCount;
extern int g_11bb000[], g_14b731c[];
extern char g_1053000[][0x50], g_1335120[][0x50];
#include <string.h>

#pragma intrinsic(memset, strlen, strcpy, strcat)

char* __cdecl txt_SkipLeadingSpaces(char* s);
void __cdecl txt_TrimTrailingSpaces(char* s);
char* __cdecl fcn_0064e790(const char* s, int c);

/* ADDRESS: GOLDTL 0x0042b810 */
/* ADDRESS: GOLDDE 0x004257a0 */
int __cdecl txt_ParseTextVariants(char* text, int index)
{
	char v19[128];
	char v16[128];
	char v15[128];
	char v18[128];
	char tokenCopy[256];
	char v20[4][160];
	char v21[4][160];
	unsigned char count;
	unsigned char kind;
	char* p;
	char* q;
	char* r;
	char* s;
	char* t;
	int i;

	memset(v20, 0, sizeof(v20));
	memset(v21, 0, sizeof(v21));
	memset(v15, 0, sizeof(v15));
	memset(v16, 0, sizeof(v16));
	kind = 0;
	count = 0;
	v19[0] = 0;
	v18[0] = 0;
	p = strtok(text, ",\";\n");
	while (p != 0) {
		if (count == 0) {
			strcpy(tokenCopy, p);
			q = txt_SkipLeadingSpaces(tokenCopy);
			txt_TrimTrailingSpaces(q);
			if (strcmpi(q, "(m)") == 0) {
				kind = 0;
			}
			else if (strcmpi(q, "(w)") == 0) {
				kind = 1;
			}
			else if (strcmpi(q, "(s)") == 0) {
				kind = 2;
			}
		}
		else {
			q = txt_SkipLeadingSpaces(p);
			if (q != 0) {
				txt_TrimTrailingSpaces(q);
				r = fcn_0064e790(q, '[');
				if (r == 0) {
					strcpy(v18, q);
				}
				else {
					if (r != q) {
						memset(v18, 0, sizeof(v18));
						strncpy(v18, q, (int) (r - q));
					}
					s = fcn_0064e790(r, '/');
					if (s != 0) {
						r++;
						memset(v15, 0, sizeof(v15));
						strncpy(v15, r, (int) (s - r) - 1);
						t = fcn_0064e790(s, ']');
						if (t == 0) {
							return 0;
						}
						s++;
						memset(v16, 0, sizeof(v16));
						strncpy(v16, s, (int) (t - s) - 1);
						p = t + 1;
						if (strlen(p) != 0) {
							memset(v19, 0, sizeof(v19));
							strcpy(v19, p);
						}
					}
					else {
						t = fcn_0064e790(r, ']');
						if (t == 0) {
							return 0;
						}
						r++;
						memset(v15, 0, sizeof(v15));
						strncpy(v15, r, (int) (t - r) - 1);
						r++;
						memset(v16, 0, sizeof(v16));
						strncpy(v16, r, (int) (t - r) - 1);
						p = t + 1;
						if (strlen(p) != 0) {
							memset(v19, 0, sizeof(v19));
							strcpy(v19, p);
						}
					}
				}
				sprintf(v20[count - 1], "%s%s%s", v18, v15, v19);
				sprintf(v21[count - 1], "%s%s%s", v18, v16, v19);
			}
		}
		p = strtok(0, ",\";\n");
		count++;
	}
	for (i = 0; i < 4; i++) {
		strcat(v20[i], "|");
		strcat((char*) ((int) txt_TextBuffer + (txt_EntryCount << 12)), v20[i]);
		g_6b7fa4 = g_6b7fa4 + strlen(v20[i]);
	}
	for (i = 0; i < 4; i++) {
		strcat(v21[i], "|");
		strcat((char*) ((int) txt_TextBuffer + (txt_EntryCount << 12)), v21[i]);
		g_6b7fa4 = g_6b7fa4 + strlen(v21[i]);
	}
	g_11bb000[txt_EntryCount] = kind;
	sprintf(g_1053000[txt_EntryCount], "%s+%i",
	    g_1335120[index - 1],
	    txt_EntryCount - g_14b731c[index]);
	g_6b7fa4 = g_6b7fa4 + 1;
	txt_EntryCount = txt_EntryCount + 1;
	return 1;
}
