


char* __cdecl cut_FindCutsceneById(int);

/* ADDRESS: GOLDDE 0x004bb490 */
int __cdecl cm_ExSetCutsceneState(char* request, char* result)
{
	char* p;

	if (result != 0) {
		result[0] = 2;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	p = cut_FindCutsceneById(*(int*) (request + 0x10));
	if (p == 0) {
		return 1;
	}
	*(int*) (p + 0xc) = *(int*) (request + 0x14);
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
