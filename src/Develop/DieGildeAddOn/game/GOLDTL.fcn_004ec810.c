


int __cdecl ahm_CheckFlag(void*);

int __cdecl ahm_CountActiveSlots(char* entity)
{
	char* q;
	int i;
	int count;

	if (ahm_CheckFlag(entity) == 0) {
		return 0;
	}
	count = 0;
	q = *(char**) (*(char**) (entity + 0x16c) + 0x65);
	for (i = 0; i < 6; i++) {
		if (*(int*) (q + 0xc + i * 8) != 0) {
			count++;
		}
	}
	return count;
}
