typedef struct {
	int id;
	int b;
} HISTORY_BANK_ENTRY;

typedef struct {
	int a;
	HISTORY_BANK_ENTRY e[8];
} HISTORY_BANK_SLOT;
// SIZE 0x44

typedef struct {
	char name[0x74];
} TXT_BANK_HEADER;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_6808a4[];

int __cdecl _strnicmp(char*, char*, int);
void __cdecl txt_ReleaseTextBank(TXT_BANK_HEADER*);


/* ADDRESS: GOLDTL 0x004b2070 */
void __cdecl txt_ResetHistoryTextBanks(void)
{
	int j;
	int i;

	for (j = 0; j < 4; j++) {
		((HISTORY_BANK_SLOT*)g_1007bc0)[j].a = 1;
		for (i = 0; i < 4; i++) {
			((HISTORY_BANK_SLOT*)g_1007bc0)[j].e[i].id = -1;
			((HISTORY_BANK_SLOT*)g_1007bc0)[j].e[i].b = 0xffff;
		}
	}
	for (i = 0; i < 128; i++) {
		if (_strnicmp(((TXT_BANK_HEADER*)txt_TextBanks)[i].name, g_6808a4, 9) == 0)
			txt_ReleaseTextBank(&((TXT_BANK_HEADER*)txt_TextBanks)[i]);
	}
}
