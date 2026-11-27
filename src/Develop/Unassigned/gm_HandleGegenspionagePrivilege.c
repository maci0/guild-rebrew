extern char g_679060[];

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl gm_HandleGegenspionage(char*, int*);


/* ADDRESS: GOLDTL 0x004f8bb0 */
int __cdecl gm_HandleGegenspionagePrivilege(char* entity, int* request)
{
	char* target;

	if (*request == 3 || *request == 1) {
		if (entity[2] == 6)
			io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1db6);
		if (entity[0x166] != 0x13 && entity[0x166] != 0x14 && entity[0x166] != 0x18 && entity[0x166] != 0x1a)
			return 1;
		if (*(int*) (entity + 0x1c8) & 0x200)
			return 9;
		if (*request == 3)
			gm_HandleGegenspionage(entity, request);
		return 2;
	}
	if (*request == 4 || *request == 2) {
		if ((*(int*) (entity + 0x1c8) & 0x100) == 0 || (target = *(char**) ((char*) request + 0x21c)) == 0)
			return 1;
		if (target[0x166] != 0x13 && target[0x166] != 0x14 && target[0x166] != 0x18 && target[0x166] != 0x1a)
			return 1;
		if (*request == 4) {
			gm_HandleGegenspionage(entity, request);
			return 10;
		}
		if (entity[2] == 6)
			io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1db6);
		return 10;
	}
	return 1;
}
