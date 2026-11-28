


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/Units/Error/error_message.h"
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00554320 */
void __cdecl he_AllocKillPlayer(char* e)
{
	char* o;

	if (gm_LookupEntityRecordById(*(int*) (e + 0xac)) == 0) {
		ReportClientMessage("he_AllocKillPlayer: player not found!");
		he_FreeAction(e);
		return;
	}
	for (o = he_StartHandlungSearch(1, 0, 0x72); o != 0; o = he_fn_Handlung()) {
		if (o != e && *(int*) (o + 0xac) == *(int*) (e + 0xac)) {
			he_FreeAction(e);
			return;
		}
	}
	*(int*) (e + 0xb4) = -1;
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	*(int*) (e + 0xb0) = -1;
	*(int*) (e + 0x84) = -1;
}
