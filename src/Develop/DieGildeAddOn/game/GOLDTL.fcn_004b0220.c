#include <stdlib.h>
#include <string.h>

char *__cdecl fcn_0050e4a0(int);
void *__cdecl fcn_00502cd0(int, int, ...);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
extern char *g_item_def_table;
unsigned short *__cdecl gm_NextEntityQueryMatch(void);

/* Native body ends at 0x4b03d6; the stored 448-byte extent adds 10 alignment NOPs. */
/* ADDRESS: GOLDTL 0x004b0220 */
int __cdecl fcn_004b0220(int a1, int a2, char *a3)
{
	if (*a3 != '-') {
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
		char *p;
		char *e;
		unsigned short *q;
		unsigned short *r;

		p = a3 + 1;
		for (i = 0; i < 2; i++) {
			if (memcmp(p, word[i], strlen(word[i])) == 0) {
				break;
			}
		}
		if (i >= 2) {
			return 0;
		}
		dir = sign[i];
		p += strlen(word[i]);
		if (*p != '_') {
			return 0;
		}
		p++;
		a3 = (char *) atoi(p);
		if ((int) a3 <= 0) {
			return 1;
		}
		e = fcn_0050e4a0(1);
		if (e == 0) {
			return 0;
		}
		q = fcn_00502cd0(*(int *) (e + 0x5d), 2, 6, 0, 0x115);
		if (q == 0) {
			return 0;
		}
		r = fcn_00502cd0(*(int *) ((char *) q + 0x14), 1, 5);
		if (r == 0) {
			return 1;
		}
		while (1) {
			type = g_item_def_table[*(unsigned short *) r * 0x41];
			if (type == 9) {
				break;
			}
			r = gm_NextEntityQueryMatch();
			if (r == 0) {
				return 1;
			}
		}
		amount = *(int *) ((char *) r + 0xe);
		if (amount <= 0) {
			return 1;
		}
		if (dir == -1) {
			factor = (int) a3 * 0.01f;
			fcn_004c51a0(-1, *(int *) ((char *) q + 2), 0, (int) (factor * amount));
		} else if (dir == 1) {
			factor = (int) a3 * 0.01f;
			fcn_004c51a0(*(int *) ((char *) q + 2), -1, 0, (int) (factor * amount));
		}
		return 1;
	}
	return 0;
}
