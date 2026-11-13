#include <stdio.h>

void __cdecl fcn_004481e0(void* resource);
void* __cdecl fcn_00448200(const char* name, int flag);
void __cdecl ReportClientMessage(char* text);

/* ADDRESS: GOLD 0x004721d0 */
void __cdecl fcn_004721d0(char* name, int index)
{
	char text[0x400];
	char* win;
	void* old;
	void* loaded;
	int scaled;

	scaled = index * 0x3c4;
	win = (char*) 0xf8f120 + scaled;
	old = *(void**) (win + 0x390);
	if (old != 0) {
		fcn_004481e0(old);
		*(int*) (win + 0x390) = 0;
	}
	if (name != 0 && *name != 0) {
		loaded = fcn_00448200(name, 1);
		*(void**) (win + 0x390) = loaded;
		if (loaded == 0) {
			sprintf(text, (char*) 0x5fe90c);
			ReportClientMessage(text);
		}
		*(int*) (win + 0x394) = 0x3f000000;
	}
}
