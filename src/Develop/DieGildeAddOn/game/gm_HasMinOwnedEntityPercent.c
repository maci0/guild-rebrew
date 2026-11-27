


extern char g_7f4ca4[];
extern float g_662cf8;

int __cdecl gm_HasMinOwnedEntityPercent(char* entity, char* spec)
{
	int total;
	int match;
	int i;

	total = 0;
	match = 0;
	for (i = 0; i < 0x300; i++) {
		if ((unsigned char) g_7f4ca4[i * 0x21c - 2] < 10) {
			total++;
			if (g_7f4ca4[i * 0x21c + 8] == entity[0xc])
				match++;
		}
	}
	if ((float) match / total * g_662cf8 >= *(int*) (spec + 0x14))
		return 1;
	return 0;
}
