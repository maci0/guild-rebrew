


int  __cdecl d2_RunErpressungDialog(void*, void*);
extern char str_fmt_s[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl he_HandleErpressungRequest(void* entity, void* request)
{
	int mode;

	mode = *(int*) request;
	if (mode != 3 && mode != 1) {
		return 1;
	}
	if (*(int*) ((char*) entity + 0x1c8) & 0x100) {
		return 1;
	}
	if (mode == 3) {
		d2_RunErpressungDialog(entity, request);
		return 2;
	}
	if (mode == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d54);
	}
	return 2;
}
