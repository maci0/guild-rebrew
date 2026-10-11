// FUNCTION: GOLD 0x0043e820
// FUNCTION: GOLDTL 0x43b660

#include <string.h>

// SIZE 0x84
typedef struct Event {
	int id;
	char name[0x80];
} Event;

extern char g_67a5bc[];

void* __cdecl m_AllocTracked(int, void*);
void __cdecl m_FreeTracked(void*);

char __cdecl fcn_0043b660(char* o, int idx, int id, char* name)
{
	Event* e;
	int i;

	if (o == 0) {
		return 0;
	}
	if (idx != 0) {
		if (id != 0) {
			if (*(Event**) (o + 0x3c8) == 0) {
				*(Event**) (o + 0x3c8) = (Event*) m_AllocTracked(0x39c, g_67a5bc);
			}
			(*(Event**) (o + 0x3c8))[idx].name[0x7f] = 0;
			strncpy((*(Event**) (o + 0x3c8))[idx].name, name, 0x7f);
			(*(Event**) (o + 0x3c8))[idx].id = id;
			return 1;
		}
		if (*(Event**) (o + 0x3c8) != 0) {
			e = &(*(Event**) (o + 0x3c8))[idx];
			if (e->id != 0) {
				e->id = 0;
				for (i = 0; i < 7; i++) {
					if ((*(Event**) (o + 0x3c8))[i].id != 0) {
						break;
					}
				}
				if (i == 7) {
					m_FreeTracked(*(Event**) (o + 0x3c8));
					*(Event**) (o + 0x3c8) = 0;
				}
			}
		}
	}
	return 1;
}
