extern char g_6b5c60[];
extern char* g_14a5320[];
extern char* g_14a5770[];
extern char* g_14abc28;
extern unsigned char g_773d75;
extern char* g_773da8;

#include <string.h>

int sprintf(char*, const char*, ...);
char* __cdecl fcn_0042b2f0(char*, int, int);

/* genitive ending test on the last character of a name */
#define ENDS_APOSTROPHE(x) ((x)[strlen(x) - 1] == 's' || (x)[strlen(x) - 1] == 'z' || (unsigned char) (x)[strlen(x) - 1] == -0x21 || (x)[strlen(x) - 1] == 'x')

/* ADDRESS: GOLDTL 0x00517c00 */
int __cdecl fcn_00517c00(int a1, unsigned char a2, int a3, char* a4)
{
	unsigned char b1[0x100];
	unsigned char b3[0x100];
	unsigned char b2[0x100];
	unsigned char loc[0x21c];
	char* p;
	int i;
	b1[0] = g_6b5c60[0];
	memset(&b1[1], 0, 255);
	b3[0] = g_6b5c60[0];
	memset(&b3[1], 0, 255);
	b2[0] = g_6b5c60[0];
	memset(&b2[1], 0, 255);
	if (a1 < 0 || a1 == 0xffff) {
		strcpy(a4, g_14abc28);
		return 0;
	}
	if (a1 != 0xfffe) {
		p = (char*) 0x7f4ca0 + a1 * 0x21c;
	} else {
		memset(loc, 0, 0x21c);
		p = (char*) loc;
		strcpy((char*) p + 0x30, g_14a5770[2]);
	}
	if (p == (char*) g_773da8) {
		strcpy(a4, (char*) 0x868060 + g_773d75 * 0x2f4);
		if (a2 != 2) {
			return 1;
		}
		strcat(a4, "'s");
		return 1;
	}
	switch (a3 & 0xff) {
	case 1:
		strcpy(a4, (char*) p + 0x30);
		if (a2 != 2) {
			return 1;
		}
		if (ENDS_APOSTROPHE((char*) p + 0x30)) {
			strcat(a4, "'");
		} else {
			strcat(a4, "s");
		}
		return 1;
	case 2:
		if (!*(unsigned char*) (p + 0xd)) {
			sprintf(a4, "%s", (char*) p + 0x30);
		} else if (!p[0x40]) {
			sprintf(a4, "%s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], 1, 4), (char*) p + 0x30);
		} else {
			sprintf(a4, "%s %s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], 1, 4), (char*) p + 0x30, (char*) p + 0x40);
		}
		return 1;
	case 3:
		if (*(unsigned char*) (p + 0x166)) {
			if (p[0x40]) {
				sprintf(a4, "%s %s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4), (char*) p + 0x30, (char*) p + 0x40);
			} else {
				sprintf(a4, "%s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4), (char*) p + 0x30);
			}
		} else if (p[0x40]) {
			sprintf(a4, "%s %s", (char*) p + 0x30, (char*) p + 0x40);
		} else {
			sprintf(a4, "%s", (char*) p + 0x30);
		}
		if (a2 != 2) {
			return 1;
		}
		if (ENDS_APOSTROPHE((char*) p + 0x40)) {
			strcat(a4, "'");
		} else {
			strcat(a4, "s");
		}
		return 1;
	case 4:
		if (*(unsigned char*) (p + 0x164)) {
			sprintf(a4, "%s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (p + 0x164)], 1, 4), (char*) p + 0x30);
		} else if (*(unsigned char*) (p + 0x165)) {
			sprintf(a4, "%s %s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (p + 0x165)], 1, 4), (char*) p + 0x30);
		} else {
			sprintf(a4, "%s", (char*) p + 0x30);
		}
		if (a2 != 2) {
			return 1;
		}
		if (ENDS_APOSTROPHE((char*) p + 0x30)) {
			strcat(a4, "'");
		} else {
			strcat(a4, "s");
		}
		return 1;
	case 5:
		sprintf(a4, "%s", fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4));
		return 1;
	case 6:
		if (p[0x40]) {
			strcpy(a4, (char*) p + 0x40);
		} else {
			strcpy(a4, (char*) p + 0x30);
		}
		return 1;
	case 7:
		if (a2 == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x40)) {
				if (p[0x40]) {
					sprintf(a4, "%s %s'", (char*) p + 0x30, (char*) p + 0x40);
				} else {
					sprintf(a4, "%s'", (char*) p + 0x30);
				}
			} else if (p[0x40]) {
				sprintf(a4, "%s %ss", (char*) p + 0x30, (char*) p + 0x40);
			} else {
				sprintf(a4, "%ss", (char*) p + 0x30);
			}
		} else if (p[0x40]) {
			sprintf(a4, "%s %s", (char*) p + 0x30, (char*) p + 0x40);
		} else {
			sprintf(a4, "%s", (char*) p + 0x30);
		}
		return 1;
	case 8:
		if (*(unsigned char*) (p + 0xd)) {
			strcpy((char*) b3, fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], 1, 4));
		}
		if (*(unsigned char*) (p + 0x166)) {
			strcpy((char*) b2, fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4));
		}
		if (a2 == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x30)) {
				sprintf((char*) b1, "%s'", (char*) p + 0x30);
			} else {
				sprintf((char*) b1, "%ss", (char*) p + 0x30);
			}
		} else {
			strcpy((char*) b1, (char*) p + 0x30);
		}
		sprintf(a4, "%s %s", (char*) (*(unsigned char*) (p + 0x166) ? b2 : b3), (char*) b1);
		return 1;
	case 9:
		if (*(unsigned int*) (p + 0x1cc) & 0x3e00) {
			if (*(unsigned int*) (p + 0x1cc) & 0x1000) {
				i = 0x26;
			} else if (*(unsigned int*) (p + 0x1cc) & 0x2000) {
				i = 0x27;
			} else if (*(unsigned int*) (p + 0x1cc) & 0x800) {
				i = 0x25;
			} else if (*(unsigned int*) (p + 0x1cc) & 0x400) {
				i = 0x24;
			} else {
				i = (*(unsigned int*) (p + 0x1cc) & 0x200) != 0 ? 0x23 : 0;
			}
		} else {
			i = *(unsigned char*) (p + 0x166);
		}
		if (*(unsigned char*) (p + 0xd)) {
			strcpy((char*) b3, fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], a2, 4));
		}
		if (i != 0) {
			strcpy((char*) b2, fcn_0042b2f0(g_14a5320[(p[9] != 0 ? 0x27b : 0x253) + i], a2, 4));
		}
		if (a2 == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x30)) {
				sprintf((char*) b1, "%s'", (char*) p + 0x30);
			} else {
				sprintf((char*) b1, "%ss", (char*) p + 0x30);
			}
		} else {
			strcpy((char*) b1, (char*) p + 0x30);
		}
		sprintf(a4, "%s %s", (char*) (i != 0 ? b2 : b3), (char*) b1);
		return 1;
	}
	return 1;
}
unsigned char _dpad_149d188[33176];
unsigned char _dpad_14a5320[620];
unsigned char _dpad_14abc28[38612];
