


#include <string.h>

// SIZE 0x84
typedef struct Event {
	int id;
	char name[0x80];
} Event;

extern char g_67a59c[];

void* __cdecl m_alloc(int, void*);
void __cdecl m_FreeTracked(void*);

char __cdecl fcn_0043b580(char* o, int idx, int id, char* name)
{
	Event* e;
	int i;

	if (o == 0) {
		return 0;
	}
	if (idx != 0) {
		if (id != 0) {
			if (*(Event**) (o + 0x1d4) == 0) {
				*(Event**) (o + 0x1d4) = (Event*) m_alloc(0x39c, g_67a59c);
			}
			(*(Event**) (o + 0x1d4))[idx].name[0x7f] = 0;
			strncpy((*(Event**) (o + 0x1d4))[idx].name, name, 0x7f);
			(*(Event**) (o + 0x1d4))[idx].id = id;
			return 1;
		}
		if (*(Event**) (o + 0x1d4) != 0) {
			e = &(*(Event**) (o + 0x1d4))[idx];
			if (e->id != 0) {
				e->id = 0;
				for (i = 0; i < 7; i++) {
					if ((*(Event**) (o + 0x1d4))[i].id != 0) {
						break;
					}
				}
				if (i == 7) {
					m_FreeTracked(*(Event**) (o + 0x1d4));
					*(Event**) (o + 0x1d4) = 0;
				}
			}
		}
	}
	return 1;
}
