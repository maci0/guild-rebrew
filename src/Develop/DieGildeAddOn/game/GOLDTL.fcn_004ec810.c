


int __cdecl ahm_CheckFlag(void*);

int __cdecl fcn_004ec810(char* a1)
{
	char* q;
	int i;
	int count;

	if (ahm_CheckFlag(a1) == 0) {
		return 0;
	}
	count = 0;
	q = *(char**) (*(char**) (a1 + 0x16c) + 0x65);
	for (i = 0; i < 6; i++) {
		if (*(int*) (q + 0xc + i * 8) != 0) {
			count++;
		}
	}
	return count;
}
