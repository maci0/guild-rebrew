


extern char g_6a22d8[];
extern char g_68b3f8[];
void __cdecl io_FormatTextBuffer(void*, int, ...);

void __cdecl fcn_0058b9c0(void* record, void* output)
{
	if (*(int*) ((char*) record + 0x2c) != 0) {
		if (*(int*) ((char*) record + 0x38) == 0) {
			io_FormatTextBuffer(output, (int) g_6a22d8,
			    *(int*) ((char*) record + 0x2c) + 0x253,
			    (char*) record + 4, (char*) record + 0x14);
		} else {
			io_FormatTextBuffer(output, (int) g_6a22d8,
			    *(int*) ((char*) record + 0x2c) + 0x27b,
			    (char*) record + 4, (char*) record + 0x14);
		}
	} else {
		io_FormatTextBuffer(output, (int) g_68b3f8, (char*) record + 4, (char*) record + 0x14);
	}
}
