#include <string.h>

char* __cdecl gm_SearchTable67(int);
int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_004c5580(char*, int, char*);

/* ADDRESS: GOLD 0x004e48b0 */
/* ADDRESS: GOLDTL 0x004e6240 */

void __cdecl fcn_004e6240(int* a1, char* a2, char* text, char* extra)
{
	char m[0xf8];
	char buf[0x800];
	char* s;
	char* q;
	int k;
	int n;

	memset(m, 0, sizeof(m));
	m[4] = 0x11;
	*(int*) (m + 0xc) = -1;
	m[0x36] = 9;
	*(int*) (m + 0x58) = 0x5ec;
	*(int*) (m + 8) = a1[1];
	k = *(int*) (a2 + 0x14);
	if (k != -1 && (a2[0x26] & 0x10) != 0)
		m[0x9c] = 0xe;
	else
		m[0x9c] = 0xc;
	*(int*) (m + 0x5c) = k;
	*(int*) (m + 0x64) = *(int*) a2;
	*(int*) (m + 0x60) = -1;
	if (k != -1) {
		s = gm_SearchTable67(k);
		if (s != 0) {
			if (gm_CheckEntityType(s) == 0) {
				q = gm_SetupEntityQuery(s);
				if (q != 0)
					*(int*) (m + 0x60) = *(int*) (q + 2);
			} else {
				q = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfd);
				if (q != 0)
					*(int*) (m + 0x60) = *(int*) (q + 2);
			}
		}
	}
	strcpy(buf, text);
	n = strlen(buf) + 1;
	if (extra != 0 && *extra != 0) {
		memcpy(buf + n, extra, strlen(extra) + 1);
		m[0x9c] |= 0x10;
		fcn_004c5580(m, strlen(extra) + n + 1, buf);
	} else {
		fcn_004c5580(m, strlen(text) + 1, text);
	}
}
