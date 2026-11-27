#include <string.h>

int __cdecl atoi(char*);
int __cdecl gm_GetLawEntry(int, void*);
void __cdecl gm_SetLawValue(unsigned short*, unsigned char, int);

struct range_4b0b30 {
	char kind;
	char strict;
	short pad2;
	int lo;
	int hi;
};
// SIZE 0xc

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


/* ADDRESS: GOLDTL 0x004b0b30 */
int __cdecl fcn_004b0b30(int a1, int a2, char* arg)
{
	int ids[2];
	int i;
	int n;
	int id;

	if (*arg != '-')
		return 0;
	{
		char names[2][32] = { "RECHTSPRECHUNG_HAERTE", "AEMTEREINKOMMEN" };
		struct range_4b0b30* r;

		ids[0] = 0;
		ids[1] = 0xf;
		arg++;
		for (i = 0; i < 2; i++) {
			if (memcmp(arg, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		arg += strlen(names[i]);
		if (*arg != '_')
			return 0;
		arg++;
		n = atoi(arg);
		id = ids[i];
		r = (struct range_4b0b30*) names;
		if (gm_GetLawEntry(id, r) == 0)
			return 0;
		if ((n < r->lo || n > r->hi) && r->strict != 0)
			return 0;
		n = MAX(MIN(r->hi, n), r->lo);
	}
	gm_SetLawValue(0, id, n);
	return 1;
}
