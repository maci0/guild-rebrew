


void* __cdecl fcn_005463a0(int, int, int);
void* __cdecl he_fn_Handlung(void);
void  __cdecl fcn_005da250(void*, void*);
void  __cdecl io_FormatTextBuffer(void*, int, int);
extern char g_679060[];

int __cdecl fcn_004f74e0(void* entity, void* request)
{
	void* p;

	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if (*(char*) ((char*) entity + 0x166) == 0xd) {
		return 1;
	}
	p = fcn_005463a0(1, 0, 0x2c);
	while (p != 0) {
		if (*(int*) ((char*) p + 0xac) == *(int*) ((char*) entity + 4)) {
			return 1;
		}
		p = he_fn_Handlung();
	}
	if (*(int*) request == 3) {
		fcn_005da250(entity, request);
		return 2;
	}
	if (*(int*) request == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d44);
	}
	return 2;
}
