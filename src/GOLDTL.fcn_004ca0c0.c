extern int g_14cbca0;
extern int g_7728f8;
extern int g_6b8010;
extern unsigned char* g_868050;
extern signed char g_7f3b00[];

char* __cdecl lb_SearchRecordTable(unsigned int);
int __cdecl plt_CheckZoneAvailability(void*, unsigned int, unsigned int, unsigned int);
char* __cdecl plt_FindRecord(void*, unsigned int, unsigned int);
char* __cdecl fcn_004bcda0(void*, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00442be0(void*);
void __cdecl fcn_004bcf20(char*, int);

// FUNCTION: GOLDTL 0x004ca0c0
// SIZE: 529

int __cdecl fcn_004ca0c0(int cmd, char* result)
{
	char status;
	void* entity;
	char* rec;
	char* found;
	int needs_create;
	int saved;

	saved = g_6b8010;
	status = '\x02';
	found = (char*) 0x0;
	needs_create = 0;

	if (g_14cbca0 != -1)
		g_7728f8 = *(int*) (cmd + 0x10);
	entity = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x14));
	if (entity != (void*) 0x0) {
		rec = lb_SearchRecordTable(*(unsigned short*) (cmd + 0x1a));

		if ((rec == (char*) 0x0) || (*(unsigned char*) (cmd + 0x1c) != 0) ||
			(plt_CheckZoneAvailability(
				 *(void**) ((char*) entity + 0x71),
				 *(unsigned char*) (cmd + 0x18),
				 *(unsigned char*) (cmd + 0x19),
				 (unsigned char) rec[0x42]
			 ) != 0)) {
			needs_create = 1;
		}

		if (*(unsigned char*) (cmd + 0x1c) != 0) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if ((found != (char*) 0x0) && (*(int*) (found + 0x10) != -1)) {
				return 1;
			}
		}
		else if (*(int*) (cmd + 0x1d) != -1) {
			found = plt_FindRecord(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19)
			);
			if (found != (char*) 0x0 && *(int*) (found + 0x10) == *(int*) (cmd + 0x1d)) {
				fcn_004432d0(g_7f3b00[g_868050[*(unsigned char*) entity + *(unsigned char*) entity * 0x24c]], 1);
				fcn_00442be0(*(void**) (found + 0x14));
				*(void**) (found + 0x14) = 0;
				fcn_004bcf20(found, 0);
				*(int*) (found + 0x10) = -1;
				fcn_004432d0(saved, 1);
			}
			if (result == (char*) 0x0) {
				return 0;
			}
			*(char**) (result + 6) = found;
			*result = '\x01';
			result[1] = '\x05';
			return 0;
		}

		if (needs_create != 0) {
			fcn_004432d0(g_7f3b00[g_868050[*(unsigned char*) entity + *(unsigned char*) entity * 0x24c]], 1);
			found = fcn_004bcda0(
				*(void**) ((char*) entity + 0x71),
				*(unsigned char*) (cmd + 0x18),
				*(unsigned char*) (cmd + 0x19),
				*(unsigned short*) (cmd + 0x1a),
				*(unsigned char*) (cmd + 0x1c)
			);
			fcn_004432d0(saved, 1);
		}

		if (found != (char*) 0x0) {
			status = '\x01';
			*(int*) (found + 4) = *(int*) ((char*) entity + 1);
			if (*(unsigned char*) (cmd + 0x1c) != 0) {
				*(int*) (found + 0x10) = *(int*) (cmd + 0x1d);
			}
		}
	}

	if (result != (char*) 0x0) {
		*(char**) (result + 6) = found;
		*result = status;
		result[1] = '\x05';
	}

	return 0;
}
