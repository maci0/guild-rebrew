extern char g_6b5c60[];
extern char g_7f4ca4[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_004ea560(void* a1, char* a2)
{
	char buf[0x200];
	char kind;
	char* slot;

	if (a1 == 0) {
		return;
	}
	kind = *(char*) ((char*) a1 + 2);
	if (kind == 6 || kind == 7 || kind == 5) {
		io_FormatTextBuffer(buf, 0x1c21, *(unsigned short*) a1,
		    a2 + (*(char*) ((char*) a1 + 9) ? 0x27b : 0x253));
		slot = g_7f4ca4;
		do {
			if (*(char*) (slot - 2) == 6) {
				fcn_00545d40(*(int*) slot, -1, buf, 0, 0x5fd, g_6b5c60);
			} else if (*(char*) (slot - 2) == 7) {
				fcn_00545d40(*(int*) slot, -1, buf, 0, 0x5fe, g_6b5c60);
			}
			slot += 0x21c;
		} while ((int) slot < (int) (g_7f4ca4 + 0x65400));
	}
}
