


int __cdecl he_FreeAction(int*);

/* ADDRESS: GOLDDE 0x005369a0 */
int __cdecl he_RunAction0x52(int* action)
{
	int v;

	v = *(int*) ((char*) action + 0x70);
	if (v == -2 || v == 0) {
		return he_FreeAction(action);
	}
	return v;
}
