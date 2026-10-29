


int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_005100f0(int, int);

int __cdecl fcn_005de960(char* e)
{
	if (e[2] == 6) {
		if (fcn_00525f60(e, 3) == 0) {
			return 0;
		}
	} else if (*(int*) (e + 0x194) < 3) {
		return 0;
	}
	fcn_005100f0(*(int*) (e + 4), -3);
	return 1;
}
