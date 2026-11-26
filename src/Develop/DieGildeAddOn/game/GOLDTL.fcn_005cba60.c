#include <string.h>

typedef struct {
	unsigned short* house;
	char pad4[0x28];
	int role;
	int value;
	int task;
} Action6fCandidate;
// SIZE 0x38

char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl d2_BuildPersonStatusDesc(Action6fCandidate*);
int __cdecl fcn_005cf720(unsigned short, unsigned short, int, int);

/* ADDRESS: GOLDTL 0x005cba60 */
int __cdecl d2_CollectAction6fCandidates(unsigned short* who, unsigned int max, Action6fCandidate* out, int kind)
{
	unsigned short* ps[4];
	char* t;
	unsigned short* q;
	int count;
	int i;

	count = 0;
	for (t = he_StartHandlungSearch(1, 0, 0x6f); t != 0 && count < 4; t = he_fn_Handlung()) {
		if (*(int*) (t + 0xac) == *(int*) (who + 2)) {
			q = gm_LookupEntityRecordById(*(int*) (t + 0xb0));
			if (q != 0) {
				ps[count++] = q;
			}
		}
	}
	if (max != 0) {
		memset(out, 0, max * 0x38);
		for (i = 0; i < (count <= max ? count : max); i++, out++) {
			out->house = ps[i];
			d2_BuildPersonStatusDesc(out);
			out->value = fcn_005cf720(*who, *out->house, kind, 0);
		}
	}
	return count;
}
