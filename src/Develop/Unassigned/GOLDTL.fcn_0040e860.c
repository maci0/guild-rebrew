

void __cdecl fcn_00455350(char*, char*, char*);
int __cdecl fcn_00442910(int, char*, char*, int);

int __cdecl CreateObjectAtDummy(int* a1, char** dummy)
{
	char pos[0x10];

	if (*dummy == 0) {
		return 0;
	}
	fcn_00455350(*dummy, *dummy + 0x4c, pos);
	return fcn_00442910(0, pos, *dummy + 0x84, *a1);
}
