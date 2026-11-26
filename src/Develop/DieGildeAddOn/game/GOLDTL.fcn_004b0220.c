#include <stdlib.h>
#include <string.h>

char *__cdecl gm_GetGuildHall(int);
void *__cdecl fcn_00502cd0(int, int, ...);
int __cdecl cm_RequestTransferCurrencyNoKill(int, int, unsigned char, int);
extern char *g_item_def_table;
unsigned short *__cdecl gm_NextEntityQueryMatch(void);

/* Native body ends at 0x4b03d6; the stored 448-byte extent adds 10 alignment NOPs. */
/* ADDRESS: GOLDTL 0x004b0220 */
int __cdecl hst_CmdStadtkasse(int unused1, int unused2, char *argText)
{
	if (*argText != '-') {
		return 0;
	}
	{
		int sign[2] = {-1, 1};
		char word[2][6] = {"MINUS", "PLUS"};
		float factor;
		int type;
		int i;
		int amount;
		int dir;
		char *cursor;
		char *e;
		unsigned short *q;
		unsigned short *item;

		cursor = argText + 1;
		for (i = 0; i < 2; i++) {
			if (memcmp(cursor, word[i], strlen(word[i])) == 0) {
				break;
			}
		}
		if (i >= 2) {
			return 0;
		}
		dir = sign[i];
		cursor += strlen(word[i]);
		if (*cursor != '_') {
			return 0;
		}
		cursor++;
		argText = (char *) atoi(cursor);
		if ((int) argText <= 0) {
			return 1;
		}
		e = gm_GetGuildHall(1);
		if (e == 0) {
			return 0;
		}
		q = fcn_00502cd0(*(int *) (e + 0x5d), 2, 6, 0, 0x115);
		if (q == 0) {
			return 0;
		}
		item = fcn_00502cd0(*(int *) ((char *) q + 0x14), 1, 5);
		if (item == 0) {
			return 1;
		}
		while (1) {
			type = g_item_def_table[*(unsigned short *) item * 0x41];
			if (type == 9) {
				break;
			}
			item = gm_NextEntityQueryMatch();
			if (item == 0) {
				return 1;
			}
		}
		amount = *(int *) ((char *) item + 0xe);
		if (amount <= 0) {
			return 1;
		}
		if (dir == -1) {
			factor = (int) argText * 0.01f;
			cm_RequestTransferCurrencyNoKill(-1, *(int *) ((char *) q + 2), 0, (int) (factor * amount));
		} else if (dir == 1) {
			factor = (int) argText * 0.01f;
			cm_RequestTransferCurrencyNoKill(*(int *) ((char *) q + 2), -1, 0, (int) (factor * amount));
		}
		return 1;
	}
	return 0;
}
