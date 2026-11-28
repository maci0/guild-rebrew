


int  __cdecl d2_ShowMedicusDialog(void*, void*);
extern char str_fmt_s[];
void __cdecl io_FormatTextBuffer(void*, int, int);

/* ADDRESS: GOLDDE 0x004e3240 */
int __cdecl he_HandleMedicusRequest(void* entity, void* request)
{
	int mode;

	mode = *(int*) request;
	if (mode == 3 || mode == 1) {
		if ((*(char*) ((char*) entity + 0x1c8) & 0x40) == 0) {
			if ((double) *(int*) ((char*) entity + 0x24) < -20.0 ||
			    (*(int*) ((char*) entity + 0x2c) & 0xfffffff0) != 0) {
				if (mode == 3) {
					return d2_ShowMedicusDialog(entity, request);
				}
				if (mode == 1 && *(char*) ((char*) entity + 2) == 6) {
					io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d3a);
				}
				return 2;
			}
		}
	}
	return 1;
}
