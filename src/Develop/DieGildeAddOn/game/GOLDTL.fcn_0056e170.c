


#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_00406120(char*);
char* __cdecl fcn_0040c120(char*, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0056e170(char* u)
{
	char* h;

	switch (*(int*) (u + 0x70)) {
	case 0:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h == 0) {
			goto kill;
		}
		if (*(char**) (h + 0x184) != 0 && *(int*) (*(char**) (h + 0x184) + 0x28) != -1) {
			fcn_00428720(fcn_00426cc0(*(int*) (*(char**) (h + 0x184) + 0x28)));
		}
		fcn_00529160(0, 0, *(unsigned short*) h, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 1:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h == 0) {
			goto kill;
		}
		if (*(char**) (h + 0x184) == 0 || *(int*) (*(char**) (h + 0x184) + 0x28) == -1) {
			(*(int*) (u + 0x70))++;
		}
		break;
	case 2:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h == 0) {
			goto kill;
		}
		h[8] = 0;
		fcn_00529160(0, 0, *(unsigned short*) h, 0);
		*(int*) (h + 0x16c) = 0;
		if (*(char**) (h + 0x184) != 0) {
			fcn_00406120(*(char**) (h + 0x184));
			h = fcn_0040c120(*(char**) (h + 0x184), 0x36, 1);
			strcpy(h + 0xf0, "bewegung/zu_boden_sinken");
		}
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 1, 0, 0);
		(*(int*) (u + 0x70))++;
		break;
	case 3:
		h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
		if (h != 0 && (u[0x78] & 2) != 0) {
			fcn_004c57e0(*(int*) (h + 4), 1);
		}
	case -2:
	case -1:
kill:
		fcn_00546190(u);
		break;
	}
}
