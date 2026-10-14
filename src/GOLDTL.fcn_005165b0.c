extern char g_773dd4;



void __cdecl fcn_00442a30(char*, int, char, int);

char __cdecl fcn_005165b0(char* e)
{
	int s;

	s = *(int*) (e + 0x220);
	if (s != 2 && s != 4) {
		if (s == 3) {
			fcn_00442a30(e, *(int*) (e + 0x1ec) + 0xf4, g_773dd4, 1);
		} else {
			fcn_00442a30(e, *(int*) (e + 0x1ec) + 0xf4, g_773dd4, 1);
		}
	}
	return 1;
}
