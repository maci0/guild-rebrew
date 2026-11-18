


char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_CheckEntityType(char*);
void __cdecl fcn_0052db70(char*);

int __cdecl fcn_004cc370(char* packet, char* reply)
{
	char* p;

	p = gm_StartFilteredEntitySearch(1, 1, *(int*) (packet + 0x10));
	if (p != 0 && *(int*) (p + 0x61) != 0 && gm_CheckEntityType(p) == 0) {
		fcn_0052db70(p);
	}
	if (reply != 0) {
		reply[0] = 1;
		reply[1] = 0;
		*(int*) (reply + 6) = 0;
	}
	return 0;
}
