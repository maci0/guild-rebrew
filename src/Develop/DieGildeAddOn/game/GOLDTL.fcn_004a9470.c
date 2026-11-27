typedef struct Info {
	int pad0[2];
	unsigned char level;
	char pad9[0x18 - 9];
} Info;
// SIZE 0x18

int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl amt_GetRoleTemplate(int job, Info* info);

/* ADDRESS: GOLDTL 0x004a9470 */
int __cdecl ai_PreparePrivErpressung(int unused1, char* actor, int unused3, int unused4, char* out)
{
	Info info;
	int d[32];
	int ids[32];
	int n;
	int i;
	int k;
	char* target;

	if (*(int*) (actor + 0x194) < 2 || (*(int*) (actor + 0x1c8) & 0x100)) {
		return 0;
	}
	n = fcn_004f6040(ids, d, *(unsigned short*) actor);
	if (n <= 0) {
		return 0;
	}
	i = 0;
	k = n;
	do {
		if (d[i] >= 4) {
			target = gm_LookupEntityRecordById(ids[i]);
			if (target && !(*(int*) (target + 0x1c8) & 0x200) && amt_GetRoleTemplate(*(unsigned char*) (target + 0x166), &info) && info.level >= 4) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (target + 4);
				return 1;
			}
		}
		k--;
		i = (i + 1) % n;
	} while (k);
	return 0;
}
