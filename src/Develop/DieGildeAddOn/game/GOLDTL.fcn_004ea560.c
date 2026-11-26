extern char g_6b5c60[];
extern char g_7f4ca4[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl amt_NotifyOfficeLost(void* entity, char* role)
{
	char buf[0x200];
	char kind;
	char* slot;

	if (entity == 0) {
		return;
	}
	kind = *(char*) ((char*) entity + 2);
	if (kind == 6 || kind == 7 || kind == 5) {
		io_FormatTextBuffer(buf, 0x1c21, *(unsigned short*) entity,
		    role + (*(char*) ((char*) entity + 9) ? 0x27b : 0x253));
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
