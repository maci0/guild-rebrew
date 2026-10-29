#include <stdio.h>
#include <string.h>

extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
extern char g_6b5c60[];

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_0041d9e0(char*);

/* ADDRESS: GOLDTL 0x00515010 */
void __cdecl fcn_00515010(void)
{
	int cnt;
	char* p;
	unsigned char* e;
	char* q;
	char line[0x100];
	char tmp[0x200];
	char tbl[0x300];
	char msg[0x200];
	char* src;
	unsigned char* p2;
	int i;
	int j;

	e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	while (e != 0) {
		if (lpGebaeudePROT[*e] != 0x1c) {
			e[5] = *(unsigned char*) 0x6b5c60;
		}
		e = (unsigned char*) gm_FindNextFilteredEntity();
	}
	e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	if (e == 0) {
		return;
	}
	do {
		if (lpGebaeudePROT[*e] != 0x1c) {
			cnt = 0;
			e[5] = *(unsigned char*) 0x6b5c60;
			p = tbl;
			for (i = 0; i < 0xc; i++) {
				src = (char*) *(int*) ((i + (int) *e * 0xe) * 4 + 0x14a6560);
				if (*src == 0) {
					continue;
				}
				strcpy(line, src);
				for (j = 0; j < 0x100; j++) {
					p2 = lpGebaeudeINST + j * 0xa9;
					if (*p2 != 0 && strcmp((char*) (p2 + 5), line) == 0) {
						break;
					}
				}
				if (j >= 0x100) {
					if (strlen(line) >= 0x20) {
						sprintf(msg, (char*) 0x69983c, line);
					} else {
						strcpy(p, line);
						p += 0x40;
						cnt++;
					}
				}
			}
			if (cnt != 0) {
				q = tbl + (gm_RandomMod((unsigned char) cnt) & 0xffff) * 0x40;
				if (strlen(q) >= 0x20) {
					sprintf(tmp, (char*) 0x69983c, q);
					fcn_0041d9e0(tmp);
				} else {
					strcpy((char*) (e + 5), q);
				}
			}
		}
		e = (unsigned char*) gm_FindNextFilteredEntity();
	} while (e != 0);
}
