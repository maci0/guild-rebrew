// FUNCTION: GOLDTL 0x4ceb40
// SIZE: 89

typedef struct
{
	int id;
	char pad[0x28];
} Slot2c;
// SIZE 0x2c

typedef struct
{
	char head[0x94];
	Slot2c slots[16];
	char tail[8];
} Player35c;
// SIZE 0x35c

extern char* g_772eb4;
extern Player35c g_9b0e20[];

Slot2c* __cdecl fcn_004ceb40(char* a1)
{
	int n;
	int i;
	int j;
	Player35c* p;

	n = *(unsigned char*) (g_772eb4 + 0x30);
	for (i = 0; i < n; i++) {
		p = &g_9b0e20[i];
		for (j = 0; j < 16; j++) {
			if (p->slots[j].id == *(int*) (a1 + 4)) {
				return &p->slots[j];
			}
		}
	}
	return 0;
}
