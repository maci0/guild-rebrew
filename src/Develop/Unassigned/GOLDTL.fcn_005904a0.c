


char* __cdecl gm_FindBuildingOwner(int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);

void __cdecl fcn_005904a0(char* obj, unsigned int flag)
{
	int id;
	int h;

	if (*(int*) (obj + 0x16c) != 0 && obj == gm_FindBuildingOwner(*(int*) (obj + 0x16c))) {
		return;
	}
	id = *(int*) (*(char**) (obj + 0x184) + 0x28);
	if (id != -1) {
		h = evt_FindScriptById(id);
		if (h != 0) {
			evt_RequestScriptExit(h);
		}
	}
	*(unsigned int*) (obj + 0x1b4) ^= (*(unsigned int*) (obj + 0x1b4) ^ flag) & 1;
}
