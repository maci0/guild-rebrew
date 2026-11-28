#include <string.h>

int __cdecl atoi(char*);
int __cdecl gm_GetLawEntry(int, void*);
void __cdecl gm_SetLawValue(unsigned short*, unsigned char, int);

struct HST_LAW_RANGE {
	char kind;
	char strict;
	short pad2;
	int lo;
	int hi;
	int pad0c[3];
	int cur;
};
// SIZE 0x1c

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


/* ADDRESS: GOLDTL 0x004b0c90 */
/* ADDRESS: GOLDDE 0x0049efb0 */
int __cdecl hst_HandleGesetzRel(int unused1, int unused2, char* text)
{
	int ids[2];
	int i;
	int n;
	int id;

	if (*text != '-')
		return 0;
	{
		int sign = -1;
		char signs[2][6] = { "MINUS", "PLUS" };
		char names[2][32] = { "RECHTSPRECHUNG_HAERTE", "AEMTEREINKOMMEN" };
		struct HST_LAW_RANGE* r;

		ids[0] = 0;
		ids[1] = 0xf;
		text++;
		for (i = 0; i < 2; i++) {
			if (memcmp(text, signs[i], strlen(signs[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		if (i == 1)
			sign = i;
		text += strlen(names[i]);
		if (*text != '_')
			return 0;
		text++;
		for (i = 0; i < 2; i++) {
			if (memcmp(text, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		text += strlen(names[i]);
		if (*text != '_')
			return 0;
		id = ids[i];
		r = (struct HST_LAW_RANGE*) names;
		if (gm_GetLawEntry(id, r) == 0)
			return 0;
		text++;
		n = atoi(text) * sign + r->cur;
		n = MAX(MIN(r->hi, n), r->lo);
	}
	gm_SetLawValue(0, id, n);
	return 1;
}
