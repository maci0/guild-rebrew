


extern unsigned char g_773d75;

unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_LookupWeaponSpec(int);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);

void __cdecl gm_RemoveSpecialTableItems(char* entity)
{
	unsigned short* p;
	int id;

	for (p = fcn_00502cd0(*(int*) (entity + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		id = *p;
		if (gm_LookupWeaponSpec(id) != 0) {
			cm_SendSellObjekt(-1, *(int*) (entity + 4), id, *(int*) ((char*) p + 0xe), (*(char*)&g_773d75), 0);
		}
	}
}
