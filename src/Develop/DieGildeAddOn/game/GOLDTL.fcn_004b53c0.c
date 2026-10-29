


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

void __cdecl fcn_004b53c0(unsigned short* key, int kind, stat12* out)
{
	unsigned char* e;
	int match;
	int total;

	match = 0;
	if (kind != 0)
		e = gm_StartFilteredEntitySearch(1, 5, kind);
	else
		e = gm_StartFilteredEntitySearch(1, 6);
	total = 0;
	while (e != 0) {
		if (*(unsigned short*) (e + 0x27) == *key)
			match++;
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
