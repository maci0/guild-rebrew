

extern char str_empty[];

char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl d2_RunCouncilVoteDialog(char* a, char* p, char* q, int* out);
int __cdecl amt_IsNextOfficeStep(char* a, int v);
int __cdecl cut_ShowSessionDialog(char c, char* a, int* args, int* out);
int __cdecl fcn_0064d41a(char* buf, char* fmt, ...);
/* ADDRESS: GOLD 0x4dada0 */

void __cdecl cut_HandleOfficeSessionStep(char* o, int* m)
{
	char* a;
	char* p;
	char* q;
	int r;
	int out;

	*(int*) (o + 0x94) = -1;
	*(int*) (o + 0x98) = -1;
	if (*(int*) (o + 0x9c) != 0) {
		return;
	}
	a = gm_LookupEntityRecordById(*(int*) (o + 0x10));
	if (a == 0 || a[0x166] == 0 || *(unsigned char*) (a + 0x1b1) > 0) {
		return;
	}
	if (m[0] == 1) {
		p = gm_LookupEntityRecordById(m[3]);
		q = gm_LookupEntityRecordById(m[4]);
		if (p == 0 || q == 0) {
			return;
		}
		r = d2_RunCouncilVoteDialog(a, p, q, &out);
		*(int*) (o + 0x98) = out;
		*(int*) (o + 0x94) = r;
		fcn_0064d41a(o + 0x14, &(*(char*)str_empty));
	} else if (m[0] == 2) {
		if (amt_IsNextOfficeStep(a, m[2]) == 0) {
			return;
		}
		r = cut_ShowSessionDialog(*(char*) (m + 1), a, m + 3, &out);
		*(int*) (o + 0x98) = out;
		*(int*) (o + 0x94) = r;
		fcn_0064d41a(o + 0x14, &(*(char*)str_empty));
	}
}
