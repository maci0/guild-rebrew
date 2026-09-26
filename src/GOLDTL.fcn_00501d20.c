extern char g_85ab90[];
extern char* g_773d78;
extern unsigned char g_773d75;
extern unsigned char* g_868050;
extern char* g_99ec10;

void* __cdecl gm_AddObjekt(void);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl fcn_00502cd0(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00502fe0(int, int, int);

// FUNCTION: GOLDTL 0x501d20
// SIZE: 692
void __cdecl fcn_00501d20(int season)
{
	unsigned int ids[8];
	char* slots;
	void* entity;
	void* query;
	unsigned short* result;
	unsigned short* r2;
	char* def;
	int i;
	int j;
	int k;
	int count;

	ids[0] = 0x92;
	ids[1] = 0x93;
	ids[2] = 0x94;
	ids[3] = 0x95;
	ids[4] = 0x96;
	ids[5] = 0x97;
	ids[6] = 0x2db;
	ids[7] = 0;

	(*(int*)&g_773d78) = (int) gm_StartFilteredEntitySearch(1, 5, 0xa);
	if ((*(int*)&g_773d78) == 0) {
		return;
	}

	slots = g_85ab90 + season * 0x2a90;
	if (season != g_773d75) {
		return;
	}
	for (i = 0; i < 0x55; i++) {
		*(int*) (slots + i * 0x80 + 4) = 0;
	}

	entity = gm_StartFilteredEntitySearch(1, 6);
	while (entity != 0) {
		if (*(char*) (g_868050 + *(unsigned char*) entity * 0x24d) != '\n') {
			query = fcn_00502cd0(*(int*) ((char*) entity + 0x5d), 1, 0, 0xff);
			for (i = 0; query != 0 && i < 0x55; i++) {
				if (*(unsigned short*) (slots + i * 0x80) != 0 &&
				    fcn_00502cd0(*(int*) ((char*) query + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) != 0) {
					*(int*) (slots + i * 0x80 + 4) = 1;
					def = g_99ec10 + *(unsigned short*) (slots + i * 0x80) * 0x41;
					for (j = 0; j < 0x55; j++) {
						for (k = 0; k < 4; k++) {
							if (*(unsigned short*) (slots + j * 0x80) == *(unsigned short*) (def + 0x2e + k * 2)) {
								*(int*) (slots + j * 0x80 + 4) = 1;
							}
						}
					}
				}
			}
		}
		entity = gm_AddObjekt();
	}

	for (i = 0; i < 0x55; i++) {
		result = fcn_00502cd0(*(int*) ((char*) (*(int*)&g_773d78) + 0x5d), 1, 0, *(unsigned short*) (slots + i * 0x80 + 0x3c));
		if (result != 0) {
			result = fcn_00502cd0(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (*(int*) (slots + i * 0x80 + 4) != 0) {
				if (fcn_00502cd0(*(int*) ((char*) result + 0x14), 1, 0, *(unsigned short*) (slots + i * 0x80)) == 0) {
					fcn_00502fe0(*(int*) ((char*) result + 2), *(unsigned short*) (slots + i * 0x80), 1);
				}
			}
		}
	}

	for (i = 0; ids[i] != 0; i++) {
		count = 0;
		result = fcn_00502cd0(*(int*) ((char*) (*(int*)&g_773d78) + 0x5d), 1, 0, ids[i]);
		if (result != 0) {
			r2 = fcn_00502cd0(*(int*) ((char*) result + 0x14), 1, 0, 0xff);
			if (r2 != 0) {
				r2 = fcn_00502cd0(*(int*) ((char*) r2 + 0x14), 1, 5);
				while (r2 != 0) {
					count++;
					r2 = gm_NextEntityQueryMatch();
				}
				result = fcn_00502cd0(*(int*) ((char*) result + 0x14), 1, 4, 0x11);
				if (result != 0 && *(unsigned char*) ((char*) result + 0x1c) != count)
					*(unsigned char*) ((char*) result + 0x1c) = (unsigned char) count;
			}
		}
	}
}
