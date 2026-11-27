


unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_SetEntityLevel(int, int);
void __cdecl ch_AssignHeadIcon(unsigned short*);

int __cdecl cm_ExSetEntityLevel(char* command, char* result)
{
	unsigned short* p;

	p = gm_LookupEntityRecordById(*(int*) (command + 0x10));
	if (p == 0) {
		return 1;
	}
	gm_SetEntityLevel(*p, *(unsigned char*) (command + 0x14));
	ch_AssignHeadIcon(p);
	if (result != 0) {
		result[0] = 1;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
