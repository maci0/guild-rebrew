#include <string.h>

int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_004f4830(int, void*);
void __cdecl fcn_004f4860(unsigned short*, unsigned char, int);

struct range_4b0c90 {
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
int __cdecl fcn_004b0c90(int a1, int a2, char* text)
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
		struct range_4b0c90* r;

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
		r = (struct range_4b0c90*) names;
		if (fcn_004f4830(id, r) == 0)
			return 0;
		text++;
		n = fcn_0064eeec(text) * sign + r->cur;
		n = MAX(MIN(r->hi, n), r->lo);
	}
	fcn_004f4860(0, id, n);
	return 1;
}
