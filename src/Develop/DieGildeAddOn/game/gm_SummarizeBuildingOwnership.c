


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

extern char gm_EntityIdField[];

/* ADDRESS: GOLDDE 0x004a36d0 */
void __cdecl gm_SummarizeBuildingOwnership(int kind, stat12* out)
{
	unsigned char* e;
	int match;
	int total;
	unsigned short k;
	char t;

	match = 0;
	if (kind != 0)
		e = gm_StartFilteredEntitySearch(1, 5, kind);
	else
		e = gm_StartFilteredEntitySearch(1, 6);
	total = 0;
	while (e != 0) {
		k = *(unsigned short*) (e + 0x27);
		if (k != 0xffff) {
			t = gm_EntityIdField[k * 0x21c - 2];
			if (t == 6 || t == 7)
				match++;
		}
		e = gm_FindNextFilteredEntity();
		total++;
	}
	out->a = match;
	out->n = total;
	if (total > 0)
		out->f = (float) match / total;
	else
		out->f = 0;
}
