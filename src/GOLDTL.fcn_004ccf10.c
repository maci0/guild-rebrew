extern int g_7f4c00;
extern unsigned short g_774970;
extern char g_7f4ca0[];

unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00508e40(int);
void __cdecl fcn_005b2220(char*, char*, void*, int);

// FUNCTION: GOLD 0x4cc390
// SIZE: 383
// FUNCTION: GOLDTL 0x004ccf10
// SIZE: 383

int __cdecl fcn_004ccf10(int cmd, char* result)
{
	void* entity;
	void* site;
	char* rec;
	int target;
	int i;

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}

	if (*(int*) (cmd + 0x10) == 0x636c6572) {
		entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (entity == (void*) 0x0) {
			return 1;
		}
		entity = gm_ff_Objekt(*(int*) ((char*) entity + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}
		if (g_7f4c00 - *(int*) ((char*) entity + 0x28) > 1) {
			*(int*) ((char*) entity + 0x1c) = -1;
			*(int*) ((char*) entity + 0x20) = -1;
			*(int*) ((char*) entity + 0x24) = -1;
			*(int*) ((char*) entity + 0x28) = g_7f4c00 - 1;
		}
		else {
			return 1;
		}
	}
	else if (*(int*) (cmd + 0x10) == 0x62757920) {
		rec = fcn_00508e40(*(int*) (cmd + 0x14));
		if (rec == 0) {
			return 1;
		}

		site = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x18));
		if (site == (void*) 0x0) {
			return 1;
		}
		entity = gm_ff_Objekt(*(int*) ((char*) site + 0x5d), 2, 6, 0, 0x12c);
		if (entity == (void*) 0x0) {
			return 1;
		}

		target = *(int*) (cmd + 0x1c);
		for (i = 0; i < 3; i++) {
			if (*(int*) ((char*) entity + 0x1c + i * 4) == target) {
				break;
			}
		}
		if (i >= 3) {
			return 1;
		}
		*(int*) ((char*) entity + 0x1c + i * 4) = -1;
		if (g_774970 == *(unsigned short*) ((char*) site + 0x27))
			fcn_005b2220(rec, g_7f4ca0 + g_774970 * 540, site, *(int*) (cmd + 0x20));
	}

	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
