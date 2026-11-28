#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/client_actions.h"
#include "Develop/DieGildeAddOn/game/entity.h"
extern char g_6b5c60[];
extern char* txt_TextEntries[];
extern char* g_14a5770[];
char* __cdecl txt_GetPackedStringEntry(char*, int, int);

/* Native cases3-9 compare the zero-extended byte to -33 (514807/51491c); preserve that failed sharp-s test. */
#define ENDS_APOSTROPHE(x) ((x)[strlen(x) - 1] == 's' || (x)[strlen(x) - 1] == 'z' || (unsigned char) (x)[strlen(x) - 1] == -0x21 || (x)[strlen(x) - 1] == 'x')

/* ADDRESS: GOLD 0x00514400 */
int __cdecl gm_FormatEntityName(int entityId, int gramCase, int formatMode, char* outBuf)
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
	if (entityId < 0 || entityId == 0xffff) {
		strcpy(outBuf, (*(char**) 0x1440ac8));
		return 0;
	}
	if (entityId != 0xfffe) {
		p = (char*) g_slot_table + entityId * 0x21c;
	} else {
		memset(loc, 0, 0x21c);
		p = (char*) loc;
		strcpy((char*) p + 0x30, g_14a5770[2]);
	}
	if (p == (char*) gm_CityEntity) {
		strcpy(outBuf, (char*) 0x7e3f40 + g_773d75 * 0x2f4);
		if ((unsigned char) gramCase == 2) {
			strcat(outBuf, "'s");
		}
		goto fail_1;
	}
	switch (formatMode & 0xff) {
	case 1:
		strcpy(outBuf, (char*) p + 0x30);
		if ((unsigned char) gramCase != 2) {
			break;
		}
		if (outBuf[strlen(outBuf) - 1] == 's' || outBuf[strlen(outBuf) - 1] == 'z' || (unsigned char) outBuf[strlen(outBuf) - 1] == 0xdf || outBuf[strlen(outBuf) - 1] == 'x') {
			strcat(outBuf, "'");
		} else {
			strcat(outBuf, "s");
		}
		goto fail_1;
	case 2:
		if (!*(unsigned char*) (p + 0xd)) {
			sprintf(outBuf, "%s", (char*) p + 0x30);
		} else if (!p[0x40]) {
			sprintf(outBuf, "%s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], 1, 4), (char*) p + 0x30);
		} else {
			sprintf(outBuf, "%s %s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], 1, 4), (char*) p + 0x30, (char*) p + 0x40);
		}
		goto fail_1;
	case 3:
		if (*(unsigned char*) (p + 0x166)) {
			if (p[0x40]) {
				sprintf(outBuf, "%s %s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4), (char*) p + 0x30, (char*) p + 0x40);
			} else {
				sprintf(outBuf, "%s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4), (char*) p + 0x30);
			}
		} else if (p[0x40]) {
			sprintf(outBuf, "%s %s", (char*) p + 0x30, (char*) p + 0x40);
		} else {
			sprintf(outBuf, "%s", (char*) p + 0x30);
		}
		if ((unsigned char) gramCase != 2) {
			break;
		}
		if (ENDS_APOSTROPHE((char*) p + 0x40)) {
			strcat(outBuf, "'");
		} else {
			strcat(outBuf, "s");
		}
		goto fail_1;
	case 4:
		if (*(unsigned char*) (p + 0x164)) {
			sprintf(outBuf, "%s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x18f : 0x130) + *(unsigned char*) (p + 0x164)], 1, 4), (char*) p + 0x30);
		} else if (*(unsigned char*) (p + 0x165)) {
			sprintf(outBuf, "%s %s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (p + 0x165)], 1, 4), (char*) p + 0x30);
		} else {
			sprintf(outBuf, "%s", (char*) p + 0x30);
		}
		if ((unsigned char) gramCase != 2) {
			break;
		}
		if (ENDS_APOSTROPHE((char*) p + 0x30)) {
			strcat(outBuf, "'");
		} else {
			strcat(outBuf, "s");
		}
		goto fail_1;
	case 5:
		sprintf(outBuf, "%s", txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], 1, 4));
		goto fail_1;
	case 6:
		if (p[0x40]) {
			strcpy(outBuf, (char*) p + 0x40);
			return 1;
		}
		strcpy(outBuf, (char*) p + 0x30);
		return 1;
	case 7:
		if ((unsigned char) gramCase == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x40)) {
				if (p[0x40]) {
					sprintf(outBuf, "%s %s'", (char*) p + 0x30, (char*) p + 0x40);
				} else {
					sprintf(outBuf, "%s'", (char*) p + 0x30);
				}
			} else if (p[0x40]) {
				sprintf(outBuf, "%s %ss", (char*) p + 0x30, (char*) p + 0x40);
			} else {
				sprintf(outBuf, "%ss", (char*) p + 0x30);
			}
		} else if (p[0x40]) {
			sprintf(outBuf, "%s %s", (char*) p + 0x30, (char*) p + 0x40);
		} else {
			sprintf(outBuf, "%s", (char*) p + 0x30);
		}
		goto fail_1;
	case 8:
		if (*(unsigned char*) (p + 0xd)) {
			strcpy((char*) b3, txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], gramCase & 0xff, 4));
		}
		if (*(unsigned char*) (p + 0x166)) {
			strcpy((char*) b2, txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x27b : 0x253) + *(unsigned char*) (p + 0x166)], gramCase & 0xff, 4));
		}
		if ((unsigned char) gramCase == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x30)) {
				sprintf((char*) b1, "%s'", (char*) p + 0x30);
			} else {
				sprintf((char*) b1, "%ss", (char*) p + 0x30);
			}
		} else {
			strcpy((char*) b1, (char*) p + 0x30);
		}
		if (*(unsigned char*) (p + 0x166)) {
			sprintf(outBuf, "%s %s", (char*) b2, (char*) b1);
		} else {
			sprintf(outBuf, "%s %s", (char*) b3, (char*) b1);
		}
		goto fail_1;
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
			strcpy((char*) b3, txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x11e : 0x114) + *(unsigned char*) (p + 0xd)], gramCase & 0xff, 4));
		}
		if (i != 0) {
			strcpy((char*) b2, txt_GetPackedStringEntry(txt_TextEntries[(p[9] != 0 ? 0x27b : 0x253) + i], gramCase & 0xff, 4));
		}
		if ((unsigned char) gramCase == 2) {
			if (ENDS_APOSTROPHE((char*) p + 0x30)) {
				sprintf((char*) b1, "%s'", (char*) p + 0x30);
			} else {
				sprintf((char*) b1, "%ss", (char*) p + 0x30);
			}
		} else {
			strcpy((char*) b1, (char*) p + 0x30);
		}
		sprintf(outBuf, "%s %s", (char*) (i != 0 ? b2 : b3), (char*) b1);
		goto fail_1;
	}
	goto fail_1;
fail_1:
	return 1;
}
