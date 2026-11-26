


unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_AssignActionSlot(int, int, int, int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);
void __cdecl gm_KillSpieler(int, int);

int __cdecl fcn_004c9980(char* x, char* out)
{
	unsigned short* e;
	int ok;

	ok = 0;
	if (out != 0)
		*out = 2;
	e = gm_LookupEntityRecordById(*(int*) (x + 0x10));
	if (e != 0) {
		ok = 1;
		he_AssignActionSlot(0, 0, *e, 0);
		if (*(char**) ((char*) e + 0x184) != 0 && *(int*) (*(char**) ((char*) e + 0x184) + 0x28) != -1)
			evt_RequestScriptExit(evt_FindScriptById(*(int*) (*(char**) ((char*) e + 0x184) + 0x28)));
		gm_KillSpieler(*e, *(int*) (x + 0x14));
	}
	if (out != 0 && ok != 0)
		*out = 1;
	return 0;
}
