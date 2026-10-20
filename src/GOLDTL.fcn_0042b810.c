#include <stdio.h>
#include <string.h>

#pragma intrinsic(memset, strlen, strcpy, strcat)

char* __cdecl fcn_0042b790(char* s);
void __cdecl fcn_0042b7e0(char* s);
char* __cdecl fcn_0064e790(const char* s, int c);

/* ADDRESS: GOLDTL 0x0042b810 */
int __cdecl fcn_0042b810(char* text, int index)
{
	char v19[128];
	char v16[128];
	char v15[128];
	char v18[128];
	char v17[256];
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

	kind = 0;
	count = 0;
	memset(v20, 0, sizeof(v20));
	memset(v21, 0, sizeof(v21));
	memset(v15, 0, sizeof(v15));
	memset(v16, 0, sizeof(v16));
	v19[0] = 0;
	v18[0] = 0;
	p = strtok(text, ",\";\n");
	while (p != 0) {
		if (count == 0) {
			strcpy(v17, p);
			q = fcn_0042b790(v17);
			fcn_0042b7e0(q);
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
			q = fcn_0042b790(p);
			if (q != 0) {
				fcn_0042b7e0(q);
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
						memset(v15, 0, sizeof(v15));
						strncpy(v15, r + 1, (int) (s - (r + 1)) - 1);
						t = fcn_0064e790(s, ']');
						if (t == 0) {
							return 0;
						}
						memset(v16, 0, sizeof(v16));
						strncpy(v16, s + 1, (int) (t - (s + 1)) - 1);
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
						memset(v15, 0, sizeof(v15));
						strncpy(v15, r + 1, (int) (t - (r + 1)) - 1);
						memset(v16, 0, sizeof(v16));
						strncpy(v16, r + 2, (int) (t - (r + 2)) - 1);
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
		strcat((char*) (*(int*) 0x6b7fa0 + (*(int*) 0x6b7f98 << 12)), v20[i]);
		*(int*) 0x6b7fa4 = *(int*) 0x6b7fa4 + strlen(v20[i]);
	}
	for (i = 0; i < 4; i++) {
		strcat(v21[i], "|");
		strcat((char*) (*(int*) 0x6b7fa0 + (*(int*) 0x6b7f98 << 12)), v21[i]);
		*(int*) 0x6b7fa4 = *(int*) 0x6b7fa4 + strlen(v21[i]);
	}
	*(int*) (*(int*) 0x6b7f98 * 4 + 0x11bb000) = kind;
	sprintf((char*) (*(int*) 0x6b7f98 * 0x50 + 0x1053000), "%s+%i",
	    (char*) (index * 0x50 + 0x13350d0),
	    *(int*) 0x6b7f98 - *(int*) (index * 4 + 0x14b731c));
	*(int*) 0x6b7fa4 = *(int*) 0x6b7fa4 + 1;
	*(int*) 0x6b7f98 = *(int*) 0x6b7f98 + 1;
	return 1;
}
