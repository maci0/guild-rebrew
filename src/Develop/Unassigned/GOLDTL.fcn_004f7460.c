


int  __cdecl fcn_005d4fa0(void*, void*);
extern char g_679060[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl fcn_004f7460(void* entity, void* request)
{
	int mode;

	mode = *(int*) request;
	if (mode == 3 || mode == 1) {
		if ((*(char*) ((char*) entity + 0x1c8) & 0x40) == 0) {
			if ((double) *(int*) ((char*) entity + 0x24) < -20.0 ||
			    (*(int*) ((char*) entity + 0x2c) & 0xfffffff0) != 0) {
				if (mode == 3) {
					return fcn_005d4fa0(entity, request);
				}
				if (mode == 1 && *(char*) ((char*) entity + 2) == 6) {
					io_FormatTextBuffer((char*) request + 0x14, (int) g_679060, 0x1d3a);
				}
				return 2;
			}
		}
	}
	return 1;
}
