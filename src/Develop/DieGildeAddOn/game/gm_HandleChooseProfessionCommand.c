


int  __cdecl d2_RunProfessionSelectDialog(void*, void*);
extern char str_fmt_s[];
void __cdecl io_FormatTextBuffer(void*, int, int);

/* ADDRESS: GOLDDE 0x004e31c0 */
int __cdecl gm_HandleChooseProfessionCommand(void* entity, void* context)
{
	int result;

	result = 2;
	if (*(int*) context != 3 && *(int*) context != 1) {
		return 1;
	}
	if (*(char*) ((char*) entity + 2) != 6 && *(char*) ((char*) entity + 2) != 5) {
		return 1;
	}
	if (*(int*) context == 3 && *(char*) ((char*) entity + 2) == 6) {
		result = d2_RunProfessionSelectDialog(entity, context) | 2;
	} else if (*(int*) context == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) "%s", 0x1d35);
	}
	return result;
}
