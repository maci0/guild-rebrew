


void* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_005c61e0(int);

int __cdecl gm_HasActiveSpecialObject(char* entity, int objId)
{
	char* match;

	match = (char*) fcn_00502cd0(*(int*) (entity + 0x178), 1, 0, objId);
	if (match != 0) {
		if (fcn_005c61e0(*(unsigned short*) match) != 0) {
			if (*(int*) (match + 0x21) != 0) {
				return 1;
			}
		}
	}
	return 0;
}
