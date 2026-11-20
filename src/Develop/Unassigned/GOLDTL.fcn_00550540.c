


int __cdecl he_FreeAction(int*);

int __cdecl fcn_00550540(int* action)
{
	int v;

	v = *(int*) ((char*) action + 0x70);
	if (v == -2 || v == 0) {
		return he_FreeAction(action);
	}
	return v;
}
