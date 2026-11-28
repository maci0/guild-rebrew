


int __cdecl gs_RemoveStraftat(int, int);

/* ADDRESS: GOLDDE 0x004b7410 */
int __cdecl cm_ExRemoveStraftat(char* request, char* output)
{
	switch (gs_RemoveStraftat(*(int*) (request + 0x10), *(int*) (request + 0x14))) {
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	}
	if (output != 0) {
		*output = 1;
	}
	return 0;
}
