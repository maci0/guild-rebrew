


int  __cdecl gm_RunIntimidationAction(void*, void*);
extern char g_679060[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl fcn_004f76d0(void* entity, void* command)
{
	int kind;

	kind = *(int*) command;
	if (kind != 3 && kind != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) entity + 0xd) < 3) {
		return 1;
	}
	if (kind == 3) {
		gm_RunIntimidationAction(entity, command);
		return 2;
	}
	if (kind == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) command + 0x14, (int) "%s", 0x1d60);
	}
	return 2;
}
