


int __cdecl he_FreeAction(int*);

int __cdecl he_RunAction0x52(int* action)
{
	int v;

	v = *(int*) ((char*) action + 0x70);
	if (v == -2 || v == 0) {
		return he_FreeAction(action);
	}
	return v;
}
