unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
void* __cdecl fcn_00502cd0(int, int, ...);
extern char* g_item_def_table;
/* ADDRESS: GOLDTL 0x00530510 */
void __cdecl fcn_00530510(void)
{
	unsigned short* entity;
	unsigned short id; int mode; char *table;

	mode = *(int*) 0x7746c4; entity = (unsigned short*) *(int*) 0x7746c8;
	*(int*) 0x7e2a9c = 0;
	*(int*) 0x7e2aa0 = 0;
	*(int*) 0x7ea3bc = 0;
	*(int*) 0x7746c0 = 0;
	if (mode != 0) {

		if (entity == 0) {
			return;
		}
	}
	else {

		if (entity == 0) {
			entity = gm_StartFilteredEntitySearch(1, 0, 0x44);
		}
	}
	if (entity == 0) {
		return;
	}
	*(unsigned char*) 0x7746f4 = 0;
	entity = fcn_00502cd0(*(int*) ((char*) entity + 0x5d), 1, 5);
	if (entity == 0) {
		return;
	}
	do {
		table = g_item_def_table; id = *entity; table += (int)id * 64;
		if ((unsigned char)table[id] == 0x1d) {
			*(int*) ((char*) entity + 0x20) &= 0xfffffffd;
		}
	} while ((entity = gm_NextEntityQueryMatch()) != 0);
}
