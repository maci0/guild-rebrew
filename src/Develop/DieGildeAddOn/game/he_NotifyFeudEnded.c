#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
extern unsigned char g_773d75;
extern char g_868060[];
extern char g_868060[];



void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);
int __cdecl gm_RandomMod(int);

void __cdecl he_NotifyFeudEnded(void* subject, void* recipient)
{
	char t;

	t = *(char*) ((char*) recipient + 2);
	if (t == 6 || t == 7) {
		io_FormatTextBuffer(g_774a80, 0x132f, *(unsigned short*) subject,
		    (gm_RandomMod(3) & 0xffff)
		        + (*(char*) ((char*) recipient + 9) ? 0x1333 : 0x1330),
		    *(unsigned short*) recipient,
		    (gm_RandomMod(3) & 0xffff) + 0x1336,
		    &((unsigned int*)g_868060)[g_773d75 * 189]);
		he_PostEntityMessage(*(int*) ((char*) recipient + 4), -1, g_774a80, 1, 0x5ec, (void*) 0);
	}
}
