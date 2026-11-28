


extern char gm_EntityIdField[];
extern float flt_100_0;

int __cdecl gm_HasMinOwnedEntityPercent(char* entity, char* spec)
{
	int total;
	int match;
	int i;

	total = 0;
	match = 0;
	for (i = 0; i < 0x300; i++) {
		if ((unsigned char) gm_EntityIdField[i * 0x21c - 2] < 10) {
			total++;
			if (gm_EntityIdField[i * 0x21c + 8] == entity[0xc])
				match++;
		}
	}
	if ((float) match / total * flt_100_0 >= *(int*) (spec + 0x14))
		return 1;
	return 0;
}
