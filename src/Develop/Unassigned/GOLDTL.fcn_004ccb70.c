


char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl evt_FindScriptById(int);
void __cdecl evt_RequestScriptExit(int);

int __cdecl fcn_004ccb70(char* a1, char* response)
{
	char* entity;
	char* q;
	int v;

	entity = gm_LookupEntityRecordById(*(int*) (a1 + 0x10));
	if (entity == 0) {
		return 1;
	}
	q = *(char**) (entity + 0x184);
	if (q != 0) {
		v = *(int*) (q + 0x28);
		if (v != -1) {
			evt_RequestScriptExit(evt_FindScriptById(v));
		}
	}
	if (response != 0) {
		response[0] = 1;
		response[1] = 0;
		*(int*) (response + 6) = 0;
	}
	return 0;
}
