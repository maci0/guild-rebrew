


int __cdecl d2_CheckActionBlocker(char*, int);
void __cdecl gm_ModifyHealth(int, int);

int __cdecl gm_ObjSpendThreeActionPoints(char* e)
{
	if (e[2] == 6) {
		if (d2_CheckActionBlocker(e, 3) == 0) {
			return 0;
		}
	} else if (*(int*) (e + 0x194) < 3) {
		return 0;
	}
	gm_ModifyHealth(*(int*) (e + 4), -3);
	return 1;
}
