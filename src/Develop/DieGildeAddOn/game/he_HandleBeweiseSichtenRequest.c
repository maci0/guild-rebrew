


void* __cdecl he_StartHandlungSearch(int, int, int);
void* __cdecl he_fn_Handlung(void);
void  __cdecl d2_RunBeweiseSichtenDialog(void*, void*);
void  __cdecl io_FormatTextBuffer(void*, int, int);
extern char str_fmt_s[];

/* ADDRESS: GOLDDE 0x004e32c0 */
int __cdecl he_HandleBeweiseSichtenRequest(void* entity, void* request)
{
	void* p;

	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if (*(char*) ((char*) entity + 0x166) == 0xd) {
		return 1;
	}
	p = he_StartHandlungSearch(1, 0, 0x2c);
	while (p != 0) {
		if (*(int*) ((char*) p + 0xac) == *(int*) ((char*) entity + 4)) {
			return 1;
		}
		p = he_fn_Handlung();
	}
	if (*(int*) request == 3) {
		d2_RunBeweiseSichtenDialog(entity, request);
		return 2;
	}
	if (*(int*) request == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d44);
	}
	return 2;
}
