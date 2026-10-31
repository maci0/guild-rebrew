extern char g_6b5c60[];
extern char g_7f4ca4[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_004ea560(void* a1, char* a2)
{
	char buf[0x200];
	char t;
	char* p;

	if (a1 == 0) {
		return;
	}
	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7 || t == 5) {
		io_FormatTextBuffer(buf, 0x1c21, *(unsigned short*) a1,
		    a2 + (*(char*) ((char*) a1 + 9) ? 0x27b : 0x253));
		p = g_7f4ca4;
		do {
			if (*(char*) (p - 2) == 6) {
				fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fd, g_6b5c60);
			} else if (*(char*) (p - 2) == 7) {
				fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
			}
			p += 0x21c;
		} while ((int) p < (int) (g_7f4ca4 + 0x65400));
	}
}
