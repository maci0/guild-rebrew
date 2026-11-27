


void __cdecl gm_GenerateShuffledIndices(int, int*);
void __cdecl gm_IncreaseEntitySkill(unsigned char*, int);
void __cdecl cm_RequestUpdateResidenceDecor(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowUseObjDialog(char*);

int __cdecl gm_ObjBoostOneSkill(unsigned char* e, int* action)
{
	int ids[5];
	char text[0x800];
	int last;
	int i;
	int count;

	last = 0;
	action[4] = 1;
	gm_GenerateShuffledIndices(5, ids);
	i = 0;
	count = 0;
	while (count < 1 && i < 5) {
		if (e[ids[i] + 0x80] < 0xfc) {
			gm_IncreaseEntitySkill(e, ids[i]);
			last = ids[i];
			count++;
		}
		i++;
	}
	if (e[2] == 6) {
		cm_RequestUpdateResidenceDecor(*(int*) (e + 4));
		io_FormatTextBuffer(text, 0xfe8, **(unsigned short**) action * 2 + 0xd71, last + 0x16b7);
		d2_ShowUseObjDialog(text);
	}
	return 1;
}
