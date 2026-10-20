#include <stdio.h>
#include <string.h>

extern int g_77250c;

unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl fcn_00502cd0(int, int, ...);
char __cdecl fcn_00443e10(void*, int*);
void __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00532750 */
void __cdecl fcn_00532750(char* a)
{
	int rc[4];
	char key[0x60];
	char value[0x100];
	unsigned short* e;
	char* p;

	p = (char*) *(int*) 0x7746c8;
	if (p == 0) {
		p = (char*) *(int*) 0x7746c4;
		if (p == 0) {
			return;
		}
	}
	if (strstr(a, (char*) 0x6a1f84) == 0) {
		return;
	}
	strcpy(key, a + 0x10);
	if (*(int*) 0x7746c8 != 0) {
		e = (unsigned short*) fcn_00502cd0(*(int*) (p + 0x5d), 1, 4, 6);
	} else {
		e = (unsigned short*) fcn_00502cd0(*(int*) (p + 0x5d), 1, 4, 2);
	}
	while (e != 0) {
		if (strcmpi(key, (char*) (*(int*) 0x99ec10 + (int) *e * 0x40 + (int) *e + 1)) == 0) {
			goto found;
		}
		e = gm_NextEntityQueryMatch();
	}
	if (*(int*) 0x7746c8 == 0) {
		return;
	}
	e = (unsigned short*) fcn_00502cd0(*(int*) (p + 0x5d), 1, 0, 0xfd);
found:
	if (e == 0) {
		return;
	}
	if (*e != 0xfd) {
		sprintf(value, (char*) 0x68b3f8,
			*(char**) ((int) *e * 8 + 0x14a79c0), *(char**) 0x14a552c);
	} else if (*(int*) 0x7746cc != 0) {
		sprintf(value, (char*) 0x68b3f8,
			*(char**) ((int) *(unsigned short*) *(int*) 0x7746cc * 8 + 0x14a79c0),
			*(char**) 0x14a5530);
	} else {
		sprintf(value, (char*) 0x68b3f8,
			*(char**) ((int) *(unsigned char*) p * 0x38 + 0x14a6558),
			*(char**) 0x14a5530);
	}
	if (fcn_00443e10(a, rc)) {
		fcn_0046bd20((rc[2] - rc[1]) / 2 + rc[1] - 0x50, rc[1], 0xa0, 0x60,
			g_77250c, value, 0x28);
	}
}
