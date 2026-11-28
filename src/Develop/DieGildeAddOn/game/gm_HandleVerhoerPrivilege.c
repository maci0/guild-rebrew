


extern char str_fmt_s[];

int __cdecl d2_OpenVerhoerDialog(void*, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl gm_HandleVerhoerPrivilege(void* entity, void* request)
{
	int result;

	result = 0;
	*(char*) ((char*) request + 0x14) = 0;
	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) entity + 0x1c8) & 0x100) != 0) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) entity + 0x1cc) & 0x200) == 0) {
		return 1;
	}
	if (*(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1e15);
	}
	if ((*(unsigned int*) ((char*) entity + 0x1c8) & 0x200) != 0) {
		return 9;
	}
	if ((*(unsigned int*) ((char*) entity + 0x1c8) & 0x40000) != 0) {
		return 1;
	}
	if (*(int*) request == 3) {
		result = d2_OpenVerhoerDialog(entity, request);
	}
	return result | 2;
}
