


int __cdecl fcn_00546190(int*);

int __cdecl fcn_00550540(int* action)
{
	int v;

	v = *(int*) ((char*) action + 0x70);
	if (v == -2 || v == 0) {
		return fcn_00546190(action);
	}
	return v;
}
