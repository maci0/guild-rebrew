


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_00506fd0(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl fcn_00502cd0(int, int, int, int, int);

int __cdecl fcn_004b48d0(unsigned short* a1)
{
	unsigned char* e;
	int x;
	int cnt;
	int ok;
	int j;
	char* row;
	unsigned short v;

	x = fcn_00506fd0(*((unsigned char*) a1 + 0x164));
	if (x == 0)
		return 0;
	cnt = 0;
	e = gm_StartFilteredEntitySearch(2, 4, a1[0], 5, x);
	while (cnt < 3 && e != 0) {
		ok = 1;
		row = ((char*)lpGebaeudePROT) + *e * 0x24d;
		for (j = 0; j < 0x40; j++) {
			v = *(unsigned short*) (row + 0x23 + j * 2);
			if (v == 0)
				break;
			if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, v & 0x7fff) == 0) {
				ok = 0;
				break;
			}
		}
		cnt += ok;
		e = gm_FindNextFilteredEntity();
	}
	if (cnt >= 3)
		return 1;
	return 0;
}
