


typedef struct
{
	int id;
	char pad[0x40];
} Rec44;
// SIZE 0x44

extern unsigned char* lpGebaeudePROT;

int __cdecl cm_GetBuildingStatCount(unsigned char* e);
unsigned short __cdecl gm_RandomMod(unsigned short n);

Rec44* __cdecl fcn_004f1a40(unsigned char* e)
{
	unsigned char* ent;
	char* d;
	Rec44* recs;
	int n;
	int k;
	int idx;

	ent = lpGebaeudePROT + *e * 0x24d;
	d = *(char**) (e + 0x65);
	if (ent[0] == 0x1d && ent[0x247] >= 1 && ent[0x247] <= 3) {
		n = cm_GetBuildingStatCount(e);
		idx = gm_RandomMod((unsigned short) n);
		k = n;
		if (k != 0) {
			recs = *(Rec44**) (d + 0x20);
			while (k != 0) {
				if (recs[idx].id != -1) {
					return &recs[idx];
				}
				k--;
				idx = (idx + 1) % n;
			}
		}
	}
	return 0;
}
