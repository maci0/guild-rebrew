char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl ch_DestroyCharacter(char*);


/* ADDRESS: GOLDTL 0x004cd4a0 */
/* ADDRESS: GOLDDE 0x004bac80 */
int __cdecl cm_ExDestroyEntityCharacter(char* packet, char* reply)
{
	char* e;

	if (reply != 0) {
		reply[0] = 2;
		reply[1] = 0;
		*(int*) (reply + 6) = 0;
	}
	e = gm_LookupEntityRecordById(*(int*) (packet + 0x10));
	if (e != 0 && *(char**) (e + 0x184) != 0) {
		ch_DestroyCharacter(*(char**) (e + 0x184));
		*(char**) (e + 0x184) = 0;
		if (reply != 0)
			reply[0] = 1;
		return 0;
	}
	return 1;
}
