


typedef struct
{
	unsigned short id;
	unsigned char x2;
	char pad3[0x1a9];
	int x1ac;
	char pad1b0[0x6c];
} Ent21c;
// SIZE 0x21c

extern char gm_EntitySlotTable[];

/* ADDRESS: GOLDDE 0x004f9340 */
int __cdecl gm_GetKircheRank(int entityIdx, int add)
{
	int r;
	int v;
	int j;

	r = 1;
	if (entityIdx < 0 || entityIdx >= 0x300) {
		return 0;
	}
	v = ((Ent21c*)gm_EntitySlotTable)[entityIdx].x1ac + add;
	for (j = 0; j < 768; j++) {
		if (v <= ((Ent21c*)gm_EntitySlotTable)[j].x1ac && ((Ent21c*)gm_EntitySlotTable)[j].id != 0xffff && ((Ent21c*)gm_EntitySlotTable)[j].x2 < 10 && j != entityIdx) {
			r++;
		}
	}
	return r;
}
