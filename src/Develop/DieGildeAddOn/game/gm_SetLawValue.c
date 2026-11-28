


#pragma pack(push, 1)
typedef struct
{
	int id;
	unsigned char k;
	int v;
	char pad[3];
} Msg0c;
// SIZE 0xc
#pragma pack(pop)

int __cdecl gm_GetLawEntry(unsigned char k, int* info);
int __cdecl cm_RequestSetLaw(Msg0c* m);

/* ADDRESS: GOLDDE 0x004e0920 */
int __cdecl gm_SetLawValue(unsigned short* entity, unsigned char lawId, int value)
{
	Msg0c m;
	int info[9];
	int id;

	if (!gm_GetLawEntry(lawId, info)) {
		return -1;
	}
	if (entity == 0) {
		id = -1;
	} else {
		if (*entity == 0xffff) {
			return -1;
		}
		id = *(int*) (entity + 2);
	}
	if (value < info[1]) {
		value = info[1];
	} else if (value > info[2]) {
		value = info[2];
	}
	m.id = id;
	m.k = lawId;
	m.v = value;
	return cm_RequestSetLaw(&m);
}
