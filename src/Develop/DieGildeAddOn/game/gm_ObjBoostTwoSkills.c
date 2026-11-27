


void __cdecl gm_GenerateShuffledIndices(int, int*);
void __cdecl gm_IncreaseEntitySkill(unsigned char*, int);
void __cdecl cm_RequestUpdateResidenceDecor(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowUseObjDialog(char*);

int __cdecl gm_ObjBoostTwoSkills(unsigned char* e, int* ctx)
{
	int first;
	int ids[5];
	char text[0x800];
	int second;
	int i;
	int n;

	second = 0;
	first = 0;
	ctx[4] = 1;
	gm_GenerateShuffledIndices(5, ids);
	i = 0;
	n = 0;
	while (n < 2 && i < 5) {
		if (e[ids[i] + 0x80] < 0xfc) {
			gm_IncreaseEntitySkill(e, ids[i]);
			n++;
			if (n == 1) {
				first = ids[i];
			}
			else if (n == 2) {
				second = ids[i];
			}
		}
		i++;
	}
	if (e[2] == 6) {
		cm_RequestUpdateResidenceDecor(*(int*) (e + 4));
		io_FormatTextBuffer(text, 0xfe8, **(unsigned short**) ctx * 2 + 0xd71, second + 0x16b7,
		    first + 0x16b7);
		d2_ShowUseObjDialog(text);
	}
	return 1;
}
