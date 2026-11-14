#include <stdio.h>
#include <string.h>

/* Resolves the four head icon slots (+0x34..+0x40) from the name at +4:
 * "<base>_HEAD<i>_<suffix>_ICON.bmp" first, then "<base>_HEAD<i>_ICON.bmp",
 * each matched case-insensitively against the 0x30-byte icon table
 * (count at 0x6f1b90, entries at 0x6f1b94); 0xff when neither is found.
 * DATA TODO: 0x6f1b90 and 0x6f1b94 have no Gold definitions. */

/* ADDRESS: GOLD 0x004fb620 */
void __cdecl fcn_004fb620(char* p)
{
	char file[0x80];
	char base[0x80];
	char suffix[0x80];
	int* slot;
	char* sep;
	char* e;
	int i;
	int j;

	slot = (int*) (p + 0x34);
	if (*slot != 0xff)
		return;
	strcpy(base, p + 4);
	sep = strrchr(base, '_');
	if (sep != 0) {
		strcpy(suffix, sep + 1);
		*sep = 0;
	}
	for (i = 0; i < 4; i++, slot++) {
		sprintf(file, "%s_HEAD%i_%s_ICON.bmp", base, i, suffix);
		*slot = 0xff;
		for (j = 0; j < *(int*) 0x6f1b90; j++) {
			e = (char*) (*(int*) 0x6f1b94 + j * 0x30);
			if (*e == 0)
				break;
			if (strcmpi(file, e) == 0)
				goto found;
		}
		sprintf(file, "%s_HEAD%i_ICON.bmp", base, i);
		*slot = 0xff;
		for (j = 0; j < *(int*) 0x6f1b90; j++) {
			e = (char*) (*(int*) 0x6f1b94 + j * 0x30);
			if (*e == 0)
				break;
			if (strcmpi(file, e) == 0)
				goto found;
		}
		continue;
found:
		*slot = j;
	}
}
